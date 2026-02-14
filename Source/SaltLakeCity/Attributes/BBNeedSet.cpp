// SaltLakeCity 4.27

#include "BBNeedSet.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Net/UnrealNetwork.h"

UBBNeedSet::UBBNeedSet() :
	Super()
{
	InitValues();
	InitMaxValues();

	Attributes.Empty();
	AttributeToEnum.Empty();
}

void UBBNeedSet::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
}

void UBBNeedSet::BeginDestroy()
{
	Attributes.Empty();
	AttributeToEnum.Empty();

	Super::BeginDestroy();
}

void UBBNeedSet::Initialize(UIBBAIAbilityComponent * AbilityComponent)
{
	Finalize(AbilityComponent);

	Subscribe(AbilityComponent);
}

void UBBNeedSet::Finalize(UIBBAIAbilityComponent * AbilityComponent)
{
	Unsubscribe(AbilityComponent);
}

void UBBNeedSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBBNeedSet, Hunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBNeedSet, Sleep, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBBNeedSet, Thirst, COND_None, REPNOTIFY_Always);
}

void UBBNeedSet::PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue)
{
	//NewValue = FMath::Clamp(NewValue, 0.0f, 10.0f);
}

float UBBNeedSet::GetValue(EBBNeed Need) const
{
	const FBBGetAttributeDelegate & Get = Attributes.FindChecked(Need).GetValue;

	return Get.IsBound() ? Get.Execute() : -1.0f;
}

void UBBNeedSet::SetValue(EBBNeed Need, float NewValue)
{
	Attributes.FindChecked(Need).SetValue.ExecuteIfBound(NewValue);
}

float UBBNeedSet::GetMaxValue(EBBNeed Need) const
{
	const FBBGetAttributeDelegate & GetMax = Attributes.FindChecked(Need).GetMaxValue;

	return GetMax.IsBound() ? GetMax.Execute() : -1.0f;
}

void UBBNeedSet::SetMaxValue(EBBNeed Need, float NewMaxValue)
{
	Attributes.FindChecked(Need).SetMaxValue.ExecuteIfBound(NewMaxValue);
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBNeedSet::GetValueDelegate(EBBNeed Need) const
{
	return Attributes.FindChecked(Need).GetValue;
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBNeedSet::GetMaxValueDelegate(EBBNeed Need) const
{
	return Attributes.FindChecked(Need).GetMaxValue;
}

UIBBBaseAttributeSet::FBBAttributeUpdate * UBBNeedSet::OnUpdate(EBBNeed Need) const
{
	return Attributes.FindChecked(Need).OnUpdate;
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
	Attributes.Emplace(EBBNeed::Hunger, BB_ATTRIBUTE_STRUCT(UBBNeedSet, Hunger));
	Attributes.Emplace(EBBNeed::Sleep, BB_ATTRIBUTE_STRUCT(UBBNeedSet, Sleep));
	Attributes.Emplace(EBBNeed::Thirst, BB_ATTRIBUTE_STRUCT(UBBNeedSet, Thirst));

	AttributeToEnum.Empty();
	AttributeToEnum.Emplace(GetHungerAttribute(), EBBNeed::Hunger);
	AttributeToEnum.Emplace(GetMaxHungerAttribute(), EBBNeed::Hunger);
	AttributeToEnum.Emplace(GetSleepAttribute(), EBBNeed::Sleep);
	AttributeToEnum.Emplace(GetMaxSleepAttribute(), EBBNeed::Sleep);
	AttributeToEnum.Emplace(GetThirstAttribute(), EBBNeed::Thirst);
	AttributeToEnum.Emplace(GetMaxThirstAttribute(), EBBNeed::Thirst);
}

void UBBNeedSet::Subscribe(UIBBAIAbilityComponent * AbilityComponent)
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHungerAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHungerAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetSleepAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxSleepAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetThirstAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxThirstAttribute()).AddUObject(this, & UBBNeedSet::UpdateAttribute);
}

void UBBNeedSet::Unsubscribe(UIBBAIAbilityComponent * AbilityComponent)
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

void UBBNeedSet::UpdateAttribute(const FOnAttributeChangeData & Data)
{
	EBBNeed AttributeToUpdate = AttributeToEnum.FindChecked(Data.Attribute);

	FBBAttribute & UpdatedAttribute = Attributes.FindChecked(AttributeToUpdate);

	verifyf(UpdatedAttribute.GetValue.IsBound(), TEXT("Value Delegate is unbound."));
	verifyf(UpdatedAttribute.GetMaxValue.IsBound(), TEXT("Max Value Delegate is unbound."));

	float Value = UpdatedAttribute.GetValue.Execute();
	float MaxValue = UpdatedAttribute.GetMaxValue.Execute();

	verifyf(UpdatedAttribute.OnUpdate, TEXT("On Update is null."));

	UpdatedAttribute.OnUpdate->Broadcast(Value, MaxValue);
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