// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"
#include "IBBNeedSet.generated.h"

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBNeedSet : public UIBBBaseAttributeSet
{
	GENERATED_BODY()

	public:	
		UIBBNeedSet() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); }

		virtual void BeginDestroy() override { Super::BeginDestroy(); }

		virtual void Initialize(UIBBAIAbilityComponent * AbilityComponent) PURE_VIRTUAL(UIBBNeedSet::Initialize, );

		virtual void Finalize(UIBBAIAbilityComponent * AbilityComponent) PURE_VIRTUAL(UIBBNeedSet::Finalize, );

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override { Super::GetLifetimeReplicatedProps(OutLifetimeProps); };

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override { Super::PreAttributeChange(Attribute, NewValue); }

		virtual float GetValue(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetValue, return -1.0f; );
		
		virtual void SetValue(EBBNeed Need, float NewValue) PURE_VIRTUAL(UIBBNeedSet::SetValue, );

		virtual float GetMaxValue(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetMaxValue, return -1.0f; );

		virtual void SetMaxValue(EBBNeed Need, float NewValue) PURE_VIRTUAL(UIBBNeedSet::SetMaxValue, );

		using FBBGetAttributeDelegate = UIBBBaseAttributeSet::FBBGetAttributeDelegate;

		virtual FBBGetAttributeDelegate GetValueDelegate(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetValueDelegate, return FBBGetAttributeDelegate(); );

		virtual FBBGetAttributeDelegate GetMaxValueDelegate(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetMaxValueDelegate, return FBBGetAttributeDelegate(); );

		using FBBAttributeUpdate = UIBBBaseAttributeSet::FBBAttributeUpdate;

		virtual FBBAttributeUpdate * OnUpdate(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::OnUpdate, return nullptr; );
};