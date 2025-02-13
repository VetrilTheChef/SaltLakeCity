// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBJobController.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "BBJobController.generated.h"

/**
 * 
 */
class UIBBSetJobCommand;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBJobController : public UIBBJobController
{
	GENERATED_BODY()

	public:
		UBBJobController();

		virtual void Initialize(UIBBJobWidget * JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory * WidgetFactory, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBJobModel * Model;

		UPROPERTY()
		UIBBJobWidget * View;

		UPROPERTY()
		UIBBSetJobCommand * SetJobCommand;

		void InitializeModel(UIBBJobModel * JobModel);

		void FinalizeModel();

		void InitializeView(UIBBJobWidget * JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory * WidgetFactory, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory);

		void FinalizeView();

		void CreateTitle(UIBBJobWidget & JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory & WidgetFactory);

		void DestroyTitle(UIBBJobWidget & JobView);

		void CreateCommands(UIBBJobWidget & JobView, UIBBJobModel & Model, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory & CommandFactory);

		void DestroyCommands(UIBBJobWidget & JobView);

		void AddJobs(UIBBJobWidget & JobView, UIBBJobModel & JobModel);

		void ClearJobs(UIBBJobWidget & JobView);

		UFUNCTION()
		void UpdateConsumer();

		UFUNCTION()
		void SetJob(EBBJob Job);
};