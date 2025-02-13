// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBDecalComponent.h"
#include "BBDecalComponentStub.generated.h"

UCLASS(NotBlueprintable)

class UBBDecalComponentStub : public UIBBDecalComponent
{
	GENERATED_BODY()

	public:	
		UBBDecalComponentStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBHighlightable> && NewHighlightable) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBHighlightable> Highlightable;

		UFUNCTION()
		void ToggleDecal(bool Highlighted);
};