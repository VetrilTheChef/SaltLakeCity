// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/Subsystems/Interfaces/IBBUINotificationSubsystem.h"
#include "BBUINotificationSubsystem.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBUINotificationSubsystem : public UIBBUINotificationSubsystem
{
	GENERATED_BODY()

	public:
		UBBUINotificationSubsystem();

		virtual void Initialize(FSubsystemCollectionBase& Collection) override;

		virtual void Deinitialize() override;

		virtual void UnregisterListener(FGameplayTag EventTag, FDelegateHandle Handle) override;

		virtual void Broadcast(FGameplayTag EventTag, const FInstancedStruct& Payload) override;

	protected:
		virtual FDelegateHandle RegisterListenerInternal
		(
			FGameplayTag EventTag,
			FBBListenerDelegate&& Delegate
		) override;

		TMap<FGameplayTag, FBBUIEvent> Events;
};