// SaltLakeCity 4.27

#include "BBSkillSet.h"

UBBSkillSet::UBBSkillSet() :
	Super()
{
	InitValues();
	InitMaxValues();

	Attributes.Empty();
	AttributeUpdates.Empty();
}

void UBBSkillSet::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
	Subscribe();
}

void UBBSkillSet::BeginDestroy()
{
	Unsubscribe();
	Attributes.Empty();
	AttributeUpdates.Empty();

	Super::BeginDestroy();
}

void UBBSkillSet::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	//NewValue = FMath::Clamp(NewValue, 0.0f, 10.0f);
}

FGameplayAttribute UBBSkillSet::GetAttribute(EBBSkill Skill) const
{
	return (* (Attributes.FindChecked(Skill).Attribute))();
}

FGameplayAttribute UBBSkillSet::GetMaxAttribute(EBBSkill Skill) const
{
	return (* (Attributes.FindChecked(Skill).MaxAttribute))();
}

float UBBSkillSet::GetValue(EBBSkill Skill) const
{
	return (this->* Attributes.FindChecked(Skill).Getter)();
}

void UBBSkillSet::SetValue(EBBSkill Skill, float NewValue)
{
	(this->* Attributes.FindChecked(Skill).Setter)(NewValue);
}

float UBBSkillSet::GetMaxValue(EBBSkill Skill) const
{
	return (this->* Attributes.FindChecked(Skill).MaxGetter)();
}

void UBBSkillSet::SetMaxValue(EBBSkill Skill, float NewMaxValue)
{
	(this->* Attributes.FindChecked(Skill).MaxSetter)(NewMaxValue);
}



void UBBSkillSet::InitValues()
{
	InitBuild(-1.0f);
	InitFuck(-1.0f);
	InitGuard(-1.0f);
	InitLead(-1.0f);
	InitResearch(-1.0f);
}

void UBBSkillSet::InitMaxValues()
{
	InitMaxBuild(-1.0f);
	InitMaxFuck(-1.0f);
	InitMaxGuard(-1.0f);
	InitMaxLead(-1.0f);
	InitMaxResearch(-1.0f);
}

void UBBSkillSet::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBSkill::Build, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Build, MaxBuild));
	Attributes.Emplace(EBBSkill::Fuck, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Fuck, MaxFuck));
	Attributes.Emplace(EBBSkill::Guard, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Guard, MaxGuard));
	Attributes.Emplace(EBBSkill::Lead, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Lead, MaxLead));
	Attributes.Emplace(EBBSkill::Research, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Research, MaxResearch));

	AttributeUpdates.Empty();
	AttributeUpdates.Emplace(GetBuildAttribute(), & UBBSkillSet::OnBuildUpdate);
	AttributeUpdates.Emplace(GetMaxBuildAttribute(), & UBBSkillSet::OnMaxBuildUpdate);
	AttributeUpdates.Emplace(GetFuckAttribute(), & UBBSkillSet::OnFuckUpdate);
	AttributeUpdates.Emplace(GetMaxFuckAttribute(), & UBBSkillSet::OnMaxFuckUpdate);
	AttributeUpdates.Emplace(GetGuardAttribute(), & UBBSkillSet::OnGuardUpdate);
	AttributeUpdates.Emplace(GetMaxGuardAttribute(), & UBBSkillSet::OnMaxGuardUpdate);
	AttributeUpdates.Emplace(GetLeadAttribute(), & UBBSkillSet::OnLeadUpdate);
	AttributeUpdates.Emplace(GetMaxLeadAttribute(), & UBBSkillSet::OnMaxLeadUpdate);
	AttributeUpdates.Emplace(GetResearchAttribute(), & UBBSkillSet::OnResearchUpdate);
	AttributeUpdates.Emplace(GetMaxResearchAttribute(), & UBBSkillSet::OnMaxResearchUpdate);
}

void UBBSkillSet::Subscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetBuildAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxBuildAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetFuckAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxFuckAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetGuardAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxGuardAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetLeadAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxLeadAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetResearchAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxResearchAttribute()).AddUObject(this, & UBBSkillSet::UpdateAttribute);
}

void UBBSkillSet::Unsubscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	if (IsValid(AbilityComponent))
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetBuildAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxBuildAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetFuckAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxFuckAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetGuardAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxGuardAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetLeadAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxLeadAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetResearchAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxResearchAttribute()).RemoveAll(this);
	}
}

void UBBSkillSet::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	(this->* (AttributeUpdates.FindChecked(Data.Attribute)))().Broadcast(Data.NewValue);
}

void UBBSkillSet::OnRep_Build(const FGameplayAttributeData & OldBuild)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, Build, OldBuild);
}

void UBBSkillSet::OnRep_MaxBuild(const FGameplayAttributeData & OldMaxBuild)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, MaxBuild, OldMaxBuild);
}

void UBBSkillSet::OnRep_Fuck(const FGameplayAttributeData & OldFuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, Fuck, OldFuck);
}

void UBBSkillSet::OnRep_MaxFuck(const FGameplayAttributeData & OldMaxFuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, MaxFuck, OldMaxFuck);
}

void UBBSkillSet::OnRep_Guard(const FGameplayAttributeData & OldGuard)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, Guard, OldGuard);
}

void UBBSkillSet::OnRep_MaxGuard(const FGameplayAttributeData & OldMaxGuard)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, MaxGuard, OldMaxGuard);
}

void UBBSkillSet::OnRep_Lead(const FGameplayAttributeData & OldLead)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, Lead, OldLead);
}

void UBBSkillSet::OnRep_MaxLead(const FGameplayAttributeData & OldMaxLead)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, MaxLead, OldMaxLead);
}

void UBBSkillSet::OnRep_Research(const FGameplayAttributeData & OldResearch)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, Research, OldResearch);
}

void UBBSkillSet::OnRep_MaxResearch(const FGameplayAttributeData & OldMaxResearch)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSet, MaxResearch, OldMaxResearch);
}
