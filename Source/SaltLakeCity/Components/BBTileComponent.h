// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/IBBTileComponent.h"
#include "BBTileComponent.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBTileComponent : public UIBBTileComponent
{
	GENERATED_BODY()

	public:
		UBBTileComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual const float GetSize() const override;

		virtual void SetSize(const float NewSize) override;

	protected:
		float Size;
};