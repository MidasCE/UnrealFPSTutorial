#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SelectionBase.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "SettingsWidget.generated.h"

class UCheckBox;
class UEditableTextBox;

UCLASS()
class FPSTUT_API USettingsWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

protected:
	void InitializeResolutionComboBox();
	void InitializeVsync();
	void InitializeFrameRate();
	void InitializeQuitButton();
	void InitializeRestartGameButton();
	void InitializeLLMSettings();

	UFUNCTION()
	void OnResolutionChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType);

	UFUNCTION()
	void OnVSyncChanged(bool InIsChecked);

	UFUNCTION()
	void OnRestartGameClicked();
	
	UFUNCTION()
	void OnQuitGameClicked();

UFUNCTION()
    void OnLLMEnableChanged(bool bIsChecked);

    UFUNCTION()
    void OnAPIKeyChanged(const FText& Text);
    
	UPROPERTY()
	TObjectPtr<UGameUserSettings> GameUserSettings;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UComboBoxString> ResolutionComboBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCheckBox> VSyncCheckBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USelectionBase> FramerateSelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USelectionBase> ShadingQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USelectionBase> GlobalIlluminationQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USelectionBase> PostProcessingQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USelectionBase> VisualEffectsQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USelectionBase> ShadowQualitySelection;

	UPROPERTY()
	TArray<FIntPoint> Resolutions;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> RestartGameButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> QuitButton;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
    TObjectPtr<UCheckBox> LLMEnableCheckBox;
    
    UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
    TObjectPtr<UEditableTextBox> APIKeyTextBox;
};
