// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBAttributeEnum.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"
#include "IBBAttributeSet.generated.h"

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBAttributeSet : public UIBBBaseAttributeSet
{
	GENERATED_BODY()

	public:
		UIBBAttributeSet() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); }

		virtual void BeginDestroy() override { Super::BeginDestroy(); }

		virtual void Initialize(UIBBAIAbilityComponent * AbilityComponent) PURE_VIRTUAL(UIBBAttributeSet::Initialize, );

		virtual void Finalize(UIBBAIAbilityComponent * AbilityComponent) PURE_VIRTUAL(UIBBAttributeSet::Finalize, );

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override { Super::GetLifetimeReplicatedProps(OutLifetimeProps); };

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override { Super::PreAttributeChange(Attribute, NewValue); }

		virtual float GetValue(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetValue, return -1.0f; );

		virtual void SetValue(EBBAttribute Attribute, float NewValue) PURE_VIRTUAL(UIBBAttributeSet::SetValue, );

		virtual float GetMaxValue(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetMaxValue, return -1.0f; );

		virtual void SetMaxValue(EBBAttribute Attribute, float NewMaxValue) PURE_VIRTUAL(UIBBAttributeSet::SetMaxValue, );

		using FBBGetAttributeDelegate = UIBBBaseAttributeSet::FBBGetAttributeDelegate;

		virtual FBBGetAttributeDelegate GetValueDelegate(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetValueDelegate, return FBBGetAttributeDelegate(); );

		virtual FBBGetAttributeDelegate GetMaxValueDelegate(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetMaxValueDelegate, return FBBGetAttributeDelegate(); );

		using FBBAttributeUpdate = UIBBBaseAttributeSet::FBBAttributeUpdate;

		virtual FBBAttributeUpdate * OnUpdate(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::OnUpdate, return nullptr; );
};