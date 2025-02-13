// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "IBBActorComponent.generated.h"

UINTERFACE(MinimalAPI)

class UBBActorComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */

class SALTLAKECITY_API IBBActorComponent
{
	GENERATED_BODY()

	public:
		virtual AActor * ToActor() PURE_VIRTUAL(IBBActorComponent::ToActor, return nullptr; );
};