// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Interfaces/IBBAttributeSet.h"
#include "BBAttributeSetStub.generated.h"

UCLASS(NotBlueprintable)

class UBBAttributeSetStub : public UIBBAttributeSet
{
	GENERATED_BODY()

	public:
		UBBAttributeSetStub();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override;

		virtual FGameplayAttribute GetAttribute(EBBAttribute Attribute) const override;

		virtual FGameplayAttribute GetMaxAttribute(EBBAttribute Attribute) const override;

		virtual float GetValue(EBBAttribute Attribute) const override;

		virtual void SetValue(EBBAttribute Attribute, float NewValue) override;

		virtual float GetMaxValue(EBBAttribute Attribute) const override;

		virtual void SetMaxValue(EBBAttribute Attribute, float NewValue) override;

		virtual FBBUpdate & OnValueUpdate(EBBAttribute Attribute) override { return (this->* (Attributes.FindChecked(Attribute).Update))(); }

		virtual FBBUpdate & OnMaxValueUpdate(EBBAttribute Attribute) override { return (this->* (Attributes.FindChecked(Attribute).MaxUpdate))(); }

	protected:
		UPROPERTY()
		FGameplayAttributeData Health;
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSetStub, Health)
			
		UPROPERTY()
		FGameplayAttributeData MaxHealth;
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSetStub, MaxHealth)
			
		UPROPERTY()
		FGameplayAttributeData Stamina;
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSetStub, Stamina)
			
		UPROPERTY()
		FGameplayAttributeData MaxStamina;
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSetStub, MaxStamina)

		TMap<EBBAttribute, FBBAttribute<UBBAttributeSetStub>> Attributes;

		using OnAttributeUpdate = FBBAttribute<UBBAttributeSetStub>::OnAttributeUpdate;

		TMap<FGameplayAttribute, OnAttributeUpdate> AttributeUpdates;

		using AttributeSetter = FBBAttribute<UBBAttributeSetStub>::AttributeSetter;

		TMap<FGameplayAttribute, AttributeSetter> AttributeSetters;

		void MapAttributes();

		void Subscribe();

		void Unsubscribe();

		void UpdateAttribute(const FOnAttributeChangeData & Data);

		UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData & OldHealth);

		UFUNCTION()
		virtual void OnRep_Stamina(const FGameplayAttributeData & OldStamina);

		UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData & OldMaxHealth);

		UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData & OldMaxStamina);

};