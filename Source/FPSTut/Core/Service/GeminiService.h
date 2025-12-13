#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Http.h"
#include "FPSTut/Core/Data/GeminiData.h"
#include "GeminiService.generated.h"

// Define the "Phone Call" type (Callback)
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

private:
	void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FGeminiCallback Callback);
	FString ExtractJsonFromGemini(const FString& RawResponse);

	FString ApiKey = "AIzaSyCbjt2VahsZafgFvko4rMxjhw9R559duSE"; // TODO: Move to Config file later
};
