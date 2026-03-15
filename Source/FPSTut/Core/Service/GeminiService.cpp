#include "GeminiService.h"
#include "JsonObjectConverter.h"
#include "HttpModule.h"
#include "FPSTut/Core/Data/GeminiData.h"
#include "Interfaces/IHttpResponse.h"

void UGeminiService::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("Gemini Service Ready"));
}

void UGeminiService::SendPrompt(const FString& UserPrompt, FGeminiCallback Callback)
{
    // 1. Build the Request Data (Using Structs)
    FGeminiRequest RequestBody;
    
    // System Rules
    FGeminiContent SystemContext;
    SystemContext.parts.Add({ "You are a Game AI. Output JSON: {\"command\": \"ACTION\"}. Commands: JUMP, WAVE, CROUCH." });
    RequestBody.system_instruction = SystemContext;
 
    // User Input
    FGeminiContent UserContext;
    UserContext.parts.Add({ UserPrompt });
    RequestBody.contents.Add(UserContext);

    // Convert Struct -> JSON String
    FString JsonString;
    FJsonObjectConverter::UStructToJsonObjectString(RequestBody, JsonString);

    // Create HTTP Request
    FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
    Request->SetURL("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash-lite:generateContent");
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");
    Request->SetHeader("x-goog-api-key", "");
    Request->SetContentAsString(JsonString);

    // Bind Lambda (The "Context Keeper")
    // capture 'Callback' so we know WHO to reply to when the internet replies.
    Request->OnProcessRequestComplete().BindLambda(
        [this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            this->HandleResponse(Request, Response, bWasSuccessful, Callback);
        });

    Request->ProcessRequest();
}

void UGeminiService::HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FGeminiCallback Callback)
{
    if (!bWasSuccessful || !Response.IsValid()) return;

    UE_LOG(LogTemp, Error, TEXT("RAW GOOGLE RESPONSE: %s"), *Response->GetContentAsString());

    // Helper: Clean the messy Google JSON
    FString CleanJson = ExtractJsonFromGemini(Response->GetContentAsString());

    // Convert Clean JSON -> Game Struct
    FAIGameCommand FinalCommand;
    if (FJsonObjectConverter::JsonObjectStringToUStruct(CleanJson, &FinalCommand))
    {
        Callback.ExecuteIfBound(FinalCommand);
    }
}

FString UGeminiService::ExtractJsonFromGemini(const FString& RawResponse)
{
    // Quick Parse: Unwrap Google's "candidates" -> "content" -> "parts" -> "text"
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawResponse);
    if (TSharedPtr<FJsonObject> JsonObj; FJsonSerializer::Deserialize(Reader, JsonObj))
    {
        const TArray<TSharedPtr<FJsonValue>>* Candidates;
        if (JsonObj->TryGetArrayField(TEXT("candidates"), Candidates) && Candidates->Num() > 0)
        {
            auto Parts = (*Candidates)[0]->AsObject()->GetObjectField(TEXT("content"))->GetArrayField(TEXT("parts"));
            const FString Text = Parts[0]->AsObject()->GetStringField(TEXT("text"));
            // Remove markdown wrapper if present
            return Text.Replace(TEXT("```json"), TEXT("")).Replace(TEXT("```"), TEXT("")).TrimStartAndEnd();
        }
    }
    return "";
}