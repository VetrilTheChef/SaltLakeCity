// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBTargetedModel.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBJobModel.generated.h"

/**
 * 
 */

class AIBBHUD;
class UDataTable;
class UIBBJobWidget;
class UIBBWorkComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBJobModel : public UIBBTargetedModel
{
	GENERATED_BODY()

	public:
		UIBBJobModel() : Super() { };

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override PURE_VIRTUAL(UIBBJobModel::GetWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBJobModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBJobModel::GetWidgetSpecification, return nullptr; );

		virtual UDataTable * GetDataTable() const PURE_VIRTUAL(UIBBJobModel::GetDataTable, return nullptr; );

		virtual void Initialize(UIBBJobWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table) PURE_VIRTUAL(UIBBJobModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBJobModel::Finalize, );

		virtual int GetNumJobs() const PURE_VIRTUAL(UIBBJobModel::GetNumJobs, return 0; );

		virtual EBBJob GetJob(int Index) const PURE_VIRTUAL(UIBBJobModel::GetJob, return EBBJob::None; );

		virtual const FText GetJobName(int Index) const PURE_VIRTUAL(UIBBJobModel::GetJobName, return FText::FromString(""); );

		virtual const FText GetJobTooltip(int Index) const PURE_VIRTUAL(UIBBJobModel::GetJobTooltip, return FText::FromString(""); );

		virtual UIBBWorkComponent * GetWorkComponent() const PURE_VIRTUAL(UIBBJobModel::GetWorkComponent, return nullptr; );

		virtual const FText GetDisplayName() const PURE_VIRTUAL(UIBBJobModel::GetDisplayName, return FText::FromString(""); );

		virtual EBBJob GetCurrentJob() const PURE_VIRTUAL(UIBBJobModel::GetJob, return EBBJob::None; );
		
		DECLARE_EVENT(UIBBJobModel, FBBConsumerUpdate);

		FBBConsumerUpdate & OnConsumerUpdate() { return ConsumerUpdate; };

	protected:
		FBBConsumerUpdate ConsumerUpdate;
};