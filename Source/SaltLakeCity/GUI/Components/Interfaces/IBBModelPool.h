// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "IBBModelPool.generated.h"

class AIBBCharacter;
class IBBWidgetTarget;
class UIBBBuildModel;
class UIBBBuildEntryModel;
class UIBBContextModel;
class UIBBDateTimeModel;
class UIBBDossierModel;
class UIBBDossierEntryModel;
class UIBBGameInstance;
class UIBBGUIModel;
class UIBBJobModel;
class UIBBModesModel;
class UIBBModelIterator;
class UIBBProgressModel;
class UIBBSelectionModel;
class UIBBTitleModel;
class UIBBWidgetSpecification;
class UTexture2D;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBModelPool : public UObject
{
	GENERATED_BODY()

	public:
		UIBBModelPool() : Super() { };

		virtual void Initialize(const UIBBGameInstance * NewGameInstance)
			PURE_VIRTUAL(UIBBModelPool::Initialize, );

		virtual void Finalize()
			PURE_VIRTUAL(UIBBModelPool::Finalize, );

		virtual void AddBuildModel(UIBBBuildModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddBuildModel, );

		virtual bool GetBuildModel(UIBBBuildModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetBuildModel, return false; );

		virtual void AddBuildEntryModel(UIBBBuildEntryModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddBuildEntryModel, );

		virtual bool GetBuildEntryModel(UIBBBuildEntryModel * & NewModel)
			PURE_VIRTUAL(UIBBModelPool::GetBuildEntryModel, return false; );

		virtual void AddContextModel(UIBBContextModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddContextModel, );

		virtual bool GetContextModel(UIBBContextModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetContextModel, return false; );

		virtual void AddDateTimeModel(UIBBDateTimeModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddDateTimeModel, );

		virtual bool GetDateTimeModel(UIBBDateTimeModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetDateTimeModel, return false; );

		virtual void AddDossierModel(UIBBDossierModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddDossierModel, );

		virtual bool GetDossierModel(UIBBDossierModel * & Model, AIBBCharacter * Character) const
			PURE_VIRTUAL(UIBBModelPool::GetDossierModel, return false; );

		virtual void AddDossierEntryModel(UIBBDossierEntryModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddDossierEntryModel, );

		virtual bool GetDossierEntryModel(UIBBDossierEntryModel * & NewModel)
			PURE_VIRTUAL(UIBBModelPool::GetDossierEntryModel, return false; );

		virtual void AddJobModel(UIBBJobModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddJobModel, );

		virtual bool GetJobModel(UIBBJobModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetJobModel, return false; );
		
		virtual void AddModesModel(UIBBModesModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddModesModel, );

		virtual bool GetModesModel(UIBBModesModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetModesModel, return false; );

		virtual void AddProgressModel(UIBBProgressModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddProgressModel, );

		virtual bool GetProgressModel(UIBBProgressModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetProgressModel, return false; );

		virtual void AddSelectionModel(UIBBSelectionModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddSelectionModel, );

		virtual bool GetSelectionModel(UIBBSelectionModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetSelectionModel, return false; );

		virtual void AddTitleModel(UIBBTitleModel * NewModel)
			PURE_VIRTUAL(UIBBModelPool::AddTitleModel, );

		virtual bool GetTitleModel(UIBBTitleModel * & Model) const
			PURE_VIRTUAL(UIBBModelPool::GetTitleModel, return false; );

		virtual const UIBBModelIterator * GetIterator(EBBWidget WidgetType)
			PURE_VIRTUAL(UIBBModelPool::GetIterator, return nullptr; );

		virtual UIBBGUIModel * GetModel(UIBBWidgetSpecification & Specification)
			PURE_VIRTUAL(UIBBModelPool::GetModel, return nullptr; );
};