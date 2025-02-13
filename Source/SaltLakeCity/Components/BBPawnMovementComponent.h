// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/IBBPawnMovementComponent.h"
#include "BBPawnMovementComponent.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBPawnMovementComponent : public UIBBPawnMovementComponent
{
	GENERATED_BODY()

	public:
		UBBPawnMovementComponent();

		void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (ClampMin = "1000.0", ClampMax = "5000.0"))
		float MaxSpeed;

		virtual void ApplyControlInputToVelocity(float DeltaTime);
};