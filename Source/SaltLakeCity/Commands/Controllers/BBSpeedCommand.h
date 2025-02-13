// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBSpeedCommand.h"
#include "BBSpeedCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBSpeedCommand : public UIBBSpeedCommand
{
	GENERATED_BODY()

	public:
		UBBSpeedCommand();

		virtual void SetController(AIBBPlayerController * NewController) override;

		virtual float GetTimeDilation() override;

		virtual void SetTimeDilation(float NewTimeDilation) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBPlayerController * Controller;

		float TimeDilation;
};