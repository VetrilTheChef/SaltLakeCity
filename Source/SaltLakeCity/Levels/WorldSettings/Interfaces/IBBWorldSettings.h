// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "IBBWorldSettings.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API AIBBWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
	public:
		AIBBWorldSettings() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay();  };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void NotifyBeginPlay() override { Super::NotifyBeginPlay(); };

		virtual void NotifyEndPlay() PURE_VIRTUAL(AIBBWorldSettings::NotifyEndPlay, );
};

Expose_TNameOf(AIBBWorldSettings);