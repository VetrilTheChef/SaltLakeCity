// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Controllers/Interfaces/IBBAIController.h"
#include "BBAIControllerStub.generated.h"

/**
 * 
 */

class UAnimMontage;

UCLASS()

class ABBAIControllerStub : public AIBBAIController
{
	GENERATED_BODY()

	public:
		ABBAIControllerStub();

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
		UPROPERTY()
		TMap<FName, UIBBAbilityTask *> BlackboardTasks;

		UPROPERTY()
		TMap<FName, UObject *> BlackboardObjects;

		UPROPERTY()
		UAnimMontage * CurrentAnimMontage;

		TMap<FName, float> BlackboardFloats;
		
		float CurrentAnimRate;

		FName CurrentAnimStartSection;

		bool CurrentAnimPlaying;
};