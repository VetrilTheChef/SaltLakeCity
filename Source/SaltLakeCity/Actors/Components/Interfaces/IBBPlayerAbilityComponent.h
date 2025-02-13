// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "IBBPlayerAbilityComponent.generated.h"

class UIBBAbilityData;
class UIBBPlayerAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIBBPlayerAbilityComponent_QueueJob, const UIBBAbilityData *, AbilityData);

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBPlayerAbilityComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	public:
		UIBBPlayerAbilityComponent() : Super() { };

		virtual TArray<TSubclassOf<UIBBPlayerAbility>> GetAbilityClasses() PURE_VIRTUAL(UIBBPlayerAbilityComponent::GetAbilityClasses, return TArray<TSubclassOf<UIBBPlayerAbility>>(); );

		virtual void AddAbility(TSubclassOf<UIBBPlayerAbility> NewPlayerAbilityClass) PURE_VIRTUAL(UIBBPlayerAbilityComponent::GiveAbility, );

		virtual void ClearAbilities() PURE_VIRTUAL(UIBBPlayerAbilityComponent::ClearAbilities, );

		virtual bool RequestAbility(UIBBAbilityData * NewAbilityData) PURE_VIRTUAL(UIBBPlayerAbilityComponent::RequestAbility, return false; );

		FIBBPlayerAbilityComponent_QueueJob OnJobQueued;
};