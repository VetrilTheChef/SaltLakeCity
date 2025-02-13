// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Levels/WorldSettings/Interfaces/IBBWorldSettings.h"
#include "BBWorldSettingsStub.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)

class ABBWorldSettingsStub : public AIBBWorldSettings
{
	GENERATED_BODY()
	
	public:
		ABBWorldSettingsStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};