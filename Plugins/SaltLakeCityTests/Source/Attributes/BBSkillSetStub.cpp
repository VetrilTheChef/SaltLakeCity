// SaltLakeCity 4.27

#include "BBSkillSetStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Net/UnrealNetwork.h"

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
	AttributeToEnum.Empty();
}

void UBBSkillSetStub::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
}

void UBBSkillSetStub::BeginDestroy()
{
	Attributes.Empty();
	AttributeToEnum.Empty();

	Super::BeginDestroy();
}

void UBBSkillSetStub::Initialize(UIBBAIAbilityComponent * AbilityComponent)
{
	Finalize(AbilityComponent);

	Subscribe(AbilityComponent);
}

void UBBSkillSetStub::Finalize(UIBBAIAbilityComponent * AbilityComponent)
{
	Unsubscribe(AbilityComponent);
}

void UBBSkillSetStub::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, Build, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, MaxBuild, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, Fuck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, MaxFuck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, Guard, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, MaxGuard, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, Lead, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, MaxLead, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, Research, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSetStub, MaxResearch, COND_None, REPNOTIFY_Always);
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

float UBBSkillSetStub::GetValue(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).GetValue.Execute();
}

void UBBSkillSetStub::SetValue(EBBSkill Skill, float NewValue)
{
	Attributes.FindChecked(Skill).SetValue.ExecuteIfBound(NewValue);
}

float UBBSkillSetStub::GetMaxValue(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).GetMaxValue.Execute();
}

void UBBSkillSetStub::SetMaxValue(EBBSkill Skill, float NewMaxValue)
{
	Attributes.FindChecked(Skill).SetMaxValue.ExecuteIfBound(NewMaxValue);
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBSkillSetStub::GetValueDelegate(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).GetValue;
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBSkillSetStub::GetMaxValueDelegate(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).GetMaxValue;
}

UIBBBaseAttributeSet::FBBAttributeUpdate * UBBSkillSetStub::OnUpdate(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).OnUpdate;
}


void UBBSkillSetStub::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBSkill::Build, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Build));
	Attributes.Emplace(EBBSkill::Fuck, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Fuck));
	Attributes.Emplace(EBBSkill::Guard, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Guard));
	Attributes.Emplace(EBBSkill::Lead, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Lead));
	Attributes.Emplace(EBBSkill::Research, BB_ATTRIBUTE_STRUCT(UBBSkillSetStub, Research));

	AttributeToEnum.Empty();
	AttributeToEnum.Emplace(GetBuildAttribute(), EBBSkill::Build);
	AttributeToEnum.Emplace(GetMaxBuildAttribute(), EBBSkill::Build);
	AttributeToEnum.Emplace(GetFuckAttribute(), EBBSkill::Fuck);
	AttributeToEnum.Emplace(GetMaxFuckAttribute(), EBBSkill::Fuck);
	AttributeToEnum.Emplace(GetGuardAttribute(), EBBSkill::Guard);
	AttributeToEnum.Emplace(GetMaxGuardAttribute(), EBBSkill::Guard);
	AttributeToEnum.Emplace(GetLeadAttribute(), EBBSkill::Lead);
	AttributeToEnum.Emplace(GetMaxLeadAttribute(), EBBSkill::Lead);
	AttributeToEnum.Emplace(GetResearchAttribute(), EBBSkill::Research);
	AttributeToEnum.Emplace(GetMaxResearchAttribute(), EBBSkill::Research);
}

void UBBSkillSetStub::Subscribe(UIBBAIAbilityComponent * AbilityComponent)
{
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

void UBBSkillSetStub::Unsubscribe(UIBBAIAbilityComponent * AbilityComponent)
{
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
	EBBSkill AttributeToUpdate = AttributeToEnum.FindChecked(Data.Attribute);

	FBBAttribute & UpdatedAttribute = Attributes.FindChecked(AttributeToUpdate);

	float Value = UpdatedAttribute.GetValue.Execute();
	float MaxValue = UpdatedAttribute.GetMaxValue.Execute();

	if (UpdatedAttribute.OnUpdate)
	{
		UpdatedAttribute.OnUpdate->Broadcast(Value, MaxValue);
	}
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