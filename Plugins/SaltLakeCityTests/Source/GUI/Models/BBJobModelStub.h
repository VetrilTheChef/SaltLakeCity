// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBJobRow.h"
#include "GUI/Models/Interfaces/IBBJobModel.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "BBJobModelStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBJobModelStub : public UIBBJobModel
{
	GENERATED_BODY()

	public:
		UBBJobModelStub();

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewTarget);

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;
		
		void SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

		virtual UDataTable * GetDataTable() const override;

		virtual void Initialize(UIBBJobWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table) override;

		virtual void Finalize() override;

		void AddJob(FText NewName, FText NewTooltip, EBBJob NewJob);

		virtual int GetNumJobs() const override;

		virtual EBBJob GetJob(int Index) const override;

		virtual const FText GetJobName(int Index) const override;

		virtual const FText GetJobTooltip(int Index) const override;

		virtual UIBBWorkComponent * GetWorkComponent() const override;

		virtual void SetWorkComponent(UIBBWorkComponent * NewWorkComponent);

		virtual const FText GetDisplayName() const override;

		void SetDisplayName(FText NewDisplayName);

		virtual EBBJob GetCurrentJob() const override;

		void SetCurrentJob(EBBJob NewCurrentJob);

		const FText FindJobName(EBBJob JobType);

		void BroadcastConsumerUpdate(UIBBWorkComponent * NewWorkComponent);

	protected:
		UPROPERTY()
		UIBBJobWidget * View;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWorkComponent * WorkComponent;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> Target;

		EBBJob CurrentJob;

		TArray<FBBJobRow> Jobs;

		FText DisplayName;

		UFUNCTION()
		void UpdateConsumer(UIBBWorkComponent * NewWorkComponent);
};