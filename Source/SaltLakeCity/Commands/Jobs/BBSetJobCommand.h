// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Jobs/Interfaces/IBBSetJobCommand.h"
#include "BBSetJobCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBSetJobCommand : public UIBBSetJobCommand
{
	GENERATED_BODY()

	public:
		UBBSetJobCommand();

		virtual UIBBWorkComponent * GetWorkComponent() const override;

		virtual void SetWorkComponent(UIBBWorkComponent * NewWorkComponent) override;

		virtual EBBJob GetJob() const override;

		virtual void SetJob(EBBJob NewJob) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		UIBBWorkComponent * WorkComponent;

		EBBJob Job;
};