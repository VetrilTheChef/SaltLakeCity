// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "IBBCommand.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBCommand : public UObject
{
	GENERATED_BODY()

	public:
		UIBBCommand() : Super() { };

		virtual void Execute() PURE_VIRTUAL(UIBBCommand::Execute, );
};