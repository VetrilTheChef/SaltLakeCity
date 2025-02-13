// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Commands/Metacommands/Interfaces/IBBCompositeCommand.h"
#include "BBCompositeCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBCompositeCommand : public UIBBCompositeCommand
{
	GENERATED_BODY()

	public:
		UBBCompositeCommand();

		virtual int Add(UIBBCommand * Command) override;

		virtual int Remove(UIBBCommand * Command) override;

		virtual void Empty() override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		TArray<UIBBCommand *> Commands;
};