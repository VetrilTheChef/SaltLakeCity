// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "BBCommandFactory.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBCommandFactory : public UIBBCommandFactory
{
	GENERATED_BODY()

	public:
		UBBCommandFactory();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void Initialize(UIBBGameInstance * NewGameInstance) override;

		virtual void Finalize() override;

		virtual bool NewOrderBuildCommand(UIBBOrderBuildCommand * & Command, UObject * Outer, const TSoftClassPtr<UIBBBuildData> BuildDataClass, const TSoftClassPtr<AIBBTargetingActor> TargetingClass, const TArray<FBBBuildablePtr> BuildableClasses, float Price, float Time) const override;

		virtual bool NewPauseCommand(UIBBPauseCommand * & Command, UObject * Outer) const override;

		virtual bool NewSpeedCommand(UIBBSpeedCommand * & Command, UObject * Outer, float TimeDilation) const override;
		
		virtual bool NewOpenWidgetCommand(UIBBOpenWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, bool PopUp) const override;

		virtual bool NewCloseWidgetCommand(UIBBCloseWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification) const override;

		virtual bool NewAttachWidgetCommand(UIBBAttachWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, UIBBWidgetComponent * Component) const override;

		virtual bool NewDetachWidgetCommand(UIBBDetachWidgetCommand * & Command, UObject * Outer, UIBBWidgetComponent * Component) const override;

		virtual bool NewGameModeCommand(UIBBGameModeCommand * & Command, UObject * Outer, EBBGameMode GameMode) const override;
		
		virtual bool NewSelectCommand(UIBBSelectCommand * & Command, UObject * Outer, TScriptInterface<IBBSelectable> Selectable) const override;
		
		virtual bool NewSetContextCommand(UIBBSetContextCommand * & Command, UObject * Outer, TScriptInterface<IBBContextualizable> Contextualizable) const override;

		virtual bool NewSetJobCommand(UIBBSetJobCommand * & Command, UObject * Outer, UIBBWorkComponent * WorkComponent, EBBJob Job) const override;

		virtual bool NewCompositeCommand(UIBBCompositeCommand * & Command, UObject * Outer) const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBOrderBuildCommand> OrderBuildCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBPauseCommand> PauseCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBSpeedCommand> SpeedCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBOpenWidgetCommand> OpenWidgetCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBCloseWidgetCommand> CloseWidgetCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBAttachWidgetCommand> AttachWidgetCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBDetachWidgetCommand> DetachWidgetCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBGameModeCommand> GameModeCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBSelectCommand> SelectCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBSetContextCommand> SetContextCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBSetJobCommand> SetJobCommandClass;

		UPROPERTY(EditDefaultsOnly, Category = "Commands")
		TSoftClassPtr<UIBBCompositeCommand> CompositeCommandClass;

		UPROPERTY()
		UIBBGameInstance * GameInstance;
};