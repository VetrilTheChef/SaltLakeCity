// SaltLakeCity 4.25

#include "BBOrderBuildAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Data/BBBuildData.h"
#include "Actors/Buildings/Interfaces/IBBBuilding.h"
#include "Actors/Components/Interfaces/IBBPlayerAbilityComponent.h"
#include "Actors/Targeting/Interfaces/IBBTargetingActor.h"


UBBOrderBuildAbility::UBBOrderBuildAbility() :
	Super()
{
	AbilityData = nullptr;
	PlayerAbilityComponent = nullptr;
	WaitTargetDataTask = nullptr;
}

bool UBBOrderBuildAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

void UBBOrderBuildAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}



void UBBOrderBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// No straightforward way to pass the ability data while keeping it non-const
	// So, const_cast

	AbilityData = const_cast<UIBBBuildData *>(Cast<UIBBBuildData>(TriggerEventData->OptionalObject));

	verifyf(IsValid(AbilityData), TEXT("Ability Data is invalid."));

	PlayerAbilityComponent = Cast<UIBBPlayerAbilityComponent>(GetAbilitySystemComponentFromActorInfo());

	verifyf(IsValid(PlayerAbilityComponent), TEXT("Player Ability Component is invalid."));

	WaitForTargetData();
}

void UBBOrderBuildAbility::WaitForTargetData()
{
	UClass * TargetingClass = AbilityData->GetTargetingClass().LoadSynchronous();

	verifyf(IsValid(TargetingClass), TEXT("Targeting Actor class is invalid."));

	WaitTargetDataTask = UAbilityTask_WaitTargetData::WaitTargetData(this, FName(TEXT("")), EGameplayTargetingConfirmation::UserConfirmed, TargetingClass);

	verifyf(IsValid(WaitTargetDataTask), TEXT("Wait Target Data Task is invalid."));

	AGameplayAbilityTargetActor * Actor = nullptr;

	WaitTargetDataTask->ValidData.AddDynamic(this, & UBBOrderBuildAbility::TargetingFinish);
	WaitTargetDataTask->Cancelled.AddDynamic(this, & UBBOrderBuildAbility::TargetingCancel);
	WaitTargetDataTask->ReadyForActivation();
	WaitTargetDataTask->BeginSpawningActor(this, TargetingClass, Actor);
	WaitTargetDataTask->FinishSpawningActor(this, Actor);

	AIBBTargetingActor * TargetActor = Cast<AIBBTargetingActor>(Actor);

	verifyf(IsValid(TargetActor), TEXT("Target Actor is invalid."));

	AbilityData->SetTargetingActor(TargetActor);

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	TArray<FBBBuildablePtr> BuildableClasses = AbilityData->GetBuildableClasses();

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (FBBBuildablePtr & BuildableClass : BuildableClasses)
	{
		TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(World->SpawnActor<AActor>(BuildableClass.Get(), SpawnParameters));

		verifyf(IsValid(Buildable.GetObject()), TEXT("Buildable is invalid."));

		Buildable->ToActor()->SetActorEnableCollision(false);
		Buildable->AddMaterialOverride(TargetActor->GetPreviewMaterial());

		AbilityData->AddBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));
		TargetActor->AttachActor(Buildable->ToActor());
	}
}

void UBBOrderBuildAbility::TargetingFinish(const FGameplayAbilityTargetDataHandle & Data)
{
	verifyf(IsValid(WaitTargetDataTask), TEXT("Wait Target Data Task is invalid."));

	WaitTargetDataTask->ValidData.RemoveDynamic(this, & UBBOrderBuildAbility::TargetingFinish);
	WaitTargetDataTask->Cancelled.RemoveDynamic(this, & UBBOrderBuildAbility::TargetingCancel);
	WaitTargetDataTask->EndTask();

	WaitTargetDataTask = nullptr;

	int NumBuildables = AbilityData->GetNumBuildables();

	for (int Index = 0; Index < NumBuildables; Index++)
	{
		TScriptInterface<IBBBuildable> Buildable = AbilityData->GetBuildable(Index);

		verifyf(IsValid(Buildable.GetObject()), TEXT("Buildable is invalid."));

		Buildable->ToActor()->SetActorEnableCollision(true);
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBBOrderBuildAbility::TargetingCancel(const FGameplayAbilityTargetDataHandle & Data)
{
	verifyf(IsValid(WaitTargetDataTask), TEXT("Wait Target Data Task is invalid."));

	WaitTargetDataTask->ValidData.RemoveDynamic(this, &UBBOrderBuildAbility::TargetingFinish);
	WaitTargetDataTask->Cancelled.RemoveDynamic(this, &UBBOrderBuildAbility::TargetingCancel);
	WaitTargetDataTask->EndTask();

	WaitTargetDataTask = nullptr;

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	for (int Index = AbilityData->GetNumBuildables() - 1; Index >= 0; Index--)
	{
		TScriptInterface<IBBBuildable> Buildable = AbilityData->GetBuildable(Index);

		verifyf(IsValid(Buildable.GetObject()), TEXT("Buildable is invalid."));

		AbilityData->RemoveBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));

		World->DestroyActor(Buildable->ToActor());
	}

	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UBBOrderBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!bWasCancelled)
	{
		verifyf(IsValid(PlayerAbilityComponent), TEXT("Player Ability Component is invalid."));

		PlayerAbilityComponent->OnJobQueued.Broadcast(AbilityData);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}