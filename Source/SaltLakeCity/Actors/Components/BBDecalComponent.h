// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBDecalComponent.h"
#include "BBDecalComponent.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBDecalComponent : public UIBBDecalComponent
{
	GENERATED_BODY()

	public:	
		UBBDecalComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBHighlightable> && NewHighlightable) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Material")
		TSoftObjectPtr<UMaterialInterface> HighlightMaterial;

		UPROPERTY()
		TScriptInterface<IBBHighlightable> Highlightable;

		UPROPERTY()
		UMaterialInterface * Material;

		void Subscribe(TScriptInterface<IBBHighlightable> && NewHighlightable);

		void Unsubscribe(TScriptInterface<IBBHighlightable> & OldHighlightable);

		UFUNCTION()
		void ToggleDecal(bool Highlighted);
};