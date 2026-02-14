// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Interfaces/IBBNeedSet.h"
#include "BBNeedSetStub.generated.h"

UCLASS(NotBlueprintable)

class UBBNeedSetStub : public UIBBNeedSet
{
	GENERATED_BODY()

	public:
		UBBNeedSetStub();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void Initialize(UIBBAIAbilityComponent * AbilityComponent) override;

		virtual void Finalize(UIBBAIAbilityComponent * AbilityComponent) override;

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override;

		virtual float GetValue(EBBNeed Need) const override;

		virtual void SetValue(EBBNeed Need, float NewValue) override;

		virtual float GetMaxValue(EBBNeed Need) const override;

		virtual void SetMaxValue(EBBNeed Need, float NewMaxValue) override;

		virtual FBBGetAttributeDelegate GetValueDelegate(EBBNeed Need) const override;

		virtual FBBGetAttributeDelegate GetMaxValueDelegate(EBBNeed Need) const override;

		virtual FBBAttributeUpdate * OnUpdate(EBBNeed Need) const override;

	protected:
		UPROPERTY()
		FGameplayAttributeData Hunger;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSetStub, Hunger)

		UPROPERTY()
		FGameplayAttributeData MaxHunger;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSetStub, MaxHunger)
		
		UPROPERTY()
		FGameplayAttributeData Sleep;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSetStub, Sleep)
		
		UPROPERTY()
		FGameplayAttributeData MaxSleep;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSetStub, MaxSleep)
		
		UPROPERTY()
		FGameplayAttributeData Thirst;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSetStub, Thirst)
		
		UPROPERTY()
		FGameplayAttributeData MaxThirst;
		BB_ATTRIBUTE_ACCESSORS(UBBNeedSetStub, MaxThirst)

		TMap<EBBNeed, FBBAttribute> Attributes;

		TMap<FGameplayAttribute, EBBNeed> AttributeToEnum;

		virtual void MapAttributes();

		void Subscribe(UIBBAIAbilityComponent * AbilityComponent);

		void Unsubscribe(UIBBAIAbilityComponent * AbilityComponent);

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