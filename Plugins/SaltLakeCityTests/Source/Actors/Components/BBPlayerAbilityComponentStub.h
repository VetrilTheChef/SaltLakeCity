// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBPlayerAbilityComponent.h"
#include "GameplayAbilities/Public/GameplayAbilitySpec.h"
#include "BBPlayerAbilityComponentStub.generated.h"

class UIBBPlayerAbility;

UCLASS(NotBlueprintable)

class UBBPlayerAbilityComponentStub : public UIBBPlayerAbilityComponent
{
	GENERATED_BODY()

	public:	
		UBBPlayerAbilityComponentStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual TArray<TSubclassOf<UIBBPlayerAbility>> GetAbilityClasses() override;

		virtual void AddAbility(TSubclassOf<UIBBPlayerAbility> NewPlayerAbilityClass) override;

		virtual void ClearAbilities() override;

		virtual bool RequestAbility(UIBBAbilityData * NewAbilityData) override;

		virtual void TargetConfirm() override;

		int GetNumTargetConfirmations();

		virtual void TargetCancel() override;

		int GetNumTargetCancellations();

		UIBBAbilityData * GetRequestedAbilityData();

	protected:
		UPROPERTY()
		UIBBAbilityData * RequestedAbilityData;

		int TargetConfirmCalls;

		int TargetCancelCalls;
};