// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Jobs/Interfaces/IBBSetJobCommand.h"
#include "BBSetJobCommandStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBSetJobCommandStub : public UIBBSetJobCommand
{
	GENERATED_BODY()

	public:
		UBBSetJobCommandStub();

		virtual UIBBWorkComponent * GetWorkComponent() const override;

		virtual void SetWorkComponent(UIBBWorkComponent * NewWorkComponent) override;

		virtual EBBJob GetJob() const override;

		virtual void SetJob(EBBJob NewJob) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		UIBBWorkComponent * WorkComponent;

		EBBJob Job;

		int Executions;
};