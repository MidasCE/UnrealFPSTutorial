#pragma once

UENUM(BlueprintType)
enum class EFramerate : uint8
{
   FPS_30 UMETA(Displayname="30 FPS"),
   FPS_60 UMETA(Displayname="60 FPS"),
   FPS_120 UMETA(Displayname="120 FPS"),
   FPS_Uncapped UMETA(Displayname="Uncapped"),
};

class FFramerateUtils
{
public:
   static int EnumToValue(const EFramerate& InFramerate)
   {
      switch (InFramerate)
      {
         case EFramerate::FPS_30:
            return 30;
         case EFramerate::FPS_60:
            return 60;
         case EFramerate::FPS_120:
            return 120;
         default:
            return 0;
      }
   }
   
   static FString EnumToString(const EFramerate& InFramerate)
   {
      const auto Value = EnumToValue(InFramerate);
      return Value > 0
         ? FString::Printf(TEXT("%d FPS"), Value)
         :FString::Printf(TEXT("Uncapped"));
   }
};