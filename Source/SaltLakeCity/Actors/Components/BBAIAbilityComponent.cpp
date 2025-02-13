// SaltLakeCity 4.27

#include "BBAIAbilityComponent.h"
#include "Abilities/AI/Interfaces/IBBAIAbility.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "Attributes/Interfaces/IBBAttributeSet.h"
#include "Attributes/Interfaces/IBBNeedSet.h"
#include "Attributes/Interfaces/IBBSkillSet.h"
#include "Controllers/Interfaces/IBBAIController.h"
#include "GameFramework/Character.h"

UBBAIAbilityComponent::UBBAIAbilityComponent() :
	Super()
{
	AIController = nullptr;
	CurrentAbilityTask = nullptr;
}

void UBBAIAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	GiveAbilities();
}

void UBBAIAbilityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AIController = nullptr;
	CurrentAbilityTask = nullptr;

	ClearActorInfo();
	ClearAbilities();

	Super::EndPlay(EndPlayReason);
}

void UBBAIAbilityComponent::Initialize(AIBBAIController * NewAIController, const TArray<FBBAttributeSetData> & SetsData)
{
	SetAIController(NewAIController);

	for (const FBBAttributeSetData & SetData : SetsData)
	{
		CreateAttributes(SetData.Class.LoadSynchronous(), SetData.DataTable.LoadSynchronous());
	}

	/*CreateAttributes(NeedsAttributeSetClass.LoadSynchronous(), NeedsDataTable);
	CreateAttributes(SkillAttributeSetClass.LoadSynchronous(), SkillsDataTable);
	CreateAttributes(AttributeSetClass.LoadSynchronous(), AttributeSetDataTable.LoadSynchronous());

	verifyf(GetSpawnedAttributes_Mutable().FindItemByClass<UIBBNeedAttributeSet>(& NeedsSet), TEXT("Needs Attribute Set not found."));
	verifyf(GetSpawnedAttributes_Mutable().FindItemByClass<UIBBSkillAttributeSet>(& SkillsSet), TEXT("Skills Attribute Set not found."));
	verifyf(GetSpawnedAttributes_Mutable().FindItemByClass<UIBBAttributeSet>(& DerivedSet), TEXT("Derived Attribute Set not found."));*/
}

void UBBAIAbilityComponent::Finalize()
{
	DestroyAttributes();

	AIController = nullptr;
}

void UBBAIAbilityComponent::SetAIController(AIBBAIController * NewAIController)
{
	verifyf(IsValid(NewAIController), TEXT("New AI Controller is invalid."));

	AIController = NewAIController;

	InitAbilityActorInfo(AIController, AIController->GetPawn());
}

const TArray<FBBAttributeSetData> UBBAIAbilityComponent::GetAttributeSetsData() const
{
	return AttributeSetsData;
}

float UBBAIAbilityComponent::GetNeed(EBBNeed Need) const
{
	const UIBBNeedSet * NeedSet = GetSet<UIBBNeedSet>();

	verifyf(IsValid(NeedSet), TEXT("Need Set is invalid."));

	return NeedSet->GetValue(Need);
}

void UBBAIAbilityComponent::SetNeed(EBBNeed Need, float NewValue)
{
	/*UIBBNeedSet * NeedSet = GetSet<UIBBNeedSet>();

	verifyf(IsValid(NeedSet), TEXT("Need Set is invalid."));

	NeedSet->SetValue(Need, NewValue);*/
}

float UBBAIAbilityComponent::GetSkill(EBBSkill Skill) const
{
	const UIBBSkillSet * SkillSet = GetSet<UIBBSkillSet>();

	verifyf(IsValid(SkillSet), TEXT("Skill Set is invalid."));

	return SkillSet->GetValue(Skill);
}

void UBBAIAbilityComponent::SetSkill(EBBSkill Skill, float NewValue)
{
	/*UIBBSkillSet * SkillSet = GetSet<UIBBSkillSet>();

	verifyf(IsValid(SkillSet), TEXT("Skill Set is invalid."));

	SkillSet->SetValue(Skill, NewValue);*/
}

bool UBBAIAbilityComponent::StartTask(UIBBAbilityTask * AbilityTask)
{
	verifyf(IsValid(AbilityTask), TEXT("Ability Task is invalid."))

	StopTask(CurrentAbilityTask);

	CurrentAbilityTask = AbilityTask;

	TArray<FGameplayAbilitySpec *> ActivatedAbilities;
	FGameplayTagContainer Tags = FGameplayTagContainer();
	Tags.AddTagFast(CurrentAbilityTask->GetEventTag());

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tags, ActivatedAbilities);

	bool Result = true;

	for (FGameplayAbilitySpec * & ActivatedAbility : ActivatedAbilities)
	{
		Result |= TriggerAbilityFromGameplayEvent(ActivatedAbility->Handle, AbilityActorInfo.Get(), CurrentAbilityTask->GetEventTag(), CurrentAbilityTask->GetEventData(), * this);
	}

	return Result;
}

bool UBBAIAbilityComponent::StopTask(UIBBAbilityTask * AbilityTask)
{
	verifyf(IsValid(AbilityTask), TEXT("Ability Task is invalid."))

	TArray<FGameplayAbilitySpec *> ActivatedAbilities;
	FGameplayTagContainer Tags = FGameplayTagContainer();
	Tags.AddTagFast(AbilityTask->GetEventTag());

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tags, ActivatedAbilities);

	bool Result = true;

	for (FGameplayAbilitySpec * & ActivatedAbility : ActivatedAbilities)
	{
		verifyf(ActivatedAbility != nullptr, TEXT("Activated Ability is null."));

		CancelAbilitySpec(* ActivatedAbility, nullptr);
	}

	CurrentAbilityTask = nullptr;

	//OnTaskCanceled().Broadcast(this, Task);

	return true;
}

bool UBBAIAbilityComponent::IsRunningTask() const
{
	if (IsValid(CurrentAbilityTask))
	{
		TArray<FGameplayAbilitySpec *> TaskAbilities;
		FGameplayTagContainer Tags = FGameplayTagContainer();
		Tags.AddTagFast(CurrentAbilityTask->GetEventTag());

		GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tags, TaskAbilities);

		for (FGameplayAbilitySpec * & TaskAbility : TaskAbilities)
		{
			verifyf(TaskAbility != nullptr, TEXT("Active Ability is null."));

			if (TaskAbility->IsActive())
			{
				return true;
			}
		}
	}

	return false;
}

void UBBAIAbilityComponent::RunBehaviorTree(UBehaviorTree * NewBehaviorTree, FName TreeTaskName, UIBBAbilityTask * TreeTask)
{
	verifyf(IsValid(AIController), TEXT("AI Controller is invalid."));

	AIController->RunBehaviorTree(NewBehaviorTree);

	if (IsValid(TreeTask))
	{
		AIController->SetBlackboardTask(TreeTaskName, TreeTask);
	}
}



void UBBAIAbilityComponent::CreateAttributes(UClass * AttributeSetClass, UDataTable * AttributeSetDataTable)
{
	InitStats(AttributeSetClass, AttributeSetDataTable);
}

void UBBAIAbilityComponent::DestroyAttributes()
{
	TArray<UAttributeSet *> AttibuteSets = GetSpawnedAttributes();

	for (UAttributeSet * & AttributeSet : AttibuteSets)
	{
		AttributeSet->MarkPendingKill();
	}
}

void UBBAIAbilityComponent::GiveAbilities()
{
	for (TSubclassOf<UIBBAIAbility> & AbilityClass : AbilityClasses)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1, -1, this);

		GiveAbility(AbilitySpec);
	}
}

void UBBAIAbilityComponent::ClearAbilities()
{
	ClearAllAbilities();
}

void UBBAIAbilityComponent::OnTagUpdated(const FGameplayTag & Tag, bool TagExists)
{
	Super::OnTagUpdated(Tag, TagExists);
}