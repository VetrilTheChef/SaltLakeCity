// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "BBSelectionComponent.generated.h"

class UDecalComponent;
class UIBBAttachWidgetCommand;
class UIBBCommandFactory;
class UIBBDetachWidgetCommand;
class UIBBSelectCommand;
class UIBBWidgetSpecification;
class UIBBWidgetSpecificationFactory;

struct FKey;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Components), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBSelectionComponent : public UIBBSelectionComponent
{
	GENERATED_BODY()

	public:	
		UBBSelectionComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBSelectable> && NewSelectable) override;

		virtual void Finalize() override;

		virtual TScriptInterface<IBBSelectable> GetSelectable() const override;

		virtual void SetSelectable(TScriptInterface<IBBSelectable> && NewSelectable) override;

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBSelectable> Selectable;

		UPROPERTY()
		UIBBSelectCommand * SelectCommand;

		UPROPERTY()
		UIBBAttachWidgetCommand * AttachCommand;

		UPROPERTY()
		UIBBDetachWidgetCommand * DetachCommand;

		UPROPERTY()
		UDecalComponent * Decal;

		void Subscribe(TScriptInterface<IBBSelectable> && NewSelectable);

		void Unsubscribe(TScriptInterface<IBBSelectable> & OldSelectable);

		void InitializeCommands(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, TScriptInterface<IBBSelectable> && NewSelectable);

		void InitializeSelectCommand(const UIBBCommandFactory & CommandFactory, TScriptInterface<IBBSelectable> && NewSelectable);

		void InitializeAttachWidgetCommand(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory);

		void InitializeDetachWidgetCommand(const UIBBCommandFactory & CommandFactory);

		void FinalizeCommands();

		void FinalizeSelectCommand();

		void FinalizeAttachWidgetCommand();

		void FinalizeDetachWidgetCommand();

		UFUNCTION()
		void Click(AActor * Actor, FKey ButtonPressed);

		UFUNCTION()
		void ToggleWidget(bool Attached);
};