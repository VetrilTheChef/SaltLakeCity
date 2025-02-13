// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBHighlightable.h"
#include "BBHighlightableStub.generated.h"

UCLASS(NotBlueprintable)

class UBBHighlightableStub : public UObject, public IBBHighlightable
{
	GENERATED_BODY()

	public:
		UBBHighlightableStub();

		virtual void UpdateHighlight(bool Highlighted) override;

		bool GetIsHighlighted() const;

		virtual UIBBDecalComponent * GetDecalComponent() const override;

		void SetDecalComponent(UIBBDecalComponent * NewDecalComponent);

		virtual AActor * ToActor() override;

		void SetActor(AActor * NewHighlightableActor);

		DECLARE_DERIVED_EVENT(UBBHighlightableStub, IBBHighlightable::FBBHighlightUpdate, FBBHighlightUpdate);

		virtual FBBHighlightUpdate & OnHighlightUpdate() final override { return HighlightUpdate; };

	protected:
		UPROPERTY()
		UIBBDecalComponent * DecalComponent;

		UPROPERTY()
		AActor * HighlightableActor;

		bool IsHighlighted;

		FBBHighlightUpdate HighlightUpdate;
};