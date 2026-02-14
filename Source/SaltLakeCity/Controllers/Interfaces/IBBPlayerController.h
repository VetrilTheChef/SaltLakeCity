// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "IBBPlayerController.generated.h"

/**
*
*/

Expose_TNameOf(AIBBPlayerController)

class UIBBAbilityData;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBPlayerController : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()

	public:
		AIBBPlayerController() : Super() { };

		virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override PURE_VIRTUAL(AIBBPlayerController::GetAbilitySystemComponent, return nullptr; );

		virtual void LerpToHeight(const float TargetHeight) PURE_VIRTUAL(AIBBPlayerController::LerpToHeight, );

		virtual void RequestAbility(UIBBAbilityData * NewAbilityData) PURE_VIRTUAL(AIBBPlayerController::RequestAbility, );

		virtual bool GetCursorGridPosition(FVector & OutPosition) const PURE_VIRTUAL(AIBBPlayerController::GetCursorGridPosition, return false; );

		UFUNCTION()
		virtual void ConfirmTarget() PURE_VIRTUAL(AIBBPlayerController::ConfirmTarget, );

		UFUNCTION()
		virtual void CancelTarget() PURE_VIRTUAL(AIBBPlayerController::CancelTarget, );

		UFUNCTION()
		virtual void StartMarqueeSelection() PURE_VIRTUAL(AIBBPlayerController::StartMarqueeSelection, );

		UFUNCTION()
		virtual void EndMarqueeSelection() PURE_VIRTUAL(AIBBPlayerController::EndMarqueeSelection, );

		UFUNCTION()
		virtual void UpdateMarqueeSelection() PURE_VIRTUAL(AIBBPlayerController::UpdateMarqueeSelection, );

		UFUNCTION()
		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) PURE_VIRTUAL(AIBBPlayerController::UpdateActiveMode, );

		DECLARE_EVENT_TwoParams(AIBBPlayerController, FChangeFloorRequest, const int, float &);

		virtual FChangeFloorRequest & OnFloorChangeRequested() final { return ChangeFloorRequest; };

	protected:
		FChangeFloorRequest ChangeFloorRequest;
};