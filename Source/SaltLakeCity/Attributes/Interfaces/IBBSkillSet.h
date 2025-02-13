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

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override { Super::PreAttributeChange(Attribute, NewValue); }

		virtual FGameplayAttribute GetAttribute(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetAttribute, return FGameplayAttribute(); );
		
		virtual FGameplayAttribute GetMaxAttribute(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetMaxAttribute, return FGameplayAttribute(); );

		virtual float GetValue(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetValue, return -1.0f; );
		
		virtual void SetValue(EBBSkill Skill, float NewValue) PURE_VIRTUAL(UIBBSkillSet::SetValue, );

		virtual float GetMaxValue(EBBSkill Skill) const PURE_VIRTUAL(UIBBSkillSet::GetMaxValue, return -1.0f; );

		virtual void SetMaxValue(EBBSkill Skill, float NewValue) PURE_VIRTUAL(UIBBSkillSet::SetMaxValue, );

		using FBBUpdate = UIBBBaseAttributeSet::FBBUpdate;

		virtual FBBUpdate & OnValueUpdate(EBBSkill Skill) PURE_VIRTUAL(UIBBSkillSet::OnValueUpdate, checkNoEntry(); static FBBUpdate RetRef; return RetRef; );

		virtual FBBUpdate & OnMaxValueUpdate(EBBSkill Skill) PURE_VIRTUAL(UIBBSkillSet::OnMaxValueUpdate, checkNoEntry(); static FBBUpdate RetRef; return RetRef; );
};