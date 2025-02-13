// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBPlayerAbilityComponent.h"
#include "GameplayAbilities/Public/GameplayAbilitySpec.h"
#include "BBPlayerAbilityComponent.generated.h"

class UIBBPlayerAbility;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBPlayerAbilityComponent : public UIBBPlayerAbilityComponent
{
	GENERATED_BODY()

	public:	
		UBBPlayerAbilityComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual TArray<TSubclassOf<UIBBPlayerAbility>> GetAbilityClasses() override;

		virtual void AddAbility(TSubclassOf<UIBBPlayerAbility> NewPlayerAbilityClass) override;

		virtual void ClearAbilities() override;

		virtual bool RequestAbility(UIBBAbilityData * NewAbilityData) override;

	protected:
		UPROPERTY(Category = "Abilities", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<UIBBPlayerAbility>> AbilityClasses;

		virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists);
};