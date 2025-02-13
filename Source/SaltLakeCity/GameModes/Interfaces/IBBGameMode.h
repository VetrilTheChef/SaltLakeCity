// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GameFramework/GameModeBase.h"
#include "IBBGameMode.generated.h"

/**
*
*/

Expose_TNameOf(AIBBGameMode)

class UIBBPlayerAbilityComponent;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
		AIBBGameMode() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize() PURE_VIRTUAL(AIBBGameMode::Initialize, );
		
		virtual void Finalize() PURE_VIRTUAL(AIBBGameMode::Finalize, );

		virtual void SetMode(EBBGameMode NewGameMode) PURE_VIRTUAL(AIBBGameMode::SetMode, );

		DECLARE_EVENT_OneParam(AIBBGameMode, FUpdateActiveMode, EBBGameMode);

		FUpdateActiveMode & OnActiveModeUpdate() { return ActiveModeUpdated; };

	protected:
		FUpdateActiveMode ActiveModeUpdated;
};