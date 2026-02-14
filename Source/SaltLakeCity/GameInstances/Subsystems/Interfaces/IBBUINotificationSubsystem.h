// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IBBUINotificationSubsystem.generated.h"

/**
*
*/

DECLARE_DELEGATE_TwoParams(FBBListenerDelegate, FGameplayTag, const FInstancedStruct&);

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBUINotificationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	public:
		UIBBUINotificationSubsystem() : Super() { };

		virtual void Initialize(FSubsystemCollectionBase& Collection) override { Super::Initialize(Collection); };

		virtual void Deinitialize() override { Super::Deinitialize(); };

		template<typename TPayloadStructType, typename TListenerClass>
		FDelegateHandle RegisterListener(
			FGameplayTag EventTag,
			TListenerClass* Listener,
			void(TListenerClass::*Callback)(const TPayloadStructType&)
		)
		{
			static_assert(TPointerIsConvertibleFromTo<TListenerClass, UObject>::Value,
				"Listener Class must implement UObject.");

			FBBListenerDelegate Delegate;

			Delegate.BindStatic(&FBBTypedEventPayload<TPayloadStructType, TListenerClass>::OnEvent, Listener, Callback);

			return RegisterListenerInternal(EventTag, MoveTemp(Delegate));
		};

		virtual void UnregisterListener(FGameplayTag EventTag, FDelegateHandle Handle)
			PURE_VIRTUAL(UIBBPresentationSubsystem::UnregisterListener, );

		virtual void Broadcast(FGameplayTag EventTag, const FInstancedStruct& Payload)
			PURE_VIRTUAL(UIBBPresentationSubsystem::Broadcast, );

	protected:
		template <typename TStructType, typename TUserClass>
		struct FBBTypedEventPayload
		{
			typedef void (TUserClass::*ListenerCallback)(const TStructType&);

			static void OnEvent(
				FGameplayTag Tag,
				const FInstancedStruct& Payload,
				TUserClass* Listener,
				ListenerCallback Callback)
			{
				const TStructType* TypedPayload = Payload.GetPtr<TStructType>();

				if (ensureMsgf(
						TypedPayload,
						TEXT("Type Mismatch: Event Tag [%s] expected struct type [%s]."),
						*Tag.ToString(),
						*TStructType::StaticStruct()->GetName()
					))
				{
					(Listener->*Callback)(*TypedPayload);
				}
			}
		};

		virtual FDelegateHandle RegisterListenerInternal(FGameplayTag EventTag, FBBListenerDelegate&& Delegate)
			PURE_VIRTUAL(UIBBUINotificationSubsystem::RegisterListenerInternal, return FDelegateHandle(););

		DECLARE_EVENT_TwoParams(UIBBUINotificationSubsystem, FBBUIEvent, FGameplayTag, const FInstancedStruct&);

		void BroadcastInternal
		(
			const FBBUIEvent& Event,
			FGameplayTag EventTag,
			const FInstancedStruct& Payload
		)
		{
			Event.Broadcast(EventTag, Payload);
		}
};

Expose_TNameOf(UIBBUINotificationSubsystem);