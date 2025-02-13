// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "BBGameMode.generated.h"

/**
*
*/

struct FAbilityEndedData;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API ABBGameMode : public AIBBGameMode
{
	GENERATED_BODY()

	public:
		ABBGameMode();

		virtual void BeginPlay() override;
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize() override;

		virtual void Finalize() override;

		virtual void SetMode(EBBGameMode NewGameMode) override;
};