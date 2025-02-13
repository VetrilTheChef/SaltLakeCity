// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/AIController.h"
#include "IBBAIController.generated.h"

/**
 * 
 */

Expose_TNameOf(AIBBAIController)

class UAnimMontage;
class UBehaviorTree;
class UIBBAbilityTask;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBAIController : public AAIController
{
	GENERATED_BODY()

	public:
		AIBBAIController() : Super() { };

		virtual void OnPossess(APawn * InPawn) override { Super::OnPossess(InPawn); };

		virtual void OnUnPossess() override { Super::OnUnPossess(); };

		virtual void StopBehaviorTree() PURE_VIRTUAL(AIBBAIController::StopBehaviorTree, );

		virtual void SetBlackboardTask(FName Name, UIBBAbilityTask * AbilityTask) PURE_VIRTUAL(AIBBAIController::SetBlackboardTask, );

		virtual void SetBlackboardObject(FName Name, UObject * Value) PURE_VIRTUAL(AIBBAIController::SetBlackboardObject, );

		virtual void SetBlackboardFloat(FName Name, float Value) PURE_VIRTUAL(AIBBAIController::SetBlackboardFloat, );

		virtual void ClearBlackboardValue(FName Name) PURE_VIRTUAL(AIBBAIController::ClearBlackboardValue, );

		virtual void PlayAnimationMontage(UAnimMontage * AnimMontage, float Rate = 1.0f, FName StartSection = NAME_None) PURE_VIRTUAL(AIBBAIController::PlayAnimationMontage, );

		virtual void StopAnimationMontage(UAnimMontage * AnimMontage) PURE_VIRTUAL(AIBBAIController::StopAnimationMontage, );
};