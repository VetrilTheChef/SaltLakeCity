// SaltLakeCity 4.25

#include "BBAIController.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

ABBAIController::ABBAIController() :
	Super()
{
}

void ABBAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(DefaultBehaviorTree.LoadSynchronous());
}

void ABBAIController::OnUnPossess()
{
	StopBehaviorTree();

	Super::OnUnPossess();
}

void ABBAIController::StopBehaviorTree()
{
	UBehaviorTreeComponent * BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (IsValid(BehaviorTreeComponent))
	{
		BehaviorTreeComponent->StopTree();
	}
}

void ABBAIController::SetBlackboardTask(FName Name, UIBBAbilityTask * AbilityTask)
{
	verifyf(IsValid(Blackboard), TEXT("Blackboard is invalid."));

	Blackboard->SetValueAsObject(Name, AbilityTask);
}

void ABBAIController::SetBlackboardObject(FName Name, UObject * Value)
{
	verifyf(IsValid(Blackboard), TEXT("Blackboard is invalid."));

	Blackboard->SetValueAsObject(Name, Value);
}

void ABBAIController::SetBlackboardFloat(FName Name, float Value)
{
	verifyf(IsValid(Blackboard), TEXT("Blackboard is invalid."));

	Blackboard->SetValueAsFloat(Name, Value);
}

void ABBAIController::ClearBlackboardValue(FName Name)
{
	verifyf(IsValid(Blackboard), TEXT("Blackboard is invalid."));

	Blackboard->ClearValue(Name);
}

void ABBAIController::PlayAnimationMontage(UAnimMontage * AnimMontage, float Rate, FName StartSection)
{
	//ACharacter * ControlledCharacter = GetCharacter();

	//if (IsValid(ControlledCharacter))
	//{
	//	ControlledCharacter->PlayAnimMontage(AnimMontage, Rate, StartSection);
	//}
}

void ABBAIController::StopAnimationMontage(UAnimMontage * AnimMontage)
{
	//ACharacter * ControlledCharacter = GetCharacter();

	//if (IsValid(ControlledCharacter))
	//{
	//	ControlledCharacter->StopAnimMontage(AnimMontage);
	//}
}