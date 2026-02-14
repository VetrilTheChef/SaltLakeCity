// SaltLakeCity 4.27

#include "BBAttributeSetStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Net/UnrealNetwork.h"

UBBAttributeSetStub::UBBAttributeSetStub() :
	Super()
{
	InitHealth(-1.0f);
	InitStamina(-1.0f);

	Attributes.Empty();
	AttributeToEnum.Empty();
}

void UBBAttributeSetStub::PostInitProperties()
{
	Super::PostInitProperties();

	MapAttributes();
}

void UBBAttributeSetStub::BeginDestroy()
{
	Attributes.Empty();
	AttributeToEnum.Empty();

	Super::BeginDestroy();
}

void UBBAttributeSetStub::Initialize(UIBBAIAbilityComponent * AbilityComponent)
{
	Finalize(AbilityComponent);

	Subscribe(AbilityComponent);
}

void UBBAttributeSetStub::Finalize(UIBBAIAbilityComponent * AbilityComponent)
{
	Unsubscribe(AbilityComponent);
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

float UBBAttributeSetStub::GetValue(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).GetValue.Execute();
}

void UBBAttributeSetStub::SetValue(EBBAttribute Attribute, float NewValue)
{
	Attributes.FindChecked(Attribute).SetValue.ExecuteIfBound(NewValue);
}

float UBBAttributeSetStub::GetMaxValue(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).GetMaxValue.Execute();
}

void UBBAttributeSetStub::SetMaxValue(EBBAttribute Attribute, float NewMaxValue)
{
	Attributes.FindChecked(Attribute).SetMaxValue.ExecuteIfBound(NewMaxValue);
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBAttributeSetStub::GetValueDelegate(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).GetValue;
}

UIBBBaseAttributeSet::FBBGetAttributeDelegate UBBAttributeSetStub::GetMaxValueDelegate(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).GetMaxValue;
}

UIBBBaseAttributeSet::FBBAttributeUpdate * UBBAttributeSetStub::OnUpdate(EBBAttribute Attribute) const
{
	return Attributes.FindChecked(Attribute).OnUpdate;
}



void UBBAttributeSetStub::MapAttributes()
{
	Attributes.Empty();
	Attributes.Emplace(EBBAttribute::Health, BB_ATTRIBUTE_STRUCT(UBBAttributeSetStub, Health));
	Attributes.Emplace(EBBAttribute::Stamina, BB_ATTRIBUTE_STRUCT(UBBAttributeSetStub, Stamina));

	AttributeToEnum.Empty();
	AttributeToEnum.Emplace(GetHealthAttribute(), EBBAttribute::Health);
	AttributeToEnum.Emplace(GetMaxHealthAttribute(), EBBAttribute::Health);
	AttributeToEnum.Emplace(GetStaminaAttribute(), EBBAttribute::Stamina);
	AttributeToEnum.Emplace(GetMaxStaminaAttribute(), EBBAttribute::Stamina);
}

void UBBAttributeSetStub::Subscribe(UIBBAIAbilityComponent * AbilityComponent)
{
	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."))

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetHealthAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxHealthAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetStaminaAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetMaxStaminaAttribute()).AddUObject(this, & UBBAttributeSetStub::UpdateAttribute);
}

void UBBAttributeSetStub::Unsubscribe(UIBBAIAbilityComponent * AbilityComponent)
{
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
	EBBAttribute AttributeToUpdate = AttributeToEnum.FindChecked(Data.Attribute);

	FBBAttribute & UpdatedAttribute = Attributes.FindChecked(AttributeToUpdate);

	float Value = UpdatedAttribute.GetValue.Execute();
	float MaxValue = UpdatedAttribute.GetMaxValue.Execute();

	if (UpdatedAttribute.OnUpdate)
	{
		UpdatedAttribute.OnUpdate->Broadcast(Value, MaxValue);
	}
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