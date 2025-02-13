// SaltLakeCity 4.27

#include "BBAIAbilityComponentStub.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"

UBBAIAbilityComponentStub::UBBAIAbilityComponentStub() :
	Super()
{
	Controller = nullptr;
	Task = nullptr;
	BehaviorTree = nullptr;
	BehaviorTreeTask = nullptr;
	BehaviorTreeTaskName = FName("");
	RunningTask = false;
}

void UBBAIAbilityComponentStub::Initialize(AIBBAIController * NewController, const TArray<FBBAttributeSetData> & SetsData)
{
	Controller = NewController;
}

void UBBAIAbilityComponentStub::Finalize()
{
	Controller = nullptr;
	Task = nullptr;
	BehaviorTree = nullptr;
	BehaviorTreeTask = nullptr;
	BehaviorTreeTaskName = FName("");
	RunningTask = false;
}

void UBBAIAbilityComponentStub::SetAIController(AIBBAIController * NewAIController)
{
	Controller = NewAIController;
}

const TArray<FBBAttributeSetData> UBBAIAbilityComponentStub::GetAttributeSetsData() const
{
	return AttributeSetsData;
}

void UBBAIAbilityComponentStub::SetAttributeSetsData(TArray<FBBAttributeSetData> NewAttributeSetsData)
{
	AttributeSetsData = NewAttributeSetsData;
}

void UBBAIAbilityComponentStub::AddAttributeSet(UIBBBaseAttributeSet * Set)
{
	if (IsValid(Set))
	{
		TArray<UAttributeSet *> NewSpawnedAttributes = GetSpawnedAttributes_Mutable();
		NewSpawnedAttributes.AddUnique(Set);

		SetSpawnedAttributes(NewSpawnedAttributes);
	}
}

void UBBAIAbilityComponentStub::RemoveAttributeSet(UIBBBaseAttributeSet * Set)
{
	if (IsValid(Set))
	{
		TArray<UAttributeSet *> NewSpawnedAttributes = GetSpawnedAttributes_Mutable();
		NewSpawnedAttributes.Remove(Set);

		SetSpawnedAttributes(NewSpawnedAttributes);
	}
}

bool UBBAIAbilityComponentStub::StartTask(UIBBAbilityTask * AbilityTask)
{
	Task = AbilityTask;

	RunningTask = true;

	return true;
}

bool UBBAIAbilityComponentStub::StopTask(UIBBAbilityTask * AbilityTask)
{
	Task = nullptr;

	RunningTask = false;

	return true;
}

bool UBBAIAbilityComponentStub::IsRunningTask() const
{
	return RunningTask;
}

void UBBAIAbilityComponentStub::SetIsRunningTask(bool NewRunningTask)
{
	RunningTask = NewRunningTask;
}

UIBBAbilityTask * UBBAIAbilityComponentStub::GetCurrentTask() const
{
	return Task;
}

void UBBAIAbilityComponentStub::RunBehaviorTree(UBehaviorTree * NewBehaviorTree, FName TreeTaskName, UIBBAbilityTask * TreeTask)
{
	BehaviorTree = NewBehaviorTree;
	BehaviorTreeTaskName = TreeTaskName;
	BehaviorTreeTask = TreeTask;
}

FName UBBAIAbilityComponentStub::GetTaskName()
{
	return BehaviorTreeTaskName;
}

UIBBAbilityTask * UBBAIAbilityComponentStub::GetTask()
{
	return BehaviorTreeTask;
}

UBehaviorTree * UBBAIAbilityComponentStub::GetBehaviorTree()
{
	return BehaviorTree;
}