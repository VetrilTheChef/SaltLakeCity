// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Levels/WorldSettings/Interfaces/IBBWorldSettings.h"
#include "BBWorldSettings.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API ABBWorldSettings : public AIBBWorldSettings
{
	GENERATED_BODY()
	
	public:
		ABBWorldSettings();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void NotifyBeginPlay() override;

		virtual void NotifyEndPlay() override;
};