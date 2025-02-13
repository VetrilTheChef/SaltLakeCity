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

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override { Super::GetLifetimeReplicatedProps(OutLifetimeProps); };

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override { Super::PreAttributeChange(Attribute, NewValue); }

		virtual FGameplayAttribute GetAttribute(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetAttribute, return FGameplayAttribute(); );

		virtual FGameplayAttribute GetMaxAttribute(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetMaxAttribute, return FGameplayAttribute(); );

		virtual float GetValue(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetValue, return -1.0f; );

		virtual void SetValue(EBBAttribute Attribute, float NewValue) PURE_VIRTUAL(UIBBAttributeSet::SetValue, );

		virtual float GetMaxValue(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAttributeSet::GetMaxValue, return -1.0f; );

		virtual void SetMaxValue(EBBAttribute Attribute, float NewValue) PURE_VIRTUAL(UIBBAttributeSet::SetMaxValue, );

		using FBBUpdate = UIBBBaseAttributeSet::FBBUpdate;

		virtual FBBUpdate & OnValueUpdate(EBBAttribute Attribute) PURE_VIRTUAL(UIBBAttributeSet::OnValueUpdate, checkNoEntry(); static FBBUpdate RetRef; return RetRef; );

		virtual FBBUpdate & OnMaxValueUpdate(EBBAttribute Attribute) PURE_VIRTUAL(UIBBAttributeSet::OnMaxValueUpdate, checkNoEntry(); static FBBUpdate RetRef; return RetRef; );
};