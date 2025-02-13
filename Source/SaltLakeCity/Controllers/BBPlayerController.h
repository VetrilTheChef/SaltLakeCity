// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Includes/BBAbilityEnum.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "BBPlayerController.generated.h"

/**
*
*/

class AIBBPawn;
class UIBBAbilityData;
class UIBBPlayerAbilityComponent;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API ABBPlayerController : public AIBBPlayerController
{
	GENERATED_BODY()

	public:
		ABBPlayerController();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void SetupInputComponent() override;

		virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

		virtual void LerpToHeight(const float TargetHeight) override;

		virtual void RequestAbility(UIBBAbilityData * NewAbilityData) override;

		virtual bool GetCursorGridPosition(FVector & OutPosition) const override;

		virtual void ConfirmTarget() override;

		virtual void CancelTarget() override;

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TSoftClassPtr<UIBBPlayerAbilityComponent> PlayerAbilityComponentClass;

		UPROPERTY()
		TMap<EBBGameMode, UInputComponent *> ModeInputComponents;

		UPROPERTY()
		UIBBPlayerAbilityComponent * PlayerAbilityComponent;

		UPROPERTY()
		AIBBPawn * ControllerPawn;

		bool MovementEnabled;

		ETraceTypeQuery GridTrace;

		ETraceTypeQuery BuildableTrace;

		void CreateAbilityComponent();

		void DestroyAbilityComponent();

		virtual void OnPossess(APawn* InPawn) override;

		void ClearInputComponents();

		void DisableMovement();

		void EnableMovement();

		void MoveForward(float AxisValue);

		void MoveRight(float AxisValue);

		void MoveUp();

		void MoveDown();

		void Zoom(float AxisValue);

		void Pan(float AxisValue);
};