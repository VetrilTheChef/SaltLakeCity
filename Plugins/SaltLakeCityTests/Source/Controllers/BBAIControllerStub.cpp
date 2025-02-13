// SaltLakeCity 4.27

#include "BBAIControllerStub.h"

ABBAIControllerStub::ABBAIControllerStub() :
	Super()
{
	BlackboardTasks.Empty();
	BlackboardObjects.Empty();
	BlackboardFloats.Empty();
	CurrentAnimMontage = nullptr;
	CurrentAnimRate = 0.0f;
	CurrentAnimStartSection = FName("");
	CurrentAnimPlaying = false;
}

void ABBAIControllerStub::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
}

void ABBAIControllerStub::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABBAIControllerStub::StopBehaviorTree()
{
}

void ABBAIControllerStub::SetBlackboardTask(FName Name, UIBBAbilityTask * AbilityTask)
{
	UIBBAbilityTask * Task = BlackboardTasks.FindOrAdd(Name);
	Task = AbilityTask;
}

void ABBAIControllerStub::SetBlackboardObject(FName Name, UObject * Value)
{
	UObject * Object = BlackboardObjects.FindOrAdd(Name);
	Object = Value;
}

void ABBAIControllerStub::SetBlackboardFloat(FName Name, float Value)
{
	float Number = BlackboardFloats.FindOrAdd(Name);
	Number = Value;
}

void ABBAIControllerStub::ClearBlackboardValue(FName Name)
{
	BlackboardTasks.Remove(Name);
	BlackboardObjects.Remove(Name);
	BlackboardFloats.Remove(Name);
}

void ABBAIControllerStub::PlayAnimationMontage(UAnimMontage * AnimMontage, float Rate, FName StartSection)
{
	CurrentAnimMontage = AnimMontage;
	CurrentAnimRate = Rate;
	CurrentAnimStartSection = StartSection;
	CurrentAnimPlaying = true;
}

void ABBAIControllerStub::StopAnimationMontage(UAnimMontage * AnimMontage)
{
	CurrentAnimPlaying = false;
}