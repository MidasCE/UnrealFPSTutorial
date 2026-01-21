// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIActor.h"

#include "Core/Service/GeminiService.h"

// Sets default values
AMyAIActor::AMyAIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyAIActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyAIActor::SendVoiceCommand(FString Text)
{
	// 1. Get the Singleton Service
	if (auto* Service = GetGameInstance()->GetSubsystem<UGeminiService>())
	{
		// 2. Prepare the Callback (My Phone Number)
		FGeminiCallback Callback;
		Callback.BindDynamic(this, &AMyAIActor::HandleAICommand);

		// 3. Send
		Service->SendPrompt(Text, Callback);
	}
	//For testing TriggerAnimation("WAVE");
}

void AMyAIActor::HandleAICommand(const FAIGameCommand& Command)
{
	UE_LOG(LogTemp, Warning, TEXT("I was ordered to: %s"), *Command.command);
	TriggerAnimation(Command.command);
}
