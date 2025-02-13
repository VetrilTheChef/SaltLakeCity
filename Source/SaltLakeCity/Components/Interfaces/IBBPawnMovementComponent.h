// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "IBBPawnMovementComponent.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	public:
		UIBBPawnMovementComponent() : Super() { };

		void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); };
};