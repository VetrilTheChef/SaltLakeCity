// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Interfaces/IBBSkillSet.h"
#include "BBSkillSetStub.generated.h"

UCLASS(NotBlueprintable)

class UBBSkillSetStub : public UIBBSkillSet
{
	GENERATED_BODY()

	public:
		UBBSkillSetStub();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override;

		virtual FGameplayAttribute GetAttribute(EBBSkill Skill) const override;

		virtual FGameplayAttribute GetMaxAttribute(EBBSkill Skill) const override;

		virtual float GetValue(EBBSkill Skill) const override;

		virtual void SetValue(EBBSkill Skill, float NewValue) override;

		virtual float GetMaxValue(EBBSkill Skill) const override;

		virtual void SetMaxValue(EBBSkill Skill, float NewValue) override;

		using FBBUpdate = UIBBBaseAttributeSet::FBBUpdate;

		virtual FBBUpdate & OnValueUpdate(EBBSkill Skill) override { return (this->* (Attributes.FindChecked(Skill).Update))(); }

		virtual FBBUpdate & OnMaxValueUpdate(EBBSkill Skill) override { return (this->* (Attributes.FindChecked(Skill).MaxUpdate))(); }

	protected:
		UPROPERTY()
		FGameplayAttributeData Build;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, Build)
		
		UPROPERTY()
		FGameplayAttributeData MaxBuild;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, MaxBuild)

		UPROPERTY()
		FGameplayAttributeData Fuck;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, Fuck)

		UPROPERTY()
		FGameplayAttributeData MaxFuck;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, MaxFuck)
		
		UPROPERTY()
		FGameplayAttributeData Guard;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, Guard)
		
		UPROPERTY()
		FGameplayAttributeData MaxGuard;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, MaxGuard)
		
		UPROPERTY()
		FGameplayAttributeData Lead;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, Lead)
		
		UPROPERTY()
		FGameplayAttributeData MaxLead;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, MaxLead)
		
		UPROPERTY()
		FGameplayAttributeData Research;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, Research)
		
		UPROPERTY()
		FGameplayAttributeData MaxResearch;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSetStub, MaxResearch)

		TMap<EBBSkill, FBBAttribute<UBBSkillSetStub>> Attributes;

		using OnAttributeUpdate = FBBAttribute <UBBSkillSetStub>::OnAttributeUpdate;

		TMap<FGameplayAttribute, OnAttributeUpdate> AttributeUpdates;

		using AttributeSetter = FBBAttribute<UBBSkillSetStub>::AttributeSetter;

		TMap<FGameplayAttribute, AttributeSetter> AttributeSetters;

		virtual void MapAttributes();

		void Subscribe();

		void Unsubscribe();

		void UpdateAttribute(const FOnAttributeChangeData & Data);

		UFUNCTION()
		virtual void OnRep_Build(const FGameplayAttributeData & OldBuild);

		UFUNCTION()
		virtual void OnRep_MaxBuild(const FGameplayAttributeData & OldMaxBuild);

		UFUNCTION()
		virtual void OnRep_Fuck(const FGameplayAttributeData & OldFuck);

		UFUNCTION()
		virtual void OnRep_MaxFuck(const FGameplayAttributeData & OldMaxFuck);

		UFUNCTION()
		virtual void OnRep_Guard(const FGameplayAttributeData & OldGuard);

		UFUNCTION()
		virtual void OnRep_MaxGuard(const FGameplayAttributeData & OldMaxGuard);

		UFUNCTION()
		virtual void OnRep_Lead(const FGameplayAttributeData & OldLead);

		UFUNCTION()
		virtual void OnRep_MaxLead(const FGameplayAttributeData & OldMaxLead);

		UFUNCTION()
		virtual void OnRep_Research(const FGameplayAttributeData & OldResearch);

		UFUNCTION()
		virtual void OnRep_MaxResearch(const FGameplayAttributeData & OldMaxResearch);
};