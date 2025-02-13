// SaltLakeCity 4.27

#include "BBAttributeSet.h"
#include "Net/UnrealNetwork.h"

UBBAttributeSet::UBBAttributeSet() :
	Super()
{
	InitValues();
	InitMaxValues();

	Attributes.Empty();
	AttributeUpdates.Empty();
}

void UBBAttributeSet::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
	Subscribe();
}

void UBBAttributeSet::BeginDestroy()
{
	Unsubscribe();
	Attributes.Empty();
	AttributeUpdates.Empty();

	Super::BeginDestroy();
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

FGameplayAttribute UBBAttributeSet::GetAttribute(EBBAttribute Attribute) const
{
	return (* (Attributes.FindChecked(Attribute).Attribute))();
}

FGameplayAttribute UBBAttributeSet::GetMaxAttribute(EBBAttribute Attribute) const
{
	return (* (Attributes.FindChecked(Attribute).MaxAttribute))();
}

float UBBAttributeSet::GetValue(EBBAttribute Attribute) const
{
	return (this->* (Attributes.FindChecked(Attribute).Getter))();
}

void UBBAttributeSet::SetValue(EBBAttribute Attribute, float NewValue)
{
	(this->* (Attributes.FindChecked(Attribute).Setter))(NewValue);
}

float UBBAttributeSet::GetMaxValue(EBBAttribute Attribute) const
{
	return (this->* (Attributes.FindChecked(Attribute).MaxGetter))();
}

void UBBAttributeSet::SetMaxValue(EBBAttribute Attribute, float NewValue)
{
	(this->* (Attributes.FindChecked(Attribute).MaxSetter))(NewValue);
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
	Attributes.Emplace(EBBAttribute::Health, BB_ATTRIBUTE_STRUCT(UBBAttributeSet, Health, MaxHealth));
	Attributes.Emplace(EBBAttribute::Stamina, BB_ATTRIBUTE_STRUCT(UBBAttributeSet, Stamina, MaxStamina));

	AttributeUpdates.Empty();
	AttributeUpdates.Emplace(GetHealthAttribute(), & UBBAttributeSet::OnHealthUpdate);
	AttributeUpdates.Emplace(GetMaxHealthAttribute(), & UBBAttributeSet::OnMaxHealthUpdate);
	AttributeUpdates.Emplace(GetStaminaAttribute(), & UBBAttributeSet::OnStaminaUpdate);
	AttributeUpdates.Emplace(GetMaxStaminaAttribute(), & UBBAttributeSet::OnMaxStaminaUpdate);
}

void UBBAttributeSet::Subscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHealthAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHealthAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetStaminaAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxStaminaAttribute()).AddUObject(this, & UBBAttributeSet::UpdateAttribute);
}

void UBBAttributeSet::Unsubscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

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
	(this->* (AttributeUpdates.FindChecked(Data.Attribute)))().Broadcast(Data.NewValue);
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