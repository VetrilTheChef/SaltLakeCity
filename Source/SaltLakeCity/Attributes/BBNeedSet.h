// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Interfaces/IBBNeedSet.h"
#include "BBNeedSet.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBNeedSet : public UIBBNeedSet
{
	GENERATED_BODY()

	public:	
		UBBNeedSet();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override;

		virtual FGameplayAttribute GetAttribute(EBBNeed Need) const override;

		virtual FGameplayAttribute GetMaxAttribute(EBBNeed Need) const override;

		virtual float GetValue(EBBNeed Need) const override;

		virtual void SetValue(EBBNeed Need, float NewValue) override;

		virtual float GetMaxValue(EBBNeed Need) const override;

		virtual void SetMaxValue(EBBNeed Need, float NewValue) override;

		virtual FBBUpdate & OnValueUpdate(EBBNeed Need) override { return (this->* (Attributes.FindChecked(Need).Update))(); }

		virtual FBBUpdate & OnMaxValueUpdate(EBBNeed Need) override { return (this->* (Attributes.FindChecked(Need).MaxUpdate))(); }

	protected:
		UPROPERTY()
		FGameplayAttributeData Hunger;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSet, Hunger)
		
		UPROPERTY()
		FGameplayAttributeData MaxHunger;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSet, MaxHunger)
		
		UPROPERTY()
		FGameplayAttributeData Sleep;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSet, Sleep)
		
		UPROPERTY()
		FGameplayAttributeData MaxSleep;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSet, MaxSleep)
		
		UPROPERTY()
		FGameplayAttributeData Thirst;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSet, Thirst)
		
		UPROPERTY()
		FGameplayAttributeData MaxThirst;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSet, MaxThirst)

		TMap<EBBNeed, FBBAttribute<UBBNeedSet>> Attributes;

		using OnAttributeUpdate = FBBAttribute <UBBNeedSet>::OnAttributeUpdate;

		TMap<FGameplayAttribute, OnAttributeUpdate> AttributeUpdates;

		void InitValues();

		void InitMaxValues();

		void MapAttributes();

		void Subscribe();

		void Unsubscribe();

		void UpdateAttribute(const FOnAttributeChangeData & Data);

		UFUNCTION()
		virtual void OnRep_Hunger(const FGameplayAttributeData & OldHunger);

		UFUNCTION()
		virtual void OnRep_MaxHunger(const FGameplayAttributeData & OldMaxHunger);

		UFUNCTION()
		virtual void OnRep_Sleep(const FGameplayAttributeData & OldSleep);

		UFUNCTION()
		virtual void OnRep_MaxSleep(const FGameplayAttributeData & OldMaxSleep);

		UFUNCTION()
		virtual void OnRep_Thirst(const FGameplayAttributeData & OldThirst);

		UFUNCTION()
		virtual void OnRep_MaxThirst(const FGameplayAttributeData & OldMaxThirst);
};