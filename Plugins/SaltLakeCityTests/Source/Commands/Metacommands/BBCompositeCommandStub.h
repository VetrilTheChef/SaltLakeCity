// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Metacommands/Interfaces/IBBCompositeCommand.h"
#include "BBCompositeCommandStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBCompositeCommandStub : public UIBBCompositeCommand
{
	GENERATED_BODY()

	public:
		UBBCompositeCommandStub();

		virtual int Add(UIBBCommand * Command) override;

		virtual int Remove(UIBBCommand * Command) override;

		virtual void Empty() override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		TArray<UIBBCommand *> Commands;

		UPROPERTY()
		int Executions;
};