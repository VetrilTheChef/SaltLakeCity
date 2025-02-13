// SaltLakeCity 4.26

#include "BBPlayerAbilityComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Player/Interfaces/IBBPlayerAbility.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"

UBBPlayerAbilityComponent::UBBPlayerAbilityComponent() :
	Super()
{
}

void UBBPlayerAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	SetOwnerActor(GetOwnerActor());
	SetAvatarActor(GetOwnerActor());

	for (auto& AbilityClass : AbilityClasses)
	{
		AddAbility(AbilityClass);
	}
}

void UBBPlayerAbilityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearAbilities();

	Super::EndPlay(EndPlayReason);
}

TArray<TSubclassOf<UIBBPlayerAbility>> UBBPlayerAbilityComponent::GetAbilityClasses()
{
	return AbilityClasses;
}

void UBBPlayerAbilityComponent::AddAbility(TSubclassOf<UIBBPlayerAbility> NewPlayerAbilityClass)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(NewPlayerAbilityClass, 1, -1, this);

	GiveAbility(AbilitySpec);
}

void UBBPlayerAbilityComponent::ClearAbilities()
{
	ClearAllAbilities();
}

bool UBBPlayerAbilityComponent::RequestAbility(UIBBAbilityData * AbilityData)
{
	verifyf(IsValid(AbilityData), TEXT("Ability Data is invalid."));

	TArray<FGameplayAbilitySpec *> RequestedAbilities;
	FGameplayTagContainer RequestedTags = FGameplayTagContainer();
	RequestedTags.AddTagFast(AbilityData->GetEventTag());

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(RequestedTags, RequestedAbilities);

	bool ActivationResult = true;

	for (FGameplayAbilitySpec * & RequestedAbility : RequestedAbilities)
	{
		ActivationResult |= TriggerAbilityFromGameplayEvent(RequestedAbility->Handle, AbilityActorInfo.Get(), AbilityData->GetEventTag(), AbilityData->GetEventData(), * this);
	}
	
	return ActivationResult;
}



void UBBPlayerAbilityComponent::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	Super::OnTagUpdated(Tag, TagExists);
}