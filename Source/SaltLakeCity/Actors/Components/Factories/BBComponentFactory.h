// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "BBComponentFactory.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBComponentFactory : public UIBBComponentFactory
{
	GENERATED_BODY()
	
	public:
		UBBComponentFactory();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void Initialize(AIBBHUD * NewHUD) override;

		virtual void Finalize() override;

		virtual bool NewAIAbilityComponent(UIBBAIAbilityComponent * & Component, AIBBAIController * Owner) const override;

		virtual bool NewContextComponent(UIBBContextComponent * & Component, TScriptInterface<IBBContextualizable> Owner) const override;

		virtual bool NewDecalComponent(UIBBDecalComponent * & Component, TScriptInterface<IBBHighlightable> Owner) const override;

		virtual bool NewPlayerAbilityComponent(UIBBPlayerAbilityComponent * & Component, AIBBPlayerController * Owner) const override;

		virtual bool NewProgressComponent(UIBBProgressComponent * & Component, TScriptInterface<IBBProgressable> Owner) const override;

		virtual bool NewSelectionComponent(UIBBSelectionComponent * & Component, TScriptInterface<IBBSelectable> Owner) const override;

		virtual bool NewWidgetComponent(UIBBWidgetComponent * & Component, AActor * Owner) const override;
		
		virtual bool NewWorkComponent(UIBBWorkComponent * & Component, TScriptInterface<IBBWorkable> Owner, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBAIAbilityComponent> AIAbilityComponentClass;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBContextComponent> ContextComponentClass;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBDecalComponent> DecalComponentClass;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBPlayerAbilityComponent> PlayerAbilityComponentClass;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBProgressComponent> ProgressComponentClass;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBSelectionComponent> SelectionComponentClass;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBWidgetComponent> WidgetComponentClass;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSoftClassPtr<UIBBWorkComponent> WorkComponentClass;

		UPROPERTY()
		AIBBHUD * HUD;

		FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
};