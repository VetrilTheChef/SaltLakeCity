// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Interfaces/IBBAttributeSet.h"
#include "Misc/TVariant.h"
#include "BBAttributeSet.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBAttributeSet : public UIBBAttributeSet
{
	GENERATED_BODY()

	public:	
		UBBAttributeSet();

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
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSet, Health)
		
		UPROPERTY()
		FGameplayAttributeData MaxHealth;
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSet, MaxHealth)
		
		UPROPERTY()
		FGameplayAttributeData Stamina;
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSet, Stamina)
		
		UPROPERTY()
		FGameplayAttributeData MaxStamina;
		BB_ATTRIBUTE_ACCESSORS(UBBAttributeSet, MaxStamina)

		TMap<EBBAttribute, FBBAttribute<UBBAttributeSet>> Attributes;

		using OnAttributeUpdate = FBBAttribute<UBBAttributeSet>::OnAttributeUpdate;

		TMap<FGameplayAttribute, OnAttributeUpdate> AttributeUpdates;

		void InitValues();

		void InitMaxValues();

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