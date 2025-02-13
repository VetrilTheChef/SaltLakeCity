// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "UObject/NoExportTypes.h"
#include "BBComponentFactoryStub.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable)

class UBBComponentFactoryStub : public UIBBComponentFactory
{
	GENERATED_BODY()

	public:
		UBBComponentFactoryStub();

		virtual void Initialize(AIBBHUD * NewHUD) override;

		virtual void Finalize() override;

		void AddAIAbilityComponent(UIBBAIAbilityComponent * Component);

		virtual bool NewAIAbilityComponent(UIBBAIAbilityComponent * & Component, AIBBAIController * Owner) const override;

		void AddContextComponent(UIBBContextComponent * Component);

		virtual bool NewContextComponent(UIBBContextComponent * & Component, TScriptInterface<IBBContextualizable> Owner) const override;

		void AddDecalComponent(UIBBDecalComponent * Component);

		virtual bool NewDecalComponent(UIBBDecalComponent * & Component, TScriptInterface<IBBHighlightable> Owner) const override;

		void AddPlayerAbilityComponent(UIBBPlayerAbilityComponent * Component);

		virtual bool NewPlayerAbilityComponent(UIBBPlayerAbilityComponent * & Component, AIBBPlayerController * Owner) const override;

		void AddProgressComponent(UIBBProgressComponent * Component);

		virtual bool NewProgressComponent(UIBBProgressComponent * & Component, TScriptInterface<IBBProgressable> Owner) const override;

		void AddSelectionComponent(UIBBSelectionComponent * Component);

		virtual bool NewSelectionComponent(UIBBSelectionComponent * & Component, TScriptInterface<IBBSelectable> Owner) const override;

		void AddWidgetComponent(UIBBWidgetComponent * Component);

		virtual bool NewWidgetComponent(UIBBWidgetComponent * & Component, AActor * Owner) const override;

		void AddWorkComponent(UIBBWorkComponent * Component);

		virtual bool NewWorkComponent(UIBBWorkComponent * & Component, TScriptInterface<IBBWorkable> Owner, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) const override;

	protected:
		UPROPERTY()
		mutable TArray<UIBBAIAbilityComponent *> AIAbilityComponents;

		UPROPERTY()
		mutable TArray<UIBBContextComponent *> ContextComponents;

		UPROPERTY()
		mutable TArray<UIBBDecalComponent *> DecalComponents;

		UPROPERTY()
		mutable TArray<UIBBPlayerAbilityComponent *> PlayerAbilityComponents;

		UPROPERTY()
		mutable TArray<UIBBProgressComponent *> ProgressComponents;

		UPROPERTY()
		mutable TArray<UIBBSelectionComponent *> SelectionComponents;

		UPROPERTY()
		mutable TArray<UIBBWidgetComponent *> WidgetComponents;

		UPROPERTY()
		mutable TArray<UIBBWorkComponent *> WorkComponents;

		UPROPERTY()
		AIBBHUD * HUD;

		FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
};