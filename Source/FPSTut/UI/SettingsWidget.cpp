#include "SettingsWidget.h"

#include "FrameRate.h"
#include "Components/CheckBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"

namespace
{
	constexpr EFramerate FramerateOptions[] = {
		EFramerate::FPS_30,
		EFramerate::FPS_60,
		EFramerate::FPS_120,
		EFramerate::FPS_Uncapped,
	};

	typedef int32(UGameUserSettings::*GetFunc)() const;
	typedef void(UGameUserSettings::*SetFunc)(int);
	struct FSelectionElement
	{
		USelectionBase* Widget;

		GetFunc GetFunc;
		SetFunc SetFunc;
	};
}

void USettingsWidget::NativeConstruct()
{
	GameUserSettings = UGameUserSettings::GetGameUserSettings();

	InitializeResolutionComboBox();
	InitializeVsync();
	InitializeFrameRate();

	InitializeQuitButton();	

	const FSelectionElement SelectionElement[] = {
		{ShadingQualitySelection, &UGameUserSettings::GetShadingQuality, &UGameUserSettings::SetShadingQuality },
		{PostProcessingQualitySelection, &UGameUserSettings::GetPostProcessingQuality, &UGameUserSettings::SetPostProcessingQuality },
		{VisualEffectsQualitySelection, &UGameUserSettings::GetVisualEffectQuality, &UGameUserSettings::SetVisualEffectQuality },
		{ShadowQualitySelection, &UGameUserSettings::GetShadingQuality, &UGameUserSettings::SetShadingQuality },
	};

	for (const auto& [Widget, GetFunc, SetFunc] : SelectionElement)
	{
	    if (!Widget) continue;
		const auto CurrentSelection = std::invoke(GetFunc, GameUserSettings);
		Widget->SetCurrentSelection(CurrentSelection);
		Widget->OnSelectionChange.BindLambda([this, SetFunc](int InSelection)
		{
			std::invoke(SetFunc, GameUserSettings, InSelection);
			GameUserSettings->ApplySettings(false);
		});
	}
}

UWidget* USettingsWidget::NativeGetDesiredFocusTarget() const
{
	return ResolutionComboBox;
}

void USettingsWidget::InitializeResolutionComboBox()
{
	if (!ResolutionComboBox) 
	{
		UE_LOG(LogTemp, Error, TEXT("Resolutions is missing from the WBP!"));
		return;
	}
	
	Resolutions.Reset();

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	ResolutionComboBox->ClearOptions();

	for (const auto& Resolution : Resolutions)
	{
		const auto ResolutionString = FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y);
		ResolutionComboBox->AddOption(ResolutionString);
	}

	//find current resolution
	const auto CurrentResolution = GameUserSettings->GetScreenResolution();
	int32 SelectedIndex = Resolutions.IndexOfByPredicate([CurrentResolution](const FIntPoint& InResolition )
	{
		return InResolition == CurrentResolution;
	});

	// CRASH FIX: Handle the case where the current resolution isn't in the list
	if (SelectedIndex == INDEX_NONE)
	{
		// Optional: Add the custom resolution to the list so it displays correctly
		const auto CustomResString = FString::Printf(TEXT("%dx%d (Windowed)"), CurrentResolution.X, CurrentResolution.Y);
		ResolutionComboBox->AddOption(CustomResString);
		Resolutions.Add(CurrentResolution); // Keep the parallel array in sync
        
		// Select this new last entry
		SelectedIndex = Resolutions.Num() - 1;
	}
	
	ResolutionComboBox->SetSelectedIndex(SelectedIndex);

	//listen to changes
	ResolutionComboBox->OnSelectionChanged.Clear();
	ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &USettingsWidget::OnResolutionChanged);
}

void USettingsWidget::InitializeQuitButton()
{
	if (!QuitButton)
	{
		UE_LOG(LogTemp, Error, TEXT("QuitButton is missing from the WBP!"));
		return;
	}

	QuitButton->OnClicked.Clear();
	QuitButton->OnClicked.AddDynamic(this, &USettingsWidget::OnQuitGameClicked);
}

void USettingsWidget::InitializeVsync()
{
	if (!VSyncCheckBox) 
	{
		UE_LOG(LogTemp, Error, TEXT("VSyncCheckBox is missing from the WBP!"));
		return;
	}
	
	VSyncCheckBox->SetIsChecked(GameUserSettings->IsVSyncEnabled());
	VSyncCheckBox->OnCheckStateChanged.Clear();
	VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::OnVSyncChanged);
}

void USettingsWidget::InitializeFrameRate()
{
	if (!FramerateSelection) 
	{
		UE_LOG(LogTemp, Error, TEXT("FramerateSelection is missing from the WBP!"));
		return;
	}
	
	FramerateSelection->Clear();

	int FramerateOptionIndex = 0;
	
	const auto CurrentFramerate = GameUserSettings->GetFrameRateLimit();
	for (const auto& Framerate: FramerateOptions)
	{
		FramerateSelection->AddOption({
			FText::FromString(FFramerateUtils::EnumToString(Framerate))
		});

		if (CurrentFramerate == FFramerateUtils::EnumToValue(Framerate))
		{
			FramerateSelection->SetCurrentSelection(FramerateOptionIndex);
		}
		FramerateOptionIndex++;
	}

	FramerateSelection->OnSelectionChange.BindLambda([this](const int InSelection)
	{
		GameUserSettings->SetFrameRateLimit(FFramerateUtils::EnumToValue(
			FramerateOptions[InSelection]
		));
		GameUserSettings->ApplySettings(false);
	});
}


void USettingsWidget::OnResolutionChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType)
{
	const auto SelectedResolution = Resolutions[ResolutionComboBox->GetSelectedIndex()];
	GameUserSettings->SetScreenResolution(SelectedResolution);
	GameUserSettings->ApplySettings(false);
}

void USettingsWidget::OnVSyncChanged(bool InIsChecked)
{
	GameUserSettings->SetVSyncEnabled(InIsChecked);
	GameUserSettings->ApplySettings(false);
}

void USettingsWidget::OnQuitGameClicked()
{
	// This function handles the actual quitting.
	// GetOwningPlayer() ensures we quit the specific player controller's session
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
