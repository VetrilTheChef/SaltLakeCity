// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"
#include "IBBSkillSet.generated.h"

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSkillSet : public UIBBBaseAttributeSet
{
	GENERATED_BODY()

	public:	
		UIBBSkillSet() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); }

		virtual void BeginDestroy() override { Super::BeginDestroy(); }

		virtual void Initialize(UIBBAIAbilityComponent * AbilityComponent) PURE_VIRTUAL(UIBBSkillSet::Initialize, );

		virtual void Finalize(UIBBAIAbilityComponent * AbilityComponent) PURE_VIRTUAL(UIBBSkillSet::Finalize, );

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override { Super::GetLifetimeReplicatedProps(OutLifetimeProps); };

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override { Super::PreAttributeChange(Attribute, NewValue); }

		virtual FGameplayAttribute GetAttribute(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetAttribute, return FGameplayAttribute(); );
		
		virtual FGameplayAttribute GetMaxAttribute(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetMaxAttribute, return FGameplayAttribute(); );

		virtual float GetValue(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetValue, return -1.0f; );
		
		virtual void SetValue(EBBSkill Skill, float NewValue) PURE_VIRTUAL(UIBBSkillSet::SetValue, );

		virtual float GetMaxValue(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetMaxValue, return -1.0f; );

		virtual void SetMaxValue(EBBSkill Skill, float NewValue) PURE_VIRTUAL(UIBBSkillSet::SetMaxValue, );

		using FBBGetAttributeDelegate = UIBBBaseAttributeSet::FBBGetAttributeDelegate;

		virtual FBBGetAttributeDelegate GetValueDelegate(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetValueDelegate, return FBBGetAttributeDelegate(); );

		virtual FBBGetAttributeDelegate GetMaxValueDelegate(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetMaxValueDelegate, return FBBGetAttributeDelegate(); );

		using FBBAttributeUpdate = UIBBBaseAttributeSet::FBBAttributeUpdate;

		virtual FBBAttributeUpdate * OnUpdate(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::OnUpdate, return nullptr; );
};