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

		virtual void Initialize(UIBBAIAbilityComponent * AbilityComponent) override;

		virtual void Finalize(UIBBAIAbilityComponent * AbilityComponent) override;

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override;

		virtual float GetValue(EBBAttribute Attribute) const override;

		virtual void SetValue(EBBAttribute Attribute, float NewValue) override;

		virtual float GetMaxValue(EBBAttribute Attribute) const override;

		virtual void SetMaxValue(EBBAttribute Attribute, float NewMaxValue) override;

		virtual FBBGetAttributeDelegate GetValueDelegate(EBBAttribute Attribute) const override;

		virtual FBBGetAttributeDelegate GetMaxValueDelegate(EBBAttribute Attribute) const override;

		virtual FBBAttributeUpdate * OnUpdate(EBBAttribute Attribute) const override;

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

		TMap<EBBAttribute, FBBAttribute> Attributes;

		TMap<FGameplayAttribute, EBBAttribute> AttributeToEnum;

		void MapAttributes();

		void Subscribe(UIBBAIAbilityComponent * AbilityComponent);

		void Unsubscribe(UIBBAIAbilityComponent * AbilityComponent);

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