// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "BBJobWidgetStub.generated.h"

/**
 * 
 */

class UIBBCommand;
class UIBBJobController;
class UIBBTitleWidget;

USTRUCT(BlueprintType)

struct FBBJob
{
	GENERATED_BODY()

	public:
		UPROPERTY()
		EBBJob Job;

		UPROPERTY()
		FText Name;

		UPROPERTY()
		FText Tooltip;

		FBBJob()
		{
			Job = EBBJob::None;
			Name = FText::FromString("");
			Tooltip = FText::FromString("");
		}

		FBBJob(EBBJob NewJob, FText NewName, FText NewTooltip)
		{
			Job = NewJob;
			Name = NewName;
			Tooltip = NewTooltip;
		}

		~FBBJob()
		{
			Job = EBBJob::None;
			Name = FText::FromString("");
			Tooltip = FText::FromString("");
		}
	};

UCLASS(NotBlueprintable)

class UBBJobWidgetStub : public UIBBJobWidget
{
	GENERATED_BODY()

	public:
		UBBJobWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void BeginDestroy() override;

		virtual EBBWidget GetType() const override;

		FText GetDisplayName();

		virtual void SetDisplayName(FText NewDisplayName) override;

		virtual void AddJob(EBBJob NewJob, FText NewJobName, FText NewJobTooltip) override;

		int GetNumJobs();

		EBBJob GetJob(int Index);

		FText GetJobName(int Index);

		FText GetJobTooltip(int Index);

		virtual void ClearJobs() override;

		EBBJob GetJob();

		virtual void SetJob(EBBJob Job) override;

		FText GetSelectedJobName();

		virtual UIBBTitleWidget * & GetTitle() override;

		UIBBCommand * GetAcceptCommand();

		virtual void SetAcceptCommand(UIBBCommand * NewAcceptCommand) override;

		UIBBCommand * GetCancelCommand();

		virtual void SetCancelCommand(UIBBCommand * NewCancelCommand) override;

	protected:
		UPROPERTY()
		FText DisplayName;

		EBBJob SelectedJob;

		TArray<FBBJob> Jobs;

		UPROPERTY()
		UIBBCommand * AcceptCommand;

		UPROPERTY()
		UIBBCommand * CancelCommand;
};