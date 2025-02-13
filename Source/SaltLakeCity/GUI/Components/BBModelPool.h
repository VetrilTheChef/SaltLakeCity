// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Includes/BBGUIModelContainers.h"
#include "GUI/Components/Interfaces/IBBModelPool.h"
#include "GUI/Includes/BBContextEnum.h"
#include "BBModelPool.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBModelPool : public UIBBModelPool
{
	GENERATED_BODY()

	public:
		UBBModelPool();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void Initialize(UIBBGameInstance * NewGameInstance) override;

		virtual void Finalize() override;

		virtual void AddBuildModel(UIBBBuildModel * NewModel) override;

		virtual bool GetBuildModel(UIBBBuildModel * & Model) const override;

		virtual void AddBuildEntryModel(UIBBBuildEntryModel * NewModel) override;

		virtual bool GetBuildEntryModel(UIBBBuildEntryModel * & NewModel) override;

		virtual void AddContextModel(UIBBContextModel * NewModel) override;

		virtual bool GetContextModel(UIBBContextModel * & Model) const override;

		virtual void AddDateTimeModel(UIBBDateTimeModel * NewModel) override;

		virtual bool GetDateTimeModel(UIBBDateTimeModel * & Model) const override;

		virtual void AddDossierModel(UIBBDossierModel * NewModel) override;

		virtual bool GetDossierModel(UIBBDossierModel * & Model, AIBBCharacter * Character) const override;

		virtual void AddDossierEntryModel(UIBBDossierEntryModel * NewModel) override;

		virtual bool GetDossierEntryModel(UIBBDossierEntryModel * & NewModel) override;

		virtual void AddJobModel(UIBBJobModel * NewModel) override;

		virtual bool GetJobModel(UIBBJobModel * & Model) const override;

		virtual void AddModesModel(UIBBModesModel * NewModel) override;

		virtual bool GetModesModel(UIBBModesModel * & Model) const override;

		virtual void AddProgressModel(UIBBProgressModel * NewModel) override;

		virtual bool GetProgressModel(UIBBProgressModel * & Model) const override;

		virtual void AddSelectionModel(UIBBSelectionModel * NewModel) override;

		virtual bool GetSelectionModel(UIBBSelectionModel * & Model) const override;

		virtual void AddSkillEntryModel(UIBBSkillEntryModel * NewModel) override;

		virtual bool GetSkillEntryModel(UIBBSkillEntryModel * & NewModel) override;

		virtual void AddTitleModel(UIBBTitleModel * NewModel) override;

		virtual bool GetTitleModel(UIBBTitleModel * & Model) const override;

		virtual const UIBBModelIterator * GetIterator(EBBWidget WidgetType) override;

		virtual UIBBGUIModel * GetModel(UIBBWidgetSpecification & Specification) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Iterator")
		TSoftClassPtr<UIBBModelIterator> ModelIteratorClass;

		UPROPERTY()
		TMap<EBBWidget, UIBBGUIModelContainer *> ModelsMap;
};