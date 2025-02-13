// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/IBBGameAbilityComponent.h"
#include "BBGameAbilityComponent.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBGameAbilityComponent : public UIBBGameAbilityComponent
{
	GENERATED_BODY()

	public:	
		UBBGameAbilityComponent();
};