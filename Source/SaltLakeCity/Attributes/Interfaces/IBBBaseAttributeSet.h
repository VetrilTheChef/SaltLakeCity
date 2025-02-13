// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "IBBBaseAttributeSet.generated.h"


UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	public:	
		UIBBBaseAttributeSet() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); }

		virtual void BeginDestroy() override { Super::BeginDestroy(); }

		DECLARE_EVENT_OneParam(UIBBBaseAttributeSet, FBBUpdate, float);
};

#define BB_GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	static FGameplayAttribute Get##PropertyName##Attribute() \
	{ \
		static FProperty * Prop = FindFieldChecked<FProperty>(ClassName::StaticClass(), GET_MEMBER_NAME_CHECKED(ClassName, PropertyName)); \
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
	FORCEINLINE FOnGameplayAttributeValueChange & Get##PropertyName##ValueChangeDelegate() \
	{ \
		UAbilitySystemComponent * AbilityComponent = GetOwningAbilitySystemComponent(); \
		verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid.")) \
		return AbilityComponent->GetGameplayAttributeValueChangeDelegate(Get##PropertyName##Attribute()); \
	}

#define BB_GAMEPLAYATTRIBUTE_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \
	virtual FBBUpdate & On##PropertyName##Update() { return PropertyName##Update; } \

#define BB_GAMEPLAYATTRIBUTE_VALUE_UPDATE(PropertyName) \
	FBBUpdate PropertyName##Update; \

#define BB_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \

#define BB_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_CHANGE_DELEGATE(PropertyName) \
	BB_GAMEPLAYATTRIBUTE_ON_ATTRIBUTE_UPDATE_EVENT(ClassName, PropertyName) \
	BB_GAMEPLAYATTRIBUTE_VALUE_UPDATE(PropertyName) \

#define BB_ATTRIBUTE_STRUCT(ClassName, PropertyName, MaxPropertyName) \
	FBBAttribute<ClassName> \
		(& ClassName##::Get##PropertyName##Attribute, \
		 & ClassName##::Get##MaxPropertyName##Attribute, \
		 & ClassName##::Get##PropertyName, \
		 & ClassName##::Set##PropertyName, \
		 & ClassName##::Get##MaxPropertyName, \
		 & ClassName##::Set##MaxPropertyName, \
		 & ClassName##::On##PropertyName##Update, \
		 & ClassName##::On##MaxPropertyName##Update) \

template <class T>
struct FBBAttribute
{
	typedef FGameplayAttribute(*AttributePropertyGetter) ();

	typedef float (T::* AttributeGetter) () const;

	typedef void (T::* AttributeSetter) (float NewValue);

	typedef UIBBBaseAttributeSet::FBBUpdate & (T::* OnAttributeUpdate) ();

	public:
		AttributePropertyGetter Attribute;

		AttributePropertyGetter MaxAttribute;

		AttributeGetter Getter;

		AttributeSetter Setter;

		AttributeGetter MaxGetter;

		AttributeSetter MaxSetter;

		OnAttributeUpdate Update;

		OnAttributeUpdate MaxUpdate;

		FBBAttribute(AttributePropertyGetter NewAttribute,
			AttributePropertyGetter NewMaxAttribute,
			AttributeGetter NewGetter,
			AttributeSetter NewSetter,
			AttributeGetter NewMaxGetter,
			AttributeSetter NewMaxSetter,
			OnAttributeUpdate NewUpdate,
			OnAttributeUpdate NewMaxUpdate) :
			Attribute(NewAttribute),
			MaxAttribute(NewMaxAttribute),
			Getter(NewGetter),
			Setter(NewSetter),
			MaxGetter(NewMaxGetter),
			MaxSetter(NewMaxSetter),
			Update(NewUpdate),
			MaxUpdate(NewMaxUpdate)
		{ }

		~FBBAttribute()
		{ }
};