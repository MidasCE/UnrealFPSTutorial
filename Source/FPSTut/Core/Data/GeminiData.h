#pragma once

#include "CoreMinimal.h"
#include "GeminiData.generated.h"

USTRUCT(BlueprintType)
struct FAIGameCommand
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString command; // e.g., "JUMP"

	UPROPERTY(BlueprintReadOnly)
	float intensity = 1.0f;
};

// The Internal API format
USTRUCT()
struct FGeminiPart { GENERATED_BODY() UPROPERTY() FString text; };

USTRUCT()
struct FGeminiContent { GENERATED_BODY() UPROPERTY() TArray<FGeminiPart> parts; };

USTRUCT()
struct FGeminiConfig { GENERATED_BODY() UPROPERTY() FString responseMimeType = "application/json"; };

USTRUCT()
struct FGeminiRequest
{
	GENERATED_BODY()
	UPROPERTY() FGeminiContent system_instruction;
	UPROPERTY() TArray<FGeminiContent> contents;
	UPROPERTY() FGeminiConfig generationConfig;
};
