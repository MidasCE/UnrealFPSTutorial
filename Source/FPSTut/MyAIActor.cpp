// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIActor.h"

#include "Core/Service/GeminiService.h"

// Sets default values
AMyAIActor::AMyAIActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyAIActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyAIActor::SendVoiceCommand(FString Text)
{
	if (UGeminiService* Service = GetGameInstance()->GetSubsystem<UGeminiService>())
	{
		FGeminiCallback Callback;
		Callback.BindDynamic(this, &AMyAIActor::HandleAICommand);

		if (!Service->bIsLLMEnabled)
		{
			UE_LOG(LogTemp, Warning, TEXT("LLM is not enable, I will do CROUCH to avoid enemy."));
			TriggerAnimation("CROUCH");
			return;
		}
		Service->SendPrompt(Text, Callback);
	}
}



void AMyAIActor::HandleAICommand(const FAIGameCommand& Command)
{
	UE_LOG(LogTemp, Warning, TEXT("I was ordered to: %s"), *Command.command);
	TriggerAnimation(Command.command);
}
