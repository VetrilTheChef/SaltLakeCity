// SaltLakeCity 4.27

#include "BBWorkComponent.h"
#include "Abilities/AI/Interfaces/IBBAIAbility.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "GameStates/Interfaces/IBBGameState.h"

UBBWorkComponent::UBBWorkComponent() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;

	Workable = TScriptInterface<IBBWorkable>(nullptr);
	AbilityComponent = nullptr;
	Task = nullptr;
	Job = EBBJob::None;
	JobSkillsMap.Empty();
}

void UBBWorkComponent::BeginPlay()
{
	Super::BeginPlay();

	JobSkillsMap.Emplace(EBBJob::Builder, EBBSkill::Build);
}

void UBBWorkComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBWorkComponent::Initialize(TScriptInterface<IBBWorkable> && NewWorkable, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob)
{
	verifyf(IsValid(NewWorkable.GetObject()), TEXT("New Workable is invalid"));
	verifyf(IsValid(NewAbilityComponent), TEXT("New Ability Component is invalid"));

	Workable = NewWorkable;
	AbilityComponent = NewAbilityComponent;
	SetJob(NewJob);
}

void UBBWorkComponent::Finalize()
{
	Workable = TScriptInterface<IBBWorkable>(nullptr);
	AbilityComponent = nullptr;
	Task = nullptr;
	Job = EBBJob::None;
	JobSkillsMap.Empty();
}

const EBBJob UBBWorkComponent::GetJob() const
{
	return Job;
}

void UBBWorkComponent::SetJob(EBBJob NewJob)
{
	if (IsValid(Task) && (Task->GetJobType() != NewJob))
	{
		UnassignTask();
	}

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));
	
	AIBBGameState * GameState = World->GetGameState<AIBBGameState>();

	verifyf(IsValid(GameState), TEXT("Game State is invalid."));

	GameState->RemoveConsumer(this, Job);

	Job = NewJob;

	GameState->AddConsumer(this, Job);
}

float UBBWorkComponent::GetJobEfficiency(EBBJob ForJob) const
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."));

	const EBBSkill * JobSkill = JobSkillsMap.Find(ForJob);

	float SkillValue = JobSkill ? AbilityComponent->GetSkill(* JobSkill) : 10.0f;

	return FMath::Max(11.0f - SkillValue, 1.0f);
}

void UBBWorkComponent::AssignTask(UIBBAbilityTask * NewTask)
{
	verifyf(IsValid(NewTask), TEXT("New Task is invalid."));

	Task = NewTask;
}

UIBBAbilityTask * UBBWorkComponent::UnassignTask()
{
	StopTask();

	UIBBAbilityTask * OldTask = Task;
	Task = nullptr;

	return OldTask;
}

UIBBAbilityTask * UBBWorkComponent::GetTask() const
{
	return Task;
}

bool UBBWorkComponent::StartTask()
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."));
	verifyf(IsValid(Task), TEXT("Task is invalid."));

	return AbilityComponent->StartTask(Task);

	/*verifyf(IsValid(Task), TEXT("Task is invalid."));

	TArray<FGameplayAbilitySpec *> RequestedAbilities;
	FGameplayTagContainer RequestedTags = FGameplayTagContainer();
	RequestedTags.AddTagFast(Task->GetEventTag());

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(RequestedTags, RequestedAbilities);

	bool ActivationResult = true;

	for (FGameplayAbilitySpec * & RequestedAbility : RequestedAbilities)
	{
		ActivationResult |= TriggerAbilityFromGameplayEvent(RequestedAbility->Handle, AbilityActorInfo.Get(), Task->GetEventTag(), Task->GetEventData(), *this);
	}

	return ActivationResult;*/
}

bool UBBWorkComponent::StopTask()
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."));
	verifyf(IsValid(Task), TEXT("Task is invalid."));

	return AbilityComponent->StopTask(Task);
}

bool UBBWorkComponent::IsWorking() const
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."));

	return AbilityComponent->IsRunningTask();
}

UIBBAbilityTask * UBBWorkComponent::CompleteTask()
{
	//OnTaskCompleted().Broadcast(this, Task);

	return UnassignTask();
}