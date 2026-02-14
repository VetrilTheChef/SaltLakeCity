// SaltLakeCity 4.27

#include "BBNeedSetStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Net/UnrealNetwork.h"

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
}

void UBBNeedSetStub::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
}

void UBBNeedSetStub::BeginDestroy()
{
	Attributes.Empty();

	Super::BeginDestroy();
}

void UBBNeedSetStub::Initialize(UIBBAIAbilityComponent * AbilityComponent)
{
	Finalize(AbilityComponent);

	Subscribe(AbilityComponent);
}

void UBBNeedSetStub::Finalize(UIBBAIAbilityComponent * AbilityComponent)
{
	Unsubscribe(AbilityComponent);
}

void UBBNeedSetStub::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBBNeedSetStub, Hunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBNeedSetStub, Sleep, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBNeedSetStub, Thirst, COND_None, REPNOTIFY_Always);
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

float UBBNeedSetStub::GetValue(EBBNeed Need) const
{
	const FBBGetAttributeDelegate & Get = Attributes.FindChecked(Need).GetValue;

	return Get.IsBound() ? Get.Execute() : -1.0f;
}

void UBBNeedSetStub::SetValue(EBBNeed Need, float NewValue)
{
	Attributes.FindChecked(Need).SetValue.ExecuteIfBound(NewValue);
}

float UBBNeedSetStub::GetMaxValue(EBBNeed Need) const
{
	const FBBGetAttributeDelegate & GetMax = Attributes.FindChecked(Need).GetMaxValue;

	return GetMax.IsBound() ? GetMax.Execute() : -1.0f;
}

void UBBNeedSetStub::SetMaxValue(EBBNeed Need, float NewMaxValue)
{
	Attributes.FindChecked(Need).SetMaxValue.ExecuteIfBound(NewMaxValue);
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBNeedSetStub::GetValueDelegate(EBBNeed Need) const
{
	return Attributes.FindChecked(Need).GetValue;
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBNeedSetStub::GetMaxValueDelegate(EBBNeed Need) const
{
	return Attributes.FindChecked(Need).GetMaxValue;
}

UIBBBaseAttributeSet::FBBAttributeUpdate * UBBNeedSetStub::OnUpdate(EBBNeed Need) const
{
	return Attributes.FindChecked(Need).OnUpdate;
}



void UBBNeedSetStub::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBNeed::Hunger, BB_ATTRIBUTE_STRUCT(UBBNeedSetStub, Hunger));
	Attributes.Emplace(EBBNeed::Sleep, BB_ATTRIBUTE_STRUCT(UBBNeedSetStub, Sleep));
	Attributes.Emplace(EBBNeed::Thirst, BB_ATTRIBUTE_STRUCT(UBBNeedSetStub, Thirst));

	AttributeToEnum.Empty();
	AttributeToEnum.Emplace(GetHungerAttribute(), EBBNeed::Hunger);
	AttributeToEnum.Emplace(GetMaxHungerAttribute(), EBBNeed::Hunger);
	AttributeToEnum.Emplace(GetSleepAttribute(), EBBNeed::Sleep);
	AttributeToEnum.Emplace(GetMaxSleepAttribute(), EBBNeed::Sleep);
	AttributeToEnum.Emplace(GetThirstAttribute(), EBBNeed::Thirst);
	AttributeToEnum.Emplace(GetMaxThirstAttribute(), EBBNeed::Thirst);
}

void UBBNeedSetStub::Subscribe(UIBBAIAbilityComponent * AbilityComponent)
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHungerAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHungerAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetSleepAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxSleepAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetThirstAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxThirstAttribute()).AddUObject(this, & UBBNeedSetStub::UpdateAttribute);
}

void UBBNeedSetStub::Unsubscribe(UIBBAIAbilityComponent * AbilityComponent)
{
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
	EBBNeed AttributeToUpdate = AttributeToEnum.FindChecked(Data.Attribute);

	FBBAttribute & UpdatedAttribute = Attributes.FindChecked(AttributeToUpdate);

	float Value = UpdatedAttribute.GetValue.Execute();
	float MaxValue = UpdatedAttribute.GetMaxValue.Execute();

	if (UpdatedAttribute.OnUpdate)
	{
		UpdatedAttribute.OnUpdate->Broadcast(Value, MaxValue);
	}
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