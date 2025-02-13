// SaltLakeCity 4.27

#include "BBAttributeSetStub.h"
#include "Net/UnrealNetwork.h"

UBBAttributeSetStub::UBBAttributeSetStub() :
	Super()
{
	InitHealth(-1.0f);
	InitStamina(-1.0f);

	Attributes.Empty();
	AttributeUpdates.Empty();
	AttributeSetters.Empty();
}

void UBBAttributeSetStub::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
	Subscribe();
}

void UBBAttributeSetStub::BeginDestroy()
{
	Unsubscribe();
	Attributes.Empty();
	AttributeUpdates.Empty();
	AttributeSetters.Empty();

	Super::BeginDestroy();
}

void UBBAttributeSetStub::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBBAttributeSetStub, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBAttributeSetStub, Stamina, COND_None, REPNOTIFY_Always);
};

void UBBAttributeSetStub::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
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

FGameplayAttribute UBBAttributeSetStub::GetAttribute(EBBAttribute Attribute) const
{
	return (* (Attributes.FindChecked(Attribute).Attribute))();
}

FGameplayAttribute UBBAttributeSetStub::GetMaxAttribute(EBBAttribute Attribute) const
{
	return (* (Attributes.FindChecked(Attribute).MaxAttribute))();
}

float UBBAttributeSetStub::GetValue(EBBAttribute Attribute) const
{
	return (this->* (Attributes.FindChecked(Attribute).Getter))();
}

void UBBAttributeSetStub::SetValue(EBBAttribute Attribute, float NewValue)
{
	(this->* (Attributes.FindChecked(Attribute).Setter))(NewValue);
}

float UBBAttributeSetStub::GetMaxValue(EBBAttribute Attribute) const
{
	return (this->* (Attributes.FindChecked(Attribute).MaxGetter))();
}

void UBBAttributeSetStub::SetMaxValue(EBBAttribute Attribute, float NewValue)
{
	(this->* (Attributes.FindChecked(Attribute).MaxSetter))(NewValue);
}



void UBBAttributeSetStub::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBAttribute::Health, BB_ATTRIBUTE_STRUCT(UBBAttributeSetStub, Health, MaxHealth));
	Attributes.Emplace(EBBAttribute::Stamina, BB_ATTRIBUTE_STRUCT(UBBAttributeSetStub, Stamina, MaxStamina));

	AttributeUpdates.Empty();
	AttributeUpdates.Emplace(GetHealthAttribute(), & UBBAttributeSetStub::OnHealthUpdate);
	AttributeUpdates.Emplace(GetMaxHealthAttribute(), & UBBAttributeSetStub::OnMaxHealthUpdate);
	AttributeUpdates.Emplace(GetStaminaAttribute(), & UBBAttributeSetStub::OnStaminaUpdate);
	AttributeUpdates.Emplace(GetMaxStaminaAttribute(), & UBBAttributeSetStub::OnMaxStaminaUpdate);

	AttributeSetters.Empty();
	AttributeSetters.Emplace(GetHealthAttribute(), & UBBAttributeSetStub::SetHealth);
	AttributeSetters.Emplace(GetMaxHealthAttribute(), & UBBAttributeSetStub::SetMaxStamina);
	AttributeSetters.Emplace(GetStaminaAttribute(), & UBBAttributeSetStub::SetStamina);
	AttributeSetters.Emplace(GetMaxStaminaAttribute(), & UBBAttributeSetStub::SetMaxStamina);
}

void UBBAttributeSetStub::Subscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHealthAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHealthAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetStaminaAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxStaminaAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
}

void UBBAttributeSetStub::Unsubscribe()
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

void UBBAttributeSetStub::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	(this->* (AttributeSetters.FindChecked(Data.Attribute)))(Data.NewValue);

	(this->* (AttributeUpdates.FindChecked(Data.Attribute)))().Broadcast(Data.NewValue);
}

void UBBAttributeSetStub::OnRep_Health(const FGameplayAttributeData & OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSetStub, Health, OldHealth);
}

void UBBAttributeSetStub::OnRep_Stamina(const FGameplayAttributeData & OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSetStub, Stamina, OldStamina);
}

void UBBAttributeSetStub::OnRep_MaxHealth(const FGameplayAttributeData & OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSetStub, MaxHealth, OldMaxHealth);
}

void UBBAttributeSetStub::OnRep_MaxStamina(const FGameplayAttributeData & OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBAttributeSetStub, MaxStamina, OldMaxStamina);
}