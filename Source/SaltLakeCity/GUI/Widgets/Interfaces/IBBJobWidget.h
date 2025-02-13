// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBJobWidget.generated.h"

/**
 * 
 */

class UIBBCommand;
class UIBBTitleWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIBBJobWidget_JobSet, EBBJob, Job);

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBJobWidget : public UIBBWidget
{
	GENERATED_BODY()

	public:
		UIBBJobWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeOnInitialized() override { Super::NativeOnInitialized(); };

		virtual EBBWidget GetType() const override PURE_VIRTUAL(UIBBJobWidget::GetType, return EBBWidget::None; );

		virtual void SetDisplayName(FText NewCharacterName) PURE_VIRTUAL(UIBBJobWidget::SetCharacterName, );

		virtual void AddJob(EBBJob NewJob, FText NewJobName, FText NewJobTooltip) PURE_VIRTUAL(UIBBJobWidget::AddJob, );

		virtual void SetJob(EBBJob Job) PURE_VIRTUAL(UIBBJobWidget::SetJob, );

		virtual void ClearJobs() PURE_VIRTUAL(UIBBJobWidget::ClearJobs, );

		virtual UIBBTitleWidget * & GetTitle() PURE_VIRTUAL(UIBBJobWidget::GetTitle, return Title; );

		virtual void SetAcceptCommand(UIBBCommand * NewAcceptCommand) PURE_VIRTUAL(UIBBJobWidget::SetAcceptCommand, );

		virtual void SetCancelCommand(UIBBCommand * NewCancelCommand) PURE_VIRTUAL(UIBBJobWidget::SetCancelCommand, );

		DECLARE_EVENT_OneParam(UIBBJobWidget, FBBJobUpdate, const EBBJob);

		FBBJobUpdate & OnJobUpdate() { return UpdateJob; };

	protected:
		UPROPERTY(meta = (BindWidget))
		UIBBTitleWidget * Title;

		FBBJobUpdate UpdateJob;
};