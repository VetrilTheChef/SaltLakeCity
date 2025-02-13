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

		virtual void PreAttributeChange(const FGameplayAttribute & Attribute, float & NewValue) override { Super::PreAttributeChange(Attribute, NewValue); }

		virtual FGameplayAttribute GetAttribute(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetAttribute, return FGameplayAttribute(); );
		
		virtual FGameplayAttribute GetMaxAttribute(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetMaxAttribute, return FGameplayAttribute(); );

		virtual float GetValue(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetValue, return -1.0f; );
		
		virtual void SetValue(EBBNeed Need, float NewValue) PURE_VIRTUAL(UIBBNeedSet::SetValue, );

		virtual float GetMaxValue(EBBNeed Need) const PURE_VIRTUAL(UIBBNeedSet::GetMaxValue, return -1.0f; );

		virtual void SetMaxValue(EBBNeed Need, float NewValue) PURE_VIRTUAL(UIBBNeedSet::SetMaxValue, );

		using FBBUpdate = UIBBBaseAttributeSet::FBBUpdate;

		virtual FBBUpdate & OnValueUpdate(EBBNeed Need) PURE_VIRTUAL(UIBBNeedSet::OnValueUpdate, checkNoEntry(); static FBBUpdate RetRef; return RetRef; );

		virtual FBBUpdate & OnMaxValueUpdate(EBBNeed Need) PURE_VIRTUAL(UIBBNeedSet::OnMaxValueUpdate, checkNoEntry(); static FBBUpdate RetRef; return RetRef; );
};