// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBContextRowData.h"
#include "UObject/NoExportTypes.h"
#include "BBModelFactory.generated.h"

/**
 * 
 */

class AIBBCharacter;
class AIBBGameMode;
class AIBBGameState;
class AIBBHUD;
class UIBBDossierEntry;
class UIBBBuildEntry;
class UIBBBuildModel;
class UIBBBuildWidget;
class UIBBBuildEntryModel;
class UIBBBuildEntryWidget;
class UIBBContextModel;
class UIBBContextWidget;
class UIBBContextRowWidget;
class UIBBDateTimeModel;
class UIBBDateTimeWidget;
class UIBBDossierModel;
class UIBBDossierWidget;
class UIBBDossierEntryModel;
class UIBBDossierEntryWidget;
class UIBBGameState;
class UIBBGUIModel;
class UIBBJobModel;
class UIBBJobWidget;
class UIBBModelPool;
class UIBBModesModel;
class UIBBModesWidget;
class UIBBProgressComponent;
class UIBBProgressModel;
class UIBBProgressWidget;
class UIBBSelectionModel;
class UIBBSelectionWidget;
class UIBBSkillEntry;
class UIBBSkillEntryModel;
class UIBBSkillEntryWidget;
class UIBBTitleModel;
class UIBBTitleWidget;
class UIBBWidget;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBModelFactory : public UObject
{
	GENERATED_BODY()
	
	public:
		UBBModelFactory();

		void Initialize(const AIBBGameState * GameState, AIBBGameMode * GameMode, AIBBHUD * NewHUD);

		void Finalize();

		bool NewBuildModel(UIBBBuildModel * & Model, UIBBBuildWidget * View) const;

		bool NewBuildEntryModel(UIBBBuildEntryModel * & Model, UIBBBuildEntryWidget * View, const UIBBBuildEntry * Entry) const;

		bool NewContextModel(UIBBContextModel * & Model, UIBBContextWidget * View) const;

		bool NewDateTimeModel(UIBBDateTimeModel * & Model, UIBBDateTimeWidget * View) const;
		
		bool NewDossierModel(UIBBDossierModel * & Model, UIBBDossierWidget * View, AIBBCharacter * Character) const;

		bool NewDossierEntryModel(UIBBDossierEntryModel * & Model, UIBBDossierEntryWidget * View, UIBBDossierEntry * Entry) const;

		bool NewJobModel(UIBBJobModel * & Model, UIBBJobWidget * View) const;
		
		bool NewModesModel(UIBBModesModel * & Model, UIBBModesWidget * View) const;

		bool NewProgressModel(UIBBProgressModel * & Model, UIBBProgressWidget * View, UIBBProgressComponent * Component) const;

		bool NewSelectionModel(UIBBSelectionModel * & Model, UIBBSelectionWidget * View) const;

		bool NewSkillEntryModel(UIBBSkillEntryModel * & Model, UIBBSkillEntryWidget * View, const UIBBSkillEntry * Entry) const;

		bool NewTitleModel(UIBBTitleModel * & Model, UIBBTitleWidget * View, UIBBGUIModel * ParentModel) const;
	
	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBBuildModel> BuildModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBBuildEntryModel> BuildEntryModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBContextModel> ContextModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDateTimeModel> DateTimeModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDossierModel> DossierModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDossierEntryModel> DossierEntryModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBJobModel> JobModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBModesModel> ModesModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBProgressModel> ProgressModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBSelectionModel> SelectionModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBSkillEntryModel> SkillEntryModelClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBTitleModel> TitleModelClass;

		UPROPERTY()
		AIBBGameMode * GameMode;

		UPROPERTY()
		const AIBBGameState * GameState;
		
		UPROPERTY()
		AIBBHUD * HUD;
};