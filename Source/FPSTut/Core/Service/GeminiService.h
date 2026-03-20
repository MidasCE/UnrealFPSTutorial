#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Http.h"
#include "FPSTut/Core/Data/GeminiData.h"
#include "GeminiService.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGeminiCallback, const FAIGameCommand&, Command);

UCLASS()
class FPSTUT_API UGeminiService : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// The Main Function: "Send this text, and call 'Callback' when done."
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SendPrompt(const FString& UserPrompt, FGeminiCallback Callback);
	
	// Exposes the True/False variable to any Blueprint
    UPROPERTY(BlueprintReadWrite, Category = "Gemini Settings")
    bool bIsLLMEnabled = false;
    
    UPROPERTY(BlueprintReadWrite, Category = "Gemini Settings")
    FString GeminiAPIKey = "";

private:
	void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FGeminiCallback Callback);
	FString ExtractJsonFromGemini(const FString& RawResponse);

};
