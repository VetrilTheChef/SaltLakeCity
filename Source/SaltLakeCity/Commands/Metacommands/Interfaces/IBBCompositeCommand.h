// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "Commands/Interfaces/IBBCommand.h"
#include "IBBCompositeCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBCompositeCommand : public UIBBCommand
{
	GENERATED_BODY()

	public:
		UIBBCompositeCommand() : Super() { };

		virtual int Add(UIBBCommand * Command) PURE_VIRTUAL(&UIBBCompositeCommand::Add, return -1; );

		virtual int Remove(UIBBCommand * Command) PURE_VIRTUAL(&UIBBCompositeCommand::Remove, return -1; );

		virtual void Empty() PURE_VIRTUAL(&UIBBCompositeCommand::Empty, );

		virtual void Execute() override PURE_VIRTUAL(&UIBBCompositeCommand::Execute, );
};