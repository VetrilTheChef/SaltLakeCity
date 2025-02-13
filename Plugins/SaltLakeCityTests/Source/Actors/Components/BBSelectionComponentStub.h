// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "BBSelectionComponentStub.generated.h"

class UIBBSelectCommand;

struct FKey;

UCLASS(NotBlueprintable)

class UBBSelectionComponentStub : public UIBBSelectionComponent
{
		GENERATED_BODY()

	public:
		UBBSelectionComponentStub();

		virtual void Initialize(TScriptInterface<IBBSelectable> && NewSelectable) override;

		virtual void Finalize() override;

		virtual TScriptInterface<IBBSelectable> GetSelectable() const override;

		virtual void SetSelectable(TScriptInterface<IBBSelectable> && NewSelectable) override;

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBSelectable> Selectable;

		UPROPERTY()
		UIBBSelectCommand * Command;

		UFUNCTION()
		void Click(AActor * Actor, FKey ButtonPressed);

		UFUNCTION()
		void ToggleWidget(bool Attached);
};