// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBSpeedCommand.h"
#include "BBSpeedCommandStub.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class UBBSpeedCommandStub : public UIBBSpeedCommand
{
	GENERATED_BODY()

	public:
		UBBSpeedCommandStub();

		virtual AIBBPlayerController * GetController();

		virtual void SetController(AIBBPlayerController * NewController) override;

		virtual float GetTimeDilation() override;

		virtual void SetTimeDilation(float NewTimeDilation) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		AIBBPlayerController * Controller;

		float TimeDilation;

		int Executions;
};