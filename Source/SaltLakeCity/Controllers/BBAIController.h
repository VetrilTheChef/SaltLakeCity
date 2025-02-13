// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Controllers/Interfaces/IBBAIController.h"
#include "BBAIController.generated.h"

/**
 * 
 */

class UAnimMontage;

UCLASS()

class SALTLAKECITY_API ABBAIController : public AIBBAIController
{
	GENERATED_BODY()

	public:
		ABBAIController();

		virtual void OnPossess(APawn * InPawn) override;

		virtual void OnUnPossess() override;

		virtual void StopBehaviorTree() override;

		virtual void SetBlackboardTask(FName Name, UIBBAbilityTask * AbilityTask) override;

		virtual void SetBlackboardObject(FName Name, UObject * Value) override;

		virtual void SetBlackboardFloat(FName Name, float Value) override;

		virtual void ClearBlackboardValue(FName Name) override;

		virtual void PlayAnimationMontage(UAnimMontage * AnimMontage, float Rate = 1.0f, FName StartSection = NAME_None) override;

		virtual void StopAnimationMontage(UAnimMontage * AnimMontage) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
		TSoftObjectPtr<UBehaviorTree> DefaultBehaviorTree;
};