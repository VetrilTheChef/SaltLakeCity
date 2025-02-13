// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "UObject/NoExportTypes.h"
#include "IBBCommandFactory.generated.h"

/**
 * 
 */

Expose_TNameOf(UIBBCommandFactory)

class AIBBTargetingActor;
class IBBContextualizable;
class IBBSelectable;
class UIBBAbilityData;
class UIBBAttachWidgetCommand;
class UIBBBuildData;
class UIBBCloseWidgetCommand;
class UIBBCompositeCommand;
class UIBBDetachWidgetCommand;
class UIBBGameInstance;
class UIBBGameModeCommand;
class UIBBOrderBuildCommand;
class UIBBOpenWidgetCommand;
class UIBBPauseCommand;
class UIBBSelectCommand;
class UIBBSetContextCommand;
class UIBBSetJobCommand;
class UIBBSpeedCommand;
class UIBBWidgetComponent;
class UIBBWidgetSpecification;
class UIBBWorkComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBCommandFactory : public UObject
{
	GENERATED_BODY()

	public:
		UIBBCommandFactory() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); };

		virtual void BeginDestroy() override { Super::BeginDestroy(); };

		virtual void Initialize(UIBBGameInstance * NewGameInstance) PURE_VIRTUAL(UIBBCommandFactory::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(Finalize, );

		virtual bool NewOrderBuildCommand(UIBBOrderBuildCommand * & Command, UObject * Outer, const TSoftClassPtr<UIBBBuildData> BuildDataClass, const TSoftClassPtr<AIBBTargetingActor> TargetingClass, const TArray<FBBBuildablePtr> BuildableClasses, float Price, float Time) const PURE_VIRTUAL(UIBBCommandFactory::NewOrderBuildCommand, return false; );

		virtual bool NewPauseCommand(UIBBPauseCommand * & Command, UObject * Outer) const PURE_VIRTUAL(UIBBCommandFactory::NewPauseCommand, return false; );

		virtual bool NewSpeedCommand(UIBBSpeedCommand * & Command, UObject * Outer, float TimeDilation) const PURE_VIRTUAL(UIBBCommandFactory::NewSpeedCommand, return false; );
		
		virtual bool NewOpenWidgetCommand(UIBBOpenWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, bool PopUp) const PURE_VIRTUAL(UIBBCommandFactory::NewOpenWidgetCommand, return false; );

		virtual bool NewCloseWidgetCommand(UIBBCloseWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification) const PURE_VIRTUAL(UIBBCommandFactory::NewCloseWidgetCommand, return false; );

		virtual bool NewAttachWidgetCommand(UIBBAttachWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, UIBBWidgetComponent * Component) const PURE_VIRTUAL(UIBBCommandFactory::NewAttachWidgetCommand, return false; );

		virtual bool NewDetachWidgetCommand(UIBBDetachWidgetCommand * & Command, UObject * Outer, UIBBWidgetComponent * Component) const PURE_VIRTUAL(UIBBCommandFactory::NewDetachWidgetCommand, return false; );

		virtual bool NewGameModeCommand(UIBBGameModeCommand * & Command, UObject * Outer, EBBGameMode ActiveGameMode) const PURE_VIRTUAL(UIBBCommandFactory::NewGameModeCommand, return false; );
		
		virtual bool NewSelectCommand(UIBBSelectCommand * & Command, UObject * Outer, TScriptInterface<IBBSelectable> Selectable) const PURE_VIRTUAL(UIBBCommandFactory::NewSelectCommand, return false; );

		virtual bool NewSetContextCommand(UIBBSetContextCommand * & Command, UObject * Outer, TScriptInterface<IBBContextualizable> Contextualizable) const PURE_VIRTUAL(UIBBCommandFactory::NewSetContextCommand, return false; );

		virtual bool NewSetJobCommand(UIBBSetJobCommand * & Command, UObject * Outer, UIBBWorkComponent * WorkComponent, EBBJob Job) const PURE_VIRTUAL(UIBBCommandFactory::NewSetJobCommand, return false; );

		virtual bool NewCompositeCommand(UIBBCompositeCommand * & Command, UObject * Outer) const PURE_VIRTUAL(UIBBCommandFactory::NewCompositeCommand, return false; );
};