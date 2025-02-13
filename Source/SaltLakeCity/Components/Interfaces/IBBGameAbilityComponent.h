// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "IBBGameAbilityComponent.generated.h"

UCLASS(Abstract, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UIBBGameAbilityComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	public:	
		UIBBGameAbilityComponent() : Super() { };
};