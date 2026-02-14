// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Interfaces/IBBSkillSet.h"
#include "BBSkillSet.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBSkillSet : public UIBBSkillSet
{
	GENERATED_BODY()

	public:	
		UBBSkillSet();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void Initialize(UIBBAIAbilityComponent * AbilityComponent) override;

		virtual void Finalize(UIBBAIAbilityComponent * AbilityComponent) override;

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override;

		virtual float GetValue(EBBSkill Skill) const override;

		virtual void SetValue(EBBSkill Skill, float NewValue) override;

		virtual float GetMaxValue(EBBSkill Skill) const override;

		virtual void SetMaxValue(EBBSkill Skill, float NewValue) override;

		virtual FBBGetAttributeDelegate GetValueDelegate(EBBSkill Skill) const override;

		virtual FBBGetAttributeDelegate GetMaxValueDelegate(EBBSkill Skill) const override;

		virtual FBBAttributeUpdate * OnUpdate(EBBSkill Skill) const override;

	protected:
		UPROPERTY()
		FGameplayAttributeData Build;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, Build)
		
		UPROPERTY()
		FGameplayAttributeData MaxBuild;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, MaxBuild)

		UPROPERTY()
		FGameplayAttributeData Fuck;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, Fuck)

		UPROPERTY()
		FGameplayAttributeData MaxFuck;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, MaxFuck)
		
		UPROPERTY()
		FGameplayAttributeData Guard;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, Guard)
		
		UPROPERTY()
		FGameplayAttributeData MaxGuard;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, MaxGuard)
		
		UPROPERTY()
		FGameplayAttributeData Lead;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, Lead)
		
		UPROPERTY()
		FGameplayAttributeData MaxLead;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, MaxLead)
		
		UPROPERTY()
		FGameplayAttributeData Research;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, Research)
		
		UPROPERTY()
		FGameplayAttributeData MaxResearch;
		BB_ATTRIBUTE_ACCESSORS(UBBSkillSet, MaxResearch)

		TMap<EBBSkill, FBBAttribute> Attributes;

		TMap<FGameplayAttribute, EBBSkill> AttributeToEnum;

		void InitValues();

		void InitMaxValues();

		void MapAttributes();

		void Subscribe(UIBBAIAbilityComponent * AbilityComponent);

		void Unsubscribe(UIBBAIAbilityComponent * AbilityComponent);

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