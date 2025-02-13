// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "Attributes/Interfaces/IBBAttributeSet.h"
#include "IBBCharacterAbilityComponent.generated.h"

class AIBBCharacter;

UCLASS(Abstract, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UIBBCharacterAbilityComponent : public UIBBAIAbilityComponent
{
	GENERATED_BODY()

	public:	
		UIBBCharacterAbilityComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(AIBBAIController * NewAIController, const TArray<FBBAttributeSetData> & AttributeSetsData) PURE_VIRTUAL(UIBBCharacterAbilityComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBCharacterAbilityComponent::Finalize, );

		virtual void SetAIController(AIBBAIController * NewAIController) override PURE_VIRTUAL(UIBBCharacterAbilityComponent::SetAIController, );
		
		virtual float GetNeed(EBBNeed Need) const PURE_VIRTUAL(UIBBCharacterAbilityComponent::GetNeed, return -1.0f; );

		virtual void SetNeed(EBBNeed Need, float NewValue) PURE_VIRTUAL(UIBBCharacterAbilityComponent::SetNeed, );

		virtual float GetSkill(EBBSkill Skill) const PURE_VIRTUAL(UIBBCharacterAbilityComponent::GetSkill, return -1.0f; );
		
		virtual void SetSkill(EBBSkill Skill, float NewValue) PURE_VIRTUAL(UIBBCharacterAbilityComponent::SetSkill, );

		virtual bool StartTask(UIBBAbilityTask * AbilityTask) override PURE_VIRTUAL(UIBBCharacterAbilityComponent::StartTask, return false; );

		virtual bool StopTask(UIBBAbilityTask * AbilityTask) override PURE_VIRTUAL(UIBBCharacterAbilityComponent::StopTask, return false; );

		virtual void RunBehaviorTree(UBehaviorTree * NewBehaviorTree, FName TreeTaskName, UIBBAbilityTask * TreeTask) override PURE_VIRTUAL(UIBBCharacterAbilityComponent::RunBehaviorTree, );
		
		virtual AIBBCharacter * GetCharacter() const PURE_VIRTUAL(UIBBCharacterAbilityComponent::GetCharacter, return nullptr; );
};