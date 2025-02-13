// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "IBBAbility.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
	public:
		UIBBAbility() : Super() { };
};