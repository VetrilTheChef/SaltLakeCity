// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBJobRow.h"
#include "GUI/Models/Interfaces/IBBJobModel.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "BBJobModel.generated.h"

/**
 * 
 */

class UIBBWorkComponent;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBJobModel : public UIBBJobModel
{
	GENERATED_BODY()

	public:
		UBBJobModel();

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;
		
		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual UDataTable * GetDataTable() const override;

		virtual void Initialize(UIBBJobWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table) override;

		virtual void Finalize() override;

		virtual int GetNumJobs() const override;

		virtual EBBJob GetJob(int Index) const override;

		virtual const FText GetJobName(int Index) const override;

		virtual const FText GetJobTooltip(int Index) const override;

		virtual UIBBWorkComponent * GetWorkComponent() const override;

		virtual const FText GetDisplayName() const override;

		virtual EBBJob GetCurrentJob() const override;

	protected:
		UPROPERTY(Category = "Data Table", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> TableAsset;

		UPROPERTY()
		UIBBJobWidget * View;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWorkComponent * Component;

		TArray<FBBJobRow> Jobs;

		void InitializeView(UIBBJobWidget * NewView);

		void InitializeJobs(UDataTable * Table);

		void InitializeHUD(AIBBHUD * NewHUD);
		
		void InitializeComponent(UIBBWorkComponent * NewWorkComponent);

		void FinalizeView();

		void FinalizeJobs();

		void FinalizeHUD();

		void FinalizeComponent();

		UFUNCTION()
		void UpdateComponent(UIBBWorkComponent * NewWorkComponent);
};