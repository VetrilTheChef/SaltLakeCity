// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"
#include "BBAbilityData.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBAbilityData : public UIBBAbilityData
{
	GENERATED_BODY()
	
	public:
		UBBAbilityData();
};