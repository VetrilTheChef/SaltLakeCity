// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Commands/Interfaces/IBBCommand.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBSetJobCommand.generated.h"

/**
 * 
 */

class UIBBWorkComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSetJobCommand : public UIBBCommand
{
	GENERATED_BODY()

	public:
		UIBBSetJobCommand() : Super() { };

		virtual UIBBWorkComponent * GetWorkComponent() const PURE_VIRTUAL(UIBBSetJobCommand::GetWorkComponent, return nullptr; );

		virtual void SetWorkComponent(UIBBWorkComponent * NewWorkComponent) PURE_VIRTUAL(UIBBSetJobCommand::SetWorkComponent, );

		virtual EBBJob GetJob() const PURE_VIRTUAL(UIBBSetJobCommand::GetJob, return EBBJob::None; );

		virtual void SetJob(EBBJob NewJob) PURE_VIRTUAL(UIBBSetJobCommand::SetJob, );

		virtual void Execute() override PURE_VIRTUAL(UIBBSetJobCommand::Execute, );
};