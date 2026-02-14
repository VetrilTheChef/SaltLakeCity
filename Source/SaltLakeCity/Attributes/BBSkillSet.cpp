// SaltLakeCity 4.27

#include "BBSkillSet.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Net/UnrealNetwork.h"

UBBSkillSet::UBBSkillSet() :
	Super()
{
	InitValues();
	InitMaxValues();

	Attributes.Empty();
	AttributeToEnum.Empty();
}

void UBBSkillSet::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
}

void UBBSkillSet::BeginDestroy()
{
	Attributes.Empty();
	AttributeToEnum.Empty();

	Super::BeginDestroy();
}

void UBBSkillSet::Initialize(UIBBAIAbilityComponent * AbilityComponent)
{
	Finalize(AbilityComponent);

	Subscribe(AbilityComponent);
}

void UBBSkillSet::Finalize(UIBBAIAbilityComponent * AbilityComponent)
{
	Unsubscribe(AbilityComponent);
}

void UBBSkillSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, Build, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, MaxBuild, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, Fuck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, MaxFuck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, Guard, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, MaxGuard, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, Lead, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, MaxLead, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, Research, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBSkillSet, MaxResearch, COND_None, REPNOTIFY_Always);
}

void UBBSkillSet::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	//NewValue = FMath::Clamp(NewValue, 0.0f, 10.0f);
}

float UBBSkillSet::GetValue(EBBSkill Skill) const
{
	const FBBGetAttributeDelegate & Get = Attributes.FindChecked(Skill).GetValue;

	return Get.IsBound() ? Get.Execute() : -1.0f;
}

void UBBSkillSet::SetValue(EBBSkill Skill, float NewValue)
{
	Attributes.FindChecked(Skill).SetValue.ExecuteIfBound(NewValue);
}

float UBBSkillSet::GetMaxValue(EBBSkill Skill) const
{
	const FBBGetAttributeDelegate & GetMax = Attributes.FindChecked(Skill).GetMaxValue;

	return GetMax.IsBound() ? GetMax.Execute() : -1.0f;
}

void UBBSkillSet::SetMaxValue(EBBSkill Skill, float NewMaxValue)
{
	Attributes.FindChecked(Skill).SetMaxValue.ExecuteIfBound(NewMaxValue);
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBSkillSet::GetValueDelegate(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).GetValue;
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBSkillSet::GetMaxValueDelegate(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).GetMaxValue;
}

UIBBBaseAttributeSet::FBBAttributeUpdate * UBBSkillSet::OnUpdate(EBBSkill Skill) const
{
	return Attributes.FindChecked(Skill).OnUpdate;
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
	Attributes.Emplace(EBBSkill::Build, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Build));
	Attributes.Emplace(EBBSkill::Fuck, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Fuck));
	Attributes.Emplace(EBBSkill::Guard, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Guard));
	Attributes.Emplace(EBBSkill::Lead, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Lead));
	Attributes.Emplace(EBBSkill::Research, BB_ATTRIBUTE_STRUCT(UBBSkillSet, Research));

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

void UBBSkillSet::Subscribe(UIBBAIAbilityComponent * AbilityComponent)
{
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

void UBBSkillSet::Unsubscribe(UIBBAIAbilityComponent * AbilityComponent)
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

void UBBSkillSet::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	EBBSkill AttributeToUpdate = AttributeToEnum.FindChecked(Data.Attribute);

	FBBAttribute & UpdatedAttribute = Attributes.FindChecked(AttributeToUpdate);

	verifyf(UpdatedAttribute.GetValue.IsBound(), TEXT("Value Delegate is unbound."));
	verifyf(UpdatedAttribute.GetMaxValue.IsBound(), TEXT("Max Value Delegate is unbound."));

	float Value = UpdatedAttribute.GetValue.Execute();
	float MaxValue = UpdatedAttribute.GetMaxValue.Execute();

	verifyf(UpdatedAttribute.OnUpdate, TEXT("On Update is null."));

	UpdatedAttribute.OnUpdate->Broadcast(Value, MaxValue);
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
