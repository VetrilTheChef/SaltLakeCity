// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/Subsystems/Interfaces/IBBUINotificationSubsystem.h"
#include "BBUINotificationSubsystemStub.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class UBBUINotificationSubsystemStub : public UIBBUINotificationSubsystem
{
	GENERATED_BODY()

	public:
		UBBUINotificationSubsystemStub();

		virtual void Initialize(FSubsystemCollectionBase& Collection) override;

		virtual void Deinitialize() override;
};