// SaltLakeCity 4.27

#include "BBNeedSet.h"

UBBNeedSet::UBBNeedSet() :
	Super()
{
	InitValues();
	InitMaxValues();

	Attributes.Empty();
	AttributeUpdates.Empty();
}

void UBBNeedSet::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
	Subscribe();
}

void UBBNeedSet::BeginDestroy()
{
	Unsubscribe();
	Attributes.Empty();
	AttributeUpdates.Empty();

	Super::BeginDestroy();
}

void UBBNeedSet::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	//NewValue = FMath::Clamp(NewValue, 0.0f, 10.0f);
}

FGameplayAttribute UBBNeedSet::GetAttribute(EBBNeed Need) const
{
	return (* (Attributes.FindChecked(Need).Attribute))();
}

FGameplayAttribute UBBNeedSet::GetMaxAttribute(EBBNeed Need) const
{
	return (* (Attributes.FindChecked(Need).MaxAttribute))();
}

float UBBNeedSet::GetValue(EBBNeed Need) const
{
	return (this->* Attributes.FindChecked(Need).Getter)();
}

void UBBNeedSet::SetValue(EBBNeed Need, float NewValue)
{
	(this->* Attributes.FindChecked(Need).Setter)(NewValue);
}

float UBBNeedSet::GetMaxValue(EBBNeed Need) const
{
	return (this->* Attributes.FindChecked(Need).MaxGetter)();
}

void UBBNeedSet::SetMaxValue(EBBNeed Need, float NewMaxValue)
{
	(this->* Attributes.FindChecked(Need).MaxSetter)(NewMaxValue);
}



void UBBNeedSet::InitValues()
{
	InitHunger(-1.0f);
	InitSleep(-1.0f);
	InitThirst(-1.0f);
}

void UBBNeedSet::InitMaxValues()
{
	InitMaxHunger(-1.0f);
	InitMaxSleep(-1.0f);
	InitMaxThirst(-1.0f);
}

void UBBNeedSet::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBNeed::Hunger, BB_ATTRIBUTE_STRUCT(UBBNeedSet, Hunger, MaxHunger));
	Attributes.Emplace(EBBNeed::Sleep, BB_ATTRIBUTE_STRUCT(UBBNeedSet, Sleep, MaxSleep));
	Attributes.Emplace(EBBNeed::Thirst, BB_ATTRIBUTE_STRUCT(UBBNeedSet, Thirst, MaxThirst));

	AttributeUpdates.Empty();
	AttributeUpdates.Emplace(GetHungerAttribute(), & UBBNeedSet::OnHungerUpdate);
	AttributeUpdates.Emplace(GetMaxHungerAttribute(), & UBBNeedSet::OnMaxHungerUpdate);
	AttributeUpdates.Emplace(GetSleepAttribute(), & UBBNeedSet::OnSleepUpdate);
	AttributeUpdates.Emplace(GetMaxSleepAttribute(), & UBBNeedSet::OnMaxSleepUpdate);
	AttributeUpdates.Emplace(GetThirstAttribute(), & UBBNeedSet::OnThirstUpdate);
	AttributeUpdates.Emplace(GetMaxThirstAttribute(), & UBBNeedSet::OnMaxThirstUpdate);
}

void UBBNeedSet::Subscribe()
{
	UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent();

	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHungerAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHungerAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetSleepAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxSleepAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetThirstAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxThirstAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
}

void UBBNeedSet::Unsubscribe()
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

void UBBNeedSet::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	(this->* (AttributeUpdates.FindChecked(Data.Attribute)))().Broadcast(Data.NewValue);
}

void UBBNeedSet::OnRep_Hunger(const FGameplayAttributeData & OldHunger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSet, Hunger, OldHunger);
}

void UBBNeedSet::OnRep_MaxHunger(const FGameplayAttributeData & OldMaxHunger)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSet, MaxHunger, OldMaxHunger);
}

void UBBNeedSet::OnRep_Sleep(const FGameplayAttributeData & OldSleep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSet, Sleep, OldSleep);
}

void UBBNeedSet::OnRep_MaxSleep(const FGameplayAttributeData & OldMaxSleep)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSet, MaxSleep, OldMaxSleep);
}

void UBBNeedSet::OnRep_Thirst(const FGameplayAttributeData & OldThirst)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSet, Thirst, OldThirst);
}

void UBBNeedSet::OnRep_MaxThirst(const FGameplayAttributeData & OldMaxThirst)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBBNeedSet, MaxThirst, OldMaxThirst);
}