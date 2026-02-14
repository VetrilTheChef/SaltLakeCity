// SaltLakeCity 5.7

#include "BBAttributeSet.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Net/UnrealNetwork.h"

UBBAttributeSet::UBBAttributeSet() :
	Super()
{
	InitValues();
	InitMaxValues();

	Attributes.Empty();
	AttributeToEnum.Empty();
}

void UBBAttributeSet::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
}

void UBBAttributeSet::BeginDestroy()
{
	Attributes.Empty();
	AttributeToEnum.Empty();

	Super::BeginDestroy();
}

void UBBAttributeSet::Initialize(UIBBAIAbilityComponent * AbilityComponent)
{
	Finalize(AbilityComponent);

	Subscribe(AbilityComponent);
}

void UBBAttributeSet::Finalize(UIBBAIAbilityComponent * AbilityComponent)
{
	Unsubscribe(AbilityComponent);
}

void UBBAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBBAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
}

void UBBAttributeSet::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
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

float UBBAttributeSet::GetValue(EBBAttribute Attribute) const
{
	const FBBGetAttributeDelegate & Get = Attributes.FindChecked(Attribute).GetValue;

	return Get.IsBound() ? Get.Execute() : -1.0f;
}

void UBBAttributeSet::SetValue(EBBAttribute Attribute, float NewValue)
{
	Attributes.FindChecked(Attribute).SetValue.ExecuteIfBound(NewValue);
}

float UBBAttributeSet::GetMaxValue(EBBAttribute Attribute) const
{
	const FBBGetAttributeDelegate & GetMax = Attributes.FindChecked(Attribute).GetMaxValue;

	return GetMax.IsBound() ? GetMax.Execute() : -1.0f;
}

void UBBAttributeSet::SetMaxValue(EBBAttribute Attribute, float NewMaxValue)
{
	Attributes.FindChecked(Attribute).SetMaxValue.ExecuteIfBound(NewMaxValue);
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBAttributeSet::GetValueDelegate(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).GetValue;
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBAttributeSet::GetMaxValueDelegate(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).GetMaxValue;
}

UIBBBaseAttributeSet::FBBAttributeUpdate * UBBAttributeSet::OnUpdate(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).OnUpdate;
}



void UBBAttributeSet::InitValues()
{
	InitHealth(-1.0f);
	InitStamina(-1.0f);
}

void UBBAttributeSet::InitMaxValues()
{
	InitMaxHealth(-1.0f);
	InitMaxStamina(-1.0f);
}

void UBBAttributeSet::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBAttribute::Health, BB_ATTRIBUTE_STRUCT(UBBAttributeSet, Health));
	Attributes.Emplace(EBBAttribute::Stamina, BB_ATTRIBUTE_STRUCT(UBBAttributeSet, Stamina));

	AttributeToEnum.Empty();
	AttributeToEnum.Emplace(GetHealthAttribute(), EBBAttribute::Health);
	AttributeToEnum.Emplace(GetMaxHealthAttribute(), EBBAttribute::Health);
	AttributeToEnum.Emplace(GetStaminaAttribute(), EBBAttribute::Stamina);
	AttributeToEnum.Emplace(GetMaxStaminaAttribute(), EBBAttribute::Stamina);
}

void UBBAttributeSet::Subscribe(UIBBAIAbilityComponent * AbilityComponent)
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHealthAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHealthAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetStaminaAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxStaminaAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
}

void UBBAttributeSet::Unsubscribe(UIBBAIAbilityComponent * AbilityComponent)
{
	if (IsValid(AbilityComponent))
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHealthAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHealthAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetStaminaAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxStaminaAttribute()).RemoveAll(this);
	}
}

void UBBAttributeSet::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	EBBAttribute AttributeToUpdate = AttributeToEnum.FindChecked(Data.Attribute);

	FBBAttribute & UpdatedAttribute = Attributes.FindChecked(AttributeToUpdate);

	verifyf(UpdatedAttribute.GetValue.IsBound(), TEXT("Value Delegate is unbound."));
	verifyf(UpdatedAttribute.GetMaxValue.IsBound(), TEXT("Max Value Delegate is unbound."));

	float Value = UpdatedAttribute.GetValue.Execute();
	float MaxValue = UpdatedAttribute.GetMaxValue.Execute();

	verifyf(UpdatedAttribute.OnUpdate, TEXT("On Update is null."));

	UpdatedAttribute.OnUpdate->Broadcast(Value, MaxValue);
}

void UBBAttributeSet::OnRep_Health(const FGameplayAttributeData & OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSet, Health, OldHealth);
}

void UBBAttributeSet::OnRep_Stamina(const FGameplayAttributeData & OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSet, Stamina, OldStamina);
}

void UBBAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData & OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSet, MaxHealth, OldMaxHealth);
}

void UBBAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData & OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSet, MaxStamina, OldMaxStamina);
}