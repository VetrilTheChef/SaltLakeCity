// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBControllerFactory.generated.h"

/**
 * 
 */

class AIBBHUD;
class UIBBBuildController;
class UIBBBuildModel;
class UIBBBuildWidget;
class UIBBBuildEntryController;
class UIBBBuildEntryModel;
class UIBBBuildEntryWidget;
class UIBBCommandFactory;
class UIBBContextController;
class UIBBContextModel;
class UIBBContextWidget;
class UIBBContextRowWidget;
class UIBBDateTimeController;
class UIBBDateTimeModel;
class UIBBDateTimeWidget;
class UIBBDossierController;
class UIBBDossierModel;
class UIBBDossierWidget;
class UIBBDossierEntryController;
class UIBBDossierEntryModel;
class UIBBDossierEntryWidget;
class UIBBGameInstance;
class UIBBJobController;
class UIBBJobModel;
class UIBBJobWidget;
class UIBBModesController;
class UIBBModesModel;
class UIBBModesWidget;
class UIBBProgressController;
class UIBBProgressModel;
class UIBBProgressWidget;
class UIBBSelectionController;
class UIBBSelectionModel;
class UIBBSelectionWidget;
class UIBBSkillEntry;
class UIBBSkillEntryController;
class UIBBSkillEntryModel;
class UIBBSkillEntryWidget;
class UIBBSpecificationFactory;
class UIBBTitleController;
class UIBBTitleModel;
class UIBBTitleWidget;
class UIBBWidgetFactory;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBControllerFactory : public UObject
{
	GENERATED_BODY()
	
	public:
		UBBControllerFactory();

		void Initialize(const UIBBGameInstance * GameInstance, const AIBBHUD * NewHUD);

		void Finalize();

		bool NewBuildController(UIBBBuildController * & Controller, UIBBBuildWidget * View, UIBBBuildModel * Model) const;

		bool NewBuildEntryController(UIBBBuildEntryController * & Controller, UIBBBuildEntryWidget * View, UIBBBuildEntryModel * Model) const;

		bool NewContextController(UIBBContextController * & Controller, UIBBContextWidget * View, UIBBContextModel * Model) const;

		bool NewDateTimeController(UIBBDateTimeController * & Controller, UIBBDateTimeWidget * View, UIBBDateTimeModel * Model) const;

		bool NewDossierController(UIBBDossierController * & Controller, UIBBDossierWidget * View, UIBBDossierModel * Model) const;

		bool NewDossierEntryController(UIBBDossierEntryController * & Controller, UIBBDossierEntryWidget * View, UIBBDossierEntryModel * Model) const;

		bool NewJobController(UIBBJobController * & Controller, UIBBJobWidget * View, UIBBJobModel * Model) const;

		bool NewModesController(UIBBModesController * & Controller, UIBBModesWidget * View, UIBBModesModel * Model) const;

		bool NewProgressController(UIBBProgressController * & Controller, UIBBProgressWidget * View, UIBBProgressModel * Model) const;

		bool NewSelectionController(UIBBSelectionController * & Controller, UIBBSelectionWidget * View, UIBBSelectionModel * Model) const;

		bool NewSkillEntryController(UIBBSkillEntryController * & Controller, UIBBSkillEntryWidget * View, UIBBSkillEntryModel * Model) const;

		bool NewTitleController(UIBBTitleController * & Controller, UIBBTitleWidget * View, UIBBTitleModel * Model) const;
	
	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBBuildController> BuildControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBBuildEntryController> BuildEntryControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBContextController> ContextControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDateTimeController> DateTimeControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDossierController> DossierControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDossierEntryController> DossierEntryControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBJobController> JobControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBModesController> ModesControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBProgressController> ProgressControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBSelectionController> SelectionControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBSkillEntryController> SkillEntryControllerClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBTitleController> TitleControllerClass;

		UPROPERTY()
		const UIBBGameInstance * GameInstance;

		UPROPERTY()
		const AIBBHUD * HUD;
};