// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "BBJobWidget.generated.h"

/**
 * 
 */

class UComboBoxString;
class UIBBButton;
class UIBBCommand;
class UIBBJobController;
class UIBBTitleWidget;
class UTextBlock;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBJobWidget : public UIBBJobWidget
{
	GENERATED_BODY()

	public:
		UBBJobWidget(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void BeginDestroy() override;

		virtual EBBWidget GetType() const override;

		virtual void SetDisplayName(FText NewCharacterName) override;

		virtual void AddJob(EBBJob NewJob, FText NewJobName, FText NewJobTooltip) override;

		virtual void ClearJobs() override;

		virtual void SetJob(EBBJob Job) override;

		virtual UIBBTitleWidget * & GetTitle() override;

		virtual void SetAcceptCommand(UIBBCommand * NewAcceptCommand) override;

		virtual void SetCancelCommand(UIBBCommand * NewCancelCommand) override;

	protected:
		UPROPERTY(meta = (BindWidget))
		UTextBlock * NameText;

		UPROPERTY(meta = (BindWidget))
		UComboBoxString * JobComboBox;

		UPROPERTY(meta = (BindWidget))
		UIBBButton * AcceptButton;

		UPROPERTY(meta = (BindWidget))
		UIBBButton * CancelButton;

		UPROPERTY()
		TMap<EBBJob, FString> Jobs;

		void InitializeComboBox();

		void DestroyTitle();

		UFUNCTION()
		void OnJobSelected(FString SelectedItem, ESelectInfo::Type SelectionType);
};