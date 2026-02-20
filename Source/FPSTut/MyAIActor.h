#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Data/GeminiData.h"
#include "MyAIActor.generated.h"

UCLASS()
class FPSTUT_API AMyAIActor : public ACharacter
{
	GENERATED_BODY()

public:    
	AMyAIActor();

protected:
	virtual void BeginPlay() override;

	// 1. The Function that receives the answer
	UFUNCTION() 
	void HandleAICommand(const FAIGameCommand& Command);

	// 2. The Blueprint Event to trigger animations
	UFUNCTION(BlueprintImplementableEvent)
	void TriggerAnimation(const FString& ActionName);

	// 3. Helper to send a command
	UFUNCTION(BlueprintCallable)
	void SendVoiceCommand(FString Text);
};
