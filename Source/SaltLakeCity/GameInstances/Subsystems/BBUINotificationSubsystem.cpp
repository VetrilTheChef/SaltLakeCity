// SaltLakeCity 5.7

#include "BBUINotificationSubsystem.h"

UBBUINotificationSubsystem::UBBUINotificationSubsystem() :
	Super()
{
}

void UBBUINotificationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBBUINotificationSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBBUINotificationSubsystem::UnregisterListener(FGameplayTag EventTag, FDelegateHandle Handle)
{
	if (FBBUIEvent* Event = Events.Find(EventTag))
	{
		Event->Remove(Handle);
	}
}

void UBBUINotificationSubsystem::Broadcast(FGameplayTag EventTag, const FInstancedStruct& Payload)
{
	if (FBBUIEvent* Event = Events.Find(EventTag))
	{
		BroadcastInternal(*Event, EventTag, Payload);
	}
}



FDelegateHandle UBBUINotificationSubsystem::RegisterListenerInternal
(
	FGameplayTag EventTag,
	FBBListenerDelegate&& Delegate
)
{
	FBBUIEvent& Event = Events.FindOrAdd(EventTag);

	return Event.Add(MoveTemp(Delegate));
}
