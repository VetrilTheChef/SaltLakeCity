// SaltLakeCity 4.27

#include "BBNeedSetStub.h"

UBBNeedSetStub::UBBNeedSetStub() :
	Super()
{
	InitHunger(-1.0f);
	InitSleep(-1.0f);
	InitThirst(-1.0f);

	InitMaxHunger(-1.0f);
	InitMaxSleep(-1.0f);
	InitMaxThirst(-1.0f);

	Attributes.Empty();
	AttributeUpdates.Empty();
	AttributeSetters.Empty();
}

void UBBNeedSetStub::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
	Subscribe();
}

void UBBNeedSetStub::BeginDestroy()
{
	Unsubscribe();
	Attributes.Empty();
	AttributeUpdates.Empty();
	AttributeSetters.Empty();

	Super::BeginDestroy();
}

void UBBNeedSetStub::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
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

FGameplayAttribute UBBNeedSetStub::GetAttribute(EBBNeed Need) const
{
	return (* (Attributes.FindChecked(Need).Attribute))();
}

FGameplayAttribute UBBNeedSetStub::GetMaxAttribute(EBBNeed Need) const
{
	return (* (Attributes.FindChecked(Need).MaxAttribute))();
}

float UBBNeedSetStub::GetValue(EBBNeed Need) const
{
	return (this->* (Attributes.FindChecked(Need).Getter))();
}

void UBBNeedSetStub::SetValue(EBBNeed Need, float NewValue)
{
	(this->* (Attributes.FindChecked(Need).Setter))(NewValue);
}

float UBBNeedSetStub::GetMaxValue(EBBNeed Need) const
{
	return (this->* (Attributes.FindChecked(Need).MaxGetter))();
}

void UBBNeedSetStub::SetMaxValue(EBBNeed Need, float NewValue)
{
	(this->* (Attributes.FindChecked(Need).MaxSetter))(NewValue);
}



void UBBNeedSetStub::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBNeed::Hunger, BB_ATTRIBUTE_STRUCT(UBBNeedSetStub, Hunger, MaxHunger));
	Attributes.Emplace(EBBNeed::Sleep, BB_ATTRIBUTE_STRUCT(UBBNeedSetStub, Sleep, MaxSleep));
	Attributes.Emplace(EBBNeed::Thirst, BB_ATTRIBUTE_STRUCT(UBBNeedSetStub, Thirst, MaxThirst));

	AttributeUpdates.Empty();
	AttributeUpdates.Emplace(GetHungerAttribute(), & UBBNeedSetStub::OnHungerUpdate);
	AttributeUpdates.Emplace(GetMaxHungerAttribute(), & UBBNeedSetStub::OnMaxHungerUpdate);
	AttributeUpdates.Emplace(GetSleepAttribute(), & UBBNeedSetStub::OnSleepUpdate);
	AttributeUpdates.Emplace(GetMaxSleepAttribute(), & UBBNeedSetStub::OnMaxSleepUpdate);
	AttributeUpdates.Emplace(GetThirstAttribute(), & UBBNeedSetStub::OnThirstUpdate);
	AttributeUpdates.Emplace(GetMaxThirstAttribute(), & UBBNeedSetStub::OnMaxThirstUpdate);

	AttributeSetters.Empty();
	AttributeSetters.Emplace(GetHungerAttribute(), & UBBNeedSetStub::SetHunger);
	AttributeSetters.Emplace(GetMaxHungerAttribute(), & UBBNeedSetStub::SetMaxHunger);
	AttributeSetters.Emplace(GetSleepAttribute(), & UBBNeedSetStub::SetSleep);
	AttributeSetters.Emplace(GetMaxSleepAttribute(), & UBBNeedSetStub::SetMaxSleep);
	AttributeSetters.Emplace(GetThirstAttribute(), & UBBNeedSetStub::SetThirst);
	AttributeSetters.Emplace(GetMaxThirstAttribute(), & UBBNeedSetStub::SetMaxThirst);
}

void UBBNeedSetStub::Subscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHungerAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHungerAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetSleepAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxSleepAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetThirstAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxThirstAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
}

void UBBNeedSetStub::Unsubscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	if (IsValid(AbilityComponent))
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHungerAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHungerAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetSleepAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxSleepAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetThirstAttribute()).RemoveAll(this);
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxThirstAttribute()).RemoveAll(this);
	}
}

void UBBNeedSetStub::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	(this->* (AttributeSetters.FindChecked(Data.Attribute)))(Data.NewValue);

	(this->* (AttributeUpdates.FindChecked(Data.Attribute)))().Broadcast(Data.NewValue);
}

void UBBNeedSetStub::OnRep_Hunger(const FGameplayAttributeData & OldHunger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSetStub, Hunger, OldHunger);
}

void UBBNeedSetStub::OnRep_MaxHunger(const FGameplayAttributeData & OldMaxHunger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSetStub, MaxHunger, OldMaxHunger);
}

void UBBNeedSetStub::OnRep_Sleep(const FGameplayAttributeData & OldSleep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSetStub, Sleep, OldSleep);
}

void UBBNeedSetStub::OnRep_MaxSleep(const FGameplayAttributeData & OldMaxSleep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSetStub, MaxSleep, OldMaxSleep);
}

void UBBNeedSetStub::OnRep_Thirst(const FGameplayAttributeData & OldThirst)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSetStub, Thirst, OldThirst);
}

void UBBNeedSetStub::OnRep_MaxThirst(const FGameplayAttributeData & OldMaxThirst)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSetStub, MaxThirst, OldMaxThirst);
}