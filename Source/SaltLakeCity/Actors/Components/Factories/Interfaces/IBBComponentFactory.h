// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBComponentFactory.generated.h"

/**
 * 
 */

Expose_TNameOf(UIBBComponentFactory)

class AActor;
class AIBBAIController;
class AIBBHUD;
class AIBBPlayerController;
class IBBContextualizable;
class IBBHighlightable;
class IBBProgressable;
class IBBSelectable;
class IBBWorkable;
class UIBBAIAbilityComponent;
class UIBBContextComponent;
class UIBBDecalComponent;
class UIBBPlayerAbilityComponent;
class UIBBProgressComponent;
class UIBBSelectionComponent;
class UIBBWidgetComponent;
class UIBBWorkComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBComponentFactory : public UObject
{
	GENERATED_BODY()
	
	public:
		UIBBComponentFactory() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); };

		virtual void BeginDestroy() override { Super::BeginDestroy(); };

		virtual void Initialize(AIBBHUD * NewHUD) PURE_VIRTUAL(UIBBComponentFactory::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBComponentFactory::Finalize, );

		virtual bool NewAIAbilityComponent(UIBBAIAbilityComponent * & Component, AIBBAIController * Owner) const PURE_VIRTUAL(UIBBComponentFactory::NewAIAbilityComponent, return false; );

		virtual bool NewContextComponent(UIBBContextComponent * & Component, TScriptInterface<IBBContextualizable> Owner) const PURE_VIRTUAL(UIBBComponentFactory::NewContextComponent, return false; );

		virtual bool NewDecalComponent(UIBBDecalComponent * & Component, TScriptInterface<IBBHighlightable> Owner) const PURE_VIRTUAL(UIBBComponentFactory::NewDecalComponent, return false; );
		
		virtual bool NewPlayerAbilityComponent(UIBBPlayerAbilityComponent * & Component, AIBBPlayerController * Owner) const PURE_VIRTUAL(UIBBComponentFactory::NewPlayerAbilityComponent, return false; );

		virtual bool NewProgressComponent(UIBBProgressComponent * & Component, TScriptInterface<IBBProgressable> Owner) const PURE_VIRTUAL(UIBBComponentFactory::NewProgressComponent, return false; );
		
		virtual bool NewSelectionComponent(UIBBSelectionComponent * & Component, TScriptInterface<IBBSelectable> Owner) const PURE_VIRTUAL(UIBBComponentFactory::NewSelectionComponent, return false; );

		virtual bool NewWidgetComponent(UIBBWidgetComponent * & Component, AActor * Owner) const PURE_VIRTUAL(UIBBComponentFactory::NewWidgetComponent, return false; );

		virtual bool NewWorkComponent(UIBBWorkComponent * & Component, TScriptInterface<IBBWorkable> Owner, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) const PURE_VIRTUAL(UIBBComponentFactory::NewWorkComponent, return false; );
};
		