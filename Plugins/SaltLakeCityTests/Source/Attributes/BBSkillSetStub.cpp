// SaltLakeCity 4.27

#include "BBSkillSetStub.h"

UBBSkillSetStub::UBBSkillSetStub() :
	Super()
{
	InitBuild(-1.0f);
	InitFuck(-1.0f);
	InitGuard(-1.0f);
	InitLead(-1.0f);
	InitResearch(-1.0f);

	InitMaxBuild(-1.0f);
	InitMaxFuck(-1.0f);
	InitMaxGuard(-1.0f);
	InitMaxLead(-1.0f);
	InitMaxResearch(-1.0f);

	Attributes.Empty();
	AttributeUpdates.Empty();
	AttributeSetters.Empty();
}

void UBBSkillSetStub::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
	Subscribe();
}

void UBBSkillSetStub::BeginDestroy()
{
	Unsubscribe();
	Attributes.Empty();
	AttributeUpdates.Empty();
	AttributeSetters.Empty();

	Super::BeginDestroy();
}

void UBBSkillSetStub::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	// SWITCH ON ATTRIBUTE
	// CLAMP NEWVALUE
	/*
	switch (Attribute)
	{
		case GetHealthAttribute():
		{
			NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());

			break;
		}
	}
	*/
}

FGameplayAttribute UBBSkillSetStub::GetAttribute(EBBSkill Skill) const
{
	return (* (Attributes.FindChecked(Skill).Attribute))();
}

FGameplayAttribute UBBSkillSetStub::GetMaxAttribute(EBBSkill Skill) const
{
	return (* (Attributes.FindChecked(Skill).MaxAttribute))();
}

float UBBSkillSetStub::GetValue(EBBSkill Skill) const
{
	return (this->* (Attributes.FindChecked(Skill).Getter))();
}

void UBBSkillSetStub::SetValue(EBBSkill Skill, float NewValue)
{
	(this->* (Attributes.FindChecked(Skill).Setter))(NewValue);
}

float UBBSkillSetStub::GetMaxValue(EBBSkill Skill) const
{
	return (this->* (Attributes.FindChecked(Skill).MaxGetter))();
}

void UBBSkillSetStub::SetMaxValue(EBBSkill Skill, float NewValue)
{
	(this->* (Attributes.FindChecked(Skill).MaxSetter))(NewValue);
}


void UBBSkillSetStub::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBSkill::Build, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Build, MaxBuild));
	Attributes.Emplace(EBBSkill::Fuck, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Fuck, MaxFuck));
	Attributes.Emplace(EBBSkill::Guard, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Guard, MaxGuard));
	Attributes.Emplace(EBBSkill::Lead, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Lead, MaxLead));
	Attributes.Emplace(EBBSkill::Research, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Research, MaxResearch));

	AttributeUpdates.Empty();
	AttributeUpdates.Emplace(GetBuildAttribute(), & UBBSkillSetStub::OnBuildUpdate);
	AttributeUpdates.Emplace(GetMaxBuildAttribute(), & UBBSkillSetStub::OnMaxBuildUpdate);
	AttributeUpdates.Emplace(GetFuckAttribute(), & UBBSkillSetStub::OnFuckUpdate);
	AttributeUpdates.Emplace(GetMaxFuckAttribute(), & UBBSkillSetStub::OnMaxFuckUpdate);
	AttributeUpdates.Emplace(GetGuardAttribute(), & UBBSkillSetStub::OnGuardUpdate);
	AttributeUpdates.Emplace(GetMaxGuardAttribute(), & UBBSkillSetStub::OnMaxGuardUpdate);
	AttributeUpdates.Emplace(GetLeadAttribute(), & UBBSkillSetStub::OnLeadUpdate);
	AttributeUpdates.Emplace(GetMaxLeadAttribute(), & UBBSkillSetStub::OnMaxLeadUpdate);
	AttributeUpdates.Emplace(GetResearchAttribute(), & UBBSkillSetStub::OnResearchUpdate);
	AttributeUpdates.Emplace(GetMaxResearchAttribute(), & UBBSkillSetStub::OnMaxResearchUpdate);

	AttributeSetters.Empty();
	AttributeSetters.Emplace(GetBuildAttribute(), & UBBSkillSetStub::SetBuild);
	AttributeSetters.Emplace(GetMaxBuildAttribute(), & UBBSkillSetStub::SetMaxBuild);
	AttributeSetters.Emplace(GetFuckAttribute(), & UBBSkillSetStub::SetFuck);
	AttributeSetters.Emplace(GetMaxFuckAttribute(), & UBBSkillSetStub::SetMaxFuck);
	AttributeSetters.Emplace(GetGuardAttribute(), & UBBSkillSetStub::SetGuard);
	AttributeSetters.Emplace(GetMaxGuardAttribute(), & UBBSkillSetStub::SetMaxGuard);
	AttributeSetters.Emplace(GetLeadAttribute(), & UBBSkillSetStub::SetLead);
	AttributeSetters.Emplace(GetMaxLeadAttribute(), & UBBSkillSetStub::SetMaxLead);
	AttributeSetters.Emplace(GetResearchAttribute(), & UBBSkillSetStub::SetResearch);
	AttributeSetters.Emplace(GetMaxResearchAttribute(), & UBBSkillSetStub::SetMaxResearch);
}

void UBBSkillSetStub::Subscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetBuildAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxBuildAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetFuckAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxFuckAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetGuardAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxGuardAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetLeadAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxLeadAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetResearchAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxResearchAttribute()).AddUObject(this, & UBBSkillSetStub::UpdateAttribute);
}

void UBBSkillSetStub::Unsubscribe()
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

void UBBSkillSetStub::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	(this->* (AttributeSetters.FindChecked(Data.Attribute)))(Data.NewValue);

	(this->* (AttributeUpdates.FindChecked(Data.Attribute)))().Broadcast(Data.NewValue);
}

void UBBSkillSetStub::OnRep_Build(const FGameplayAttributeData & OldBuild)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, Build, OldBuild);
}

void UBBSkillSetStub::OnRep_MaxBuild(const FGameplayAttributeData & OldMaxBuild)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, MaxBuild, OldMaxBuild);
}

void UBBSkillSetStub::OnRep_Fuck(const FGameplayAttributeData & OldFuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, Fuck, OldFuck);
}

void UBBSkillSetStub::OnRep_MaxFuck(const FGameplayAttributeData & OldMaxFuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, MaxFuck, OldMaxFuck);
}

void UBBSkillSetStub::OnRep_Guard(const FGameplayAttributeData & OldGuard)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, Guard, OldGuard);
}

void UBBSkillSetStub::OnRep_MaxGuard(const FGameplayAttributeData & OldMaxGuard)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, MaxGuard, OldMaxGuard);
}

void UBBSkillSetStub::OnRep_Lead(const FGameplayAttributeData & OldLead)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, Lead, OldLead);
}

void UBBSkillSetStub::OnRep_MaxLead(const FGameplayAttributeData & OldMaxLead)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, MaxLead, OldMaxLead);
}

void UBBSkillSetStub::OnRep_Research(const FGameplayAttributeData & OldResearch)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, Research, OldResearch);
}

void UBBSkillSetStub::OnRep_MaxResearch(const FGameplayAttributeData & OldMaxResearch)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBSkillSetStub, MaxResearch, OldMaxResearch);
}