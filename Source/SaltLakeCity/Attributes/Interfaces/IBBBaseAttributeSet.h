// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "IBBBaseAttributeSet.generated.h"

class UIBBAIAbilityComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	public:	
		UIBBBaseAttributeSet() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); }

		virtual void BeginDestroy() override { Super::BeginDestroy(); }

		virtual void Initialize(UIBBAIAbilityComponent* AbilityComponent)
			PURE_VIRTUAL(UIBBBaseAttributeSet::Initialize, );

		virtual void Finalize(UIBBAIAbilityComponent* AbilityComponent)
			PURE_VIRTUAL(UIBBBaseAttributeSet::Finalize, );

		DECLARE_DELEGATE_RetVal(float, FBBGetAttributeDelegate);

		DECLARE_DELEGATE_OneParam(FBBSetAttributeDelegate, float);

		DECLARE_EVENT_TwoParams(UIBBBaseAttributeSet, FBBAttributeUpdate, float, float);
};

#define BB_GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	static FGameplayAttribute Get##PropertyName##Attribute() \
	{ \
		static FProperty* Prop = FindFieldChecked<FProperty>( \
			ClassName::StaticClass(), \
			GET_MEMBER_NAME_CHECKED(ClassName, PropertyName) \
		); \
		return Prop; \
	}

#define BB_GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	FORCEINLINE float Get##PropertyName() const \
	{ \
		return PropertyName.GetCurrentValue(); \
	}

#define BB_GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	FORCEINLINE void Set##PropertyName(float NewValue) \
	{ \
		UAbilitySystemComponent* AbilityComponent = GetOwningAbilitySystemComponent(); \
		verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid.")) \
		AbilityComponent->SetNumericAttributeBase(Get##PropertyName##Attribute(), NewValue); \
	}

#define BB_GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
	FORCEINLINE void Init##PropertyName(float NewValue) \
	{ \
		PropertyName.SetBaseValue(NewValue); \
		PropertyName.SetCurrentValue(NewValue); \
	}

#define BB_GAMEPLAYATTRIBUTE_VALUE_CHANGE_DELEGATE(PropertyName) \
	FORCEINLINE FOnGameplayAttributeValueChange& Get##PropertyName##ValueChangeDelegate() \
	{ \
		UAbilitySystemComponent* AbilityComponent = GetOwningAbilitySystemComponent(); \
		verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid.")) \
		return AbilityComponent->GetGameplayAttributeValueChangeDelegate(Get##PropertyName##Attribute()); \
	}

#define BB_GAMEPLAYATTRIBUTE_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \
	virtual FBBAttributeUpdate& On##PropertyName##Update() { return PropertyName##Update; } \

#define BB_GAMEPLAYATTRIBUTE_UPDATE_EVENT(PropertyName) \
	FBBAttributeUpdate PropertyName##Update; \

#define BB_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \

#define BB_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_CHANGE_DELEGATE(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_UPDATE_EVENT(PropertyName) \

#define BB_ATTRIBUTE_STRUCT(ClassName, PropertyName) \
    FBBAttribute(FBBGetAttributeDelegate::CreateUObject(this, &ClassName::Get##PropertyName), \
        FBBSetAttributeDelegate::CreateUObject(this, &ClassName::Set##PropertyName), \
        FBBGetAttributeDelegate::CreateUObject(this, &ClassName::GetMax##PropertyName), \
        FBBSetAttributeDelegate::CreateUObject(this, &ClassName::SetMax##PropertyName), \
        &PropertyName##Update) \

struct FBBAttribute
{
	public:
		using FBBGetAttributeDelegate = UIBBBaseAttributeSet::FBBGetAttributeDelegate;

		using FBBSetAttributeDelegate = UIBBBaseAttributeSet::FBBSetAttributeDelegate;
		
		using FBBAttributeUpdate = UIBBBaseAttributeSet::FBBAttributeUpdate;

		FBBGetAttributeDelegate GetValue;

		FBBSetAttributeDelegate SetValue;

		FBBGetAttributeDelegate GetMaxValue;

		FBBSetAttributeDelegate SetMaxValue;

		FBBAttributeUpdate* OnUpdate;

		FBBAttribute(FBBGetAttributeDelegate NewGetValueDelegate,
			FBBSetAttributeDelegate NewSetValueDelegate,
			FBBGetAttributeDelegate NewGetMaxValueDelegate,
			FBBSetAttributeDelegate NewSetMaxValueDelegate,
			FBBAttributeUpdate* NewOnUpdate) :
			GetValue(NewGetValueDelegate),
			SetValue(NewSetValueDelegate),
			GetMaxValue(NewGetMaxValueDelegate),
			SetMaxValue(NewSetMaxValueDelegate),
			OnUpdate(NewOnUpdate)
		{ }

		~FBBAttribute()
		{ }
};