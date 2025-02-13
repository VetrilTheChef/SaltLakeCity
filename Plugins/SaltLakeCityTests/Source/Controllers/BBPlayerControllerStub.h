// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "BBPlayerControllerStub.generated.h"

/**
*
*/

class UIBBPlayerAbilityComponent;

UCLASS()

class ABBPlayerControllerStub : public AIBBPlayerController
{
	GENERATED_BODY()

	public:
		ABBPlayerControllerStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void SetupInputComponent() override;

		virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

		void SetAbilitySystemComponent(UIBBPlayerAbilityComponent * NewPlayerAbilityComponent);

		float GetLerpHeight();

		virtual void LerpToHeight(const float TargetHeight) override;

		UIBBAbilityData * GetRequestedAbilityData();

		virtual void RequestAbility(UIBBAbilityData * NewAbilityData) override;

		virtual void ConfirmTarget() override;

		virtual void CancelTarget() override;

		EBBGameMode GetActiveMode();

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

		void BroadcastFloorChangeRequest(int TargetFloorDelta, float TargetFloorHeight);

	protected:
		UPROPERTY()
		UIBBPlayerAbilityComponent * PlayerAbilityComponent;

		UPROPERTY()
		UIBBAbilityData * RequestedAbilityData;

		float PawnHeight;

		EBBGameMode ActiveGameMode;
};