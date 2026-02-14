// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Interfaces/IBBModelPool.h"
#include "BBModelPoolStub.generated.h"

UCLASS(NotBlueprintable)

class UBBModelPoolStub : public UIBBModelPool
{
	GENERATED_BODY()

	public:
		UBBModelPoolStub();

		virtual void Initialize(const UIBBGameInstance * NewGameInstance) override;

		virtual void AddBuildModel(UIBBBuildModel * NewModel) override;

		virtual bool GetBuildModel(UIBBBuildModel * & Model) const override;

		virtual int GetNumBuildModels() const;

		virtual UIBBBuildModel * GetBuildModel(int Index) const;

		virtual void AddContextModel(UIBBContextModel * NewModel) override;

		virtual bool GetContextModel(UIBBContextModel * & Model) const override;

		virtual int GetNumContextModels() const;

		virtual UIBBContextModel * GetContextModel(int Index) const;

		virtual void AddDateTimeModel(UIBBDateTimeModel * NewModel) override;

		virtual bool GetDateTimeModel(UIBBDateTimeModel * & Model) const override;

		virtual int GetNumDateTimeModels() const;

		virtual UIBBDateTimeModel * GetDateTimeModel(int Index) const;

		virtual void AddDossierModel(UIBBDossierModel * NewModel) override;

		virtual bool GetDossierModel(UIBBDossierModel * & Model, AIBBCharacter * Character) const override;

		virtual int GetNumDossierModels() const;

		virtual UIBBDossierModel * GetDossierModel(int Index) const;

		virtual void AddJobModel(UIBBJobModel * NewModel) override;

		virtual bool GetJobModel(UIBBJobModel * & Model) const override;

		virtual int GetNumJobModels() const;

		virtual UIBBJobModel * GetJobModel(int Index) const;

		virtual void AddProgressModel(UIBBProgressModel * NewModel) override;

		virtual bool GetProgressModel(UIBBProgressModel * & Model) const override;

		virtual int GetNumProgressModels() const;

		virtual void AddSelectionModel(UIBBSelectionModel * NewModel) override;

		virtual bool GetSelectionModel(UIBBSelectionModel * & Model) const override;

		virtual int GetNumSelectionModels() const;

		virtual UIBBProgressModel * GetProgressModel(int Index) const;

		virtual void AddTitleModel(UIBBTitleModel * NewModel) override;

		virtual bool GetTitleModel(UIBBTitleModel * & Model) const override;

		virtual int GetNumTitleModels() const;

		virtual UIBBTitleModel * GetTitleModel(int Index) const;

		virtual UIBBModelIterator * GetIterator(EBBWidget WidgetType) override;

		virtual UIBBGUIModel * GetModel(UIBBWidgetSpecification & Specification) override;

		void SetModel(UIBBGUIModel * NewReturnModel);

	protected:
		UPROPERTY()
		TArray<UIBBBuildModel *> BuildModels;

		UPROPERTY()
		TArray<UIBBContextModel *> ContextModels;

		UPROPERTY()
		TArray<UIBBDateTimeModel *> DateTimeModels;

		UPROPERTY()
		TArray<UIBBDossierModel *> DossierModels;

		UPROPERTY()
		TArray<UIBBJobModel *> JobModels;

		UPROPERTY()
		TArray<UIBBProgressModel *> ProgressModels;

		UPROPERTY()
		TArray<UIBBSelectionModel *> SelectionModels;

		UPROPERTY()
		TArray<UIBBTitleModel *> TitleModels;

		UPROPERTY()
		UIBBGUIModel * ReturnModel;
};