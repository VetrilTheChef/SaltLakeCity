// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "BBAIAbilityComponent.generated.h"

class UIBBAIAbility;
class UIBBAbilitiesAttributeSet;
class UIBBAttributeSet;
class UIBBNeedSet;
class UIBBSkillSet;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBAIAbilityComponent : public UIBBAIAbilityComponent
{
	GENERATED_BODY()

	public:	
		UBBAIAbilityComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(AIBBAIController * NewAIController, const TArray<FBBAttributeSetData> & SetsData) override;

		virtual void Finalize() override;

		virtual void SetAIController(AIBBAIController * NewAIController) override;

		virtual const TArray<FBBAttributeSetData> GetAttributeSetsData() const override;

		virtual float GetNeed(EBBNeed Need) const override;

		virtual void SetNeed(EBBNeed Need, float NewValue) override;

		virtual float GetSkill(EBBSkill Skill) const override;

		virtual void SetSkill(EBBSkill Skill, float NewValue) override;

		virtual bool StartTask(UIBBAbilityTask * AbilityTask) override;

		virtual bool StopTask(UIBBAbilityTask * AbilityTask) override;

		virtual bool IsRunningTask() const override;

		virtual void RunBehaviorTree(UBehaviorTree * NewBehaviorTree, FName TreeTaskName, UIBBAbilityTask * TreeTask) override;

	protected:
		UPROPERTY(Category = "Attribute Sets", EditAnywhere, BlueprintReadWrite)
		TArray<FBBAttributeSetData> AttributeSetsData;

		UPROPERTY(Category = "Abilities", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<UIBBAIAbility>> AbilityClasses;

		UPROPERTY()
		AIBBAIController * AIController;

		UPROPERTY()
		UIBBAbilityTask * CurrentAbilityTask;

		void CreateAttributes(UClass * AttributeSetClass, UDataTable * AttributeSetDataTable);

		void DestroyAttributes();

		void InitializeAttributes(UIBBAIAbilityComponent * AbilityComponent);

		void FinalizeAttributes(UIBBAIAbilityComponent * AbilityComponent);

		void GiveAbilities();

		void ClearAbilities();

		virtual void OnTagUpdated(const FGameplayTag & Tag, bool TagExists);
};