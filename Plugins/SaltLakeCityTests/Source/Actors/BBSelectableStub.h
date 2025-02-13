// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "BBSelectableStub.generated.h"

UCLASS(NotBlueprintable)

class UBBSelectableStub : public UObject, public IBBSelectable
{
	GENERATED_BODY()

	public:
		UBBSelectableStub();

		virtual void UpdateSelection(bool Selected) override;

		virtual bool GetIsSelected() const;

		virtual UIBBSelectionComponent * GetSelectionComponent() const override;

		void SetSelectionComponent(UIBBSelectionComponent * NewSelectionComponent);

		virtual AActor * ToActor() override;

		void SetActor(AActor * NewSelectableActor);

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget);

		DECLARE_DERIVED_EVENT(UBBSelectableStub, IBBSelectable::FBBSelectionUpdate, FBBSelectionUpdate);

		virtual FBBSelectionUpdate & OnSelectionUpdate() final override { return SelectionUpdate; };

	protected:
		UPROPERTY()
		UIBBSelectionComponent * SelectionComponent;

		UPROPERTY()
		AActor * SelectableActor;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		bool IsSelected;

		FBBSelectionUpdate SelectionUpdate;
};