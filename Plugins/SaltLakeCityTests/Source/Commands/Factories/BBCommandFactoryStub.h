// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "BBCommandFactoryStub.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable)

class UBBCommandFactoryStub : public UIBBCommandFactory
{
	GENERATED_BODY()

	public:
		UBBCommandFactoryStub();

		virtual void PostInitProperties() override;

		virtual void Initialize(UIBBGameInstance * NewGameInstance) override;

		virtual void Finalize() override;

		void AddOrderBuildCommand(UIBBOrderBuildCommand * NewOrderBuildCommand);

		virtual bool NewOrderBuildCommand(UIBBOrderBuildCommand * & Command, UObject * Outer, const TSoftClassPtr<UIBBBuildData> BuildDataClass, const TSoftClassPtr<AIBBTargetingActor> TargetingClass, const TArray<FBBBuildablePtr> BuildableClasses, float Price, float Time) const override;

		void AddPauseCommand(UIBBPauseCommand * NewPauseCommand);

		virtual bool NewPauseCommand(UIBBPauseCommand * & Command, UObject * Outer) const override;

		void AddSpeedCommand(UIBBSpeedCommand * NewSpeedCommand);

		virtual bool NewSpeedCommand(UIBBSpeedCommand * & Command, UObject * Outer, float TimeDilation) const override;

		void AddOpenWidgetCommand(UIBBOpenWidgetCommand * NewOpenWidgetCommand);

		virtual bool NewOpenWidgetCommand(UIBBOpenWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, bool PopUp) const override;

		void AddCloseWidgetCommand(UIBBCloseWidgetCommand * NewCloseWidgetCommand);

		virtual bool NewCloseWidgetCommand(UIBBCloseWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification) const override;

		void AddAttachWidgetCommand(UIBBAttachWidgetCommand * NewAttachWidgetCommand);

		virtual bool NewAttachWidgetCommand(UIBBAttachWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, UIBBWidgetComponent * Component) const override;

		void AddDetachWidgetCommand(UIBBDetachWidgetCommand * NewDetachWidgetCommand);

		virtual bool NewDetachWidgetCommand(UIBBDetachWidgetCommand * & Command, UObject * Outer, UIBBWidgetComponent * Component) const override;

		void AddGameModeCommand(UIBBGameModeCommand * NewGameModeCommand);

		virtual bool NewGameModeCommand(UIBBGameModeCommand * & Command, UObject * Outer, EBBGameMode ActiveGameMode) const override;

		void AddSelectCommand(UIBBSelectCommand * NewSelectCommand);
		
		virtual bool NewSelectCommand(UIBBSelectCommand * & Command, UObject * Outer, TScriptInterface<IBBSelectable> Selectable) const override;

		void AddSetContextCommand(UIBBSetContextCommand * NewSetContextCommand);

		virtual bool NewSetContextCommand(UIBBSetContextCommand * & Command, UObject * Outer, TScriptInterface<IBBContextualizable> Contextualizable) const override;

		void AddSetJobCommand(UIBBSetJobCommand * NewSetJobCommand);

		virtual bool NewSetJobCommand(UIBBSetJobCommand * & Command, UObject * Outer, UIBBWorkComponent * WorkComponent, EBBJob Job) const override;

		void AddCompositeCommand(UIBBCompositeCommand * NewCompositeCommand);

		virtual bool NewCompositeCommand(UIBBCompositeCommand * & Command, UObject * Outer) const override;

	protected:
		UPROPERTY()
		UIBBGameInstance * GameInstance;

		UPROPERTY()
		mutable TArray<UIBBAttachWidgetCommand *> AttachWidgetCommands;

		UPROPERTY()
		mutable TArray<UIBBCloseWidgetCommand *> CloseWidgetCommands;

		UPROPERTY()
		mutable TArray<UIBBCompositeCommand *> CompositeCommands;

		UPROPERTY()
		mutable TArray<UIBBDetachWidgetCommand *> DetachWidgetCommands;

		UPROPERTY()
		mutable TArray<UIBBGameModeCommand *> GameModeCommands;

		UPROPERTY()
		mutable TArray<UIBBOpenWidgetCommand *> OpenWidgetCommands;

		UPROPERTY()
		mutable TArray<UIBBOrderBuildCommand *> OrderBuildCommands;

		UPROPERTY()
		mutable TArray<UIBBPauseCommand *> PauseCommands;

		UPROPERTY()
		mutable TArray<UIBBSelectCommand *> SelectCommands;

		UPROPERTY()
		mutable TArray<UIBBSetContextCommand *> SetContextCommands;

		UPROPERTY()
		mutable TArray<UIBBSetJobCommand *> SetJobCommands;

		UPROPERTY()
		mutable TArray<UIBBSpeedCommand *> SpeedCommands;
};