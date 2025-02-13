// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/BBContextRowData.h"
#include "IBBWidgetFactory.generated.h"

/**
 * 
 */

Expose_TNameOf(UIBBWidgetFactory)

class AIBBCharacter;
class AIBBGameMode;
class AIBBGameState;
class AIBBHUD;
class APlayerController;
class UIBBDossierEntry;
class UIBBBaseAttributeSet;
class UIBBBuildEntry;
class UIBBBuildWidget;
class UIBBBuildEntryWidget;
class UIBBCommandFactory;
class UIBBContextWidget;
class UIBBContextRowWidget;
class UIBBDateTimeWidget;
class UIBBDossierWidget;
class UIBBDossierEntryWidget;
class UIBBGameInstance;
class UIBBGUIModel;
class UIBBJobWidget;
class UIBBModelPool;
class UIBBModesWidget;
class UIBBProgressComponent;
class UIBBProgressWidget;
class UIBBSelectionWidget;
class UIBBSpecificationFactory;
class UIBBTargetedWidgetSpecification;
class UIBBTitleWidget;
class UIBBWidget;
class UIBBWidgetSpecification;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBWidgetFactory : public UObject
{
	GENERATED_BODY()
	
	public:
		UIBBWidgetFactory() : Super() { };

		virtual void Initialize(const UIBBGameInstance * NewGameInstance, const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, AIBBHUD * NewHUD, APlayerController * NewPlayerController) PURE_VIRTUAL(UIBBWidgetFactory::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBWidgetFactory::Finalize, );

		virtual void InjectSpecificationFactory(UIBBSpecificationFactory * NewSpecificationFactory) PURE_VIRTUAL(UIBBWidgetFactory::InjectSpecificationFactory, );

		virtual bool NewBuildWidget(UIBBBuildWidget * & Widget) const PURE_VIRTUAL(UIBBWidgetFactory::NewBuildWidget, return false; );

		virtual bool NewBuildEntryWidget(UIBBBuildEntryWidget * & Widget, const UIBBBuildEntry * Entry) const PURE_VIRTUAL(UIBBWidgetFactory::NewBuildEntryWidget, return false; );

		virtual bool NewContextWidget(UIBBContextWidget * & Widget) const PURE_VIRTUAL(UIBBWidgetFactory::NewContextWidget, return false; );

		virtual bool NewContextRowWidget(UIBBContextRowWidget * & Widget, FBBContextRowData NewRowData) const PURE_VIRTUAL(UIBBWidgetFactory::NewContextRowWidget, return false; );

		virtual bool NewDateTimeWidget(UIBBDateTimeWidget * & Widget) const PURE_VIRTUAL(UIBBWidgetFactory::NewDateTimeWidget, return false; );

		virtual bool NewDossierWidget(UIBBDossierWidget * & Widget, AIBBCharacter * Character) const PURE_VIRTUAL(UIBBWidgetFactory::NewDossierWidget, return false; );

		virtual bool NewDossierEntryWidget(UIBBDossierEntryWidget * & Widget, UIBBDossierEntry * Entry) const PURE_VIRTUAL(UIBBWidgetFactory::NewDossierEntryWidget, return false; );

		virtual bool NewJobWidget(UIBBJobWidget * & Widget) const PURE_VIRTUAL(UIBBWidgetFactory::NewJobWidget, return false; );
		
		virtual bool NewModesWidget(UIBBModesWidget * & Widget) const PURE_VIRTUAL(UIBBWidgetFactory::NewModesWidget, return false; );

		virtual bool NewProgressWidget(UIBBProgressWidget * & Widget, UIBBProgressComponent * Component) const PURE_VIRTUAL(UIBBWidgetFactory::NewProgressWidget, return false; );

		virtual bool NewSelectionWidget(UIBBSelectionWidget * & Widget) const PURE_VIRTUAL(UIBBWidgetFactory::NewSelectionWidget, return false; );

		virtual bool NewTitleWidget(UIBBTitleWidget * & Widget, UIBBGUIModel * ParentModel) const PURE_VIRTUAL(UIBBWidgetFactory::NewTitleWidget, return false; );
};