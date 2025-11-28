#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonTextBlock.h"
#include "SelectionOption.h"
#include "SelectionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FPSTUT_API USelectionBase : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	USelectionBase();
	virtual void NativeConstruct() override;

	void Clear();
	void AddOption(const  FSelectionOption& Inoption);
	void SetCurrentSelection(int InIndex);
	
	UFUNCTION(BlueprintCallable)
	void SelectPrevious();

	UFUNCTION(BlueprintCallable)
	void SelectNext();

	DECLARE_DELEGATE_OneParam(FOnSelectionChange, int)
	FOnSelectionChange OnSelectionChange;
protected:
	UFUNCTION()
	UWidget* OnNavigation(EUINavigation InNavigation);

	void UpdateCurrentSelection();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSelectionOption> Options;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> LabelText;

	int CurrentSelection;
};
