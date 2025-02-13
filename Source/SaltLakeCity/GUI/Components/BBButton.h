// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "BBButton.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBButton : public UIBBButton
{
	GENERATED_BODY()
	
	public:
		UBBButton(const FObjectInitializer & ObjectInitializer);

		virtual void PostInitProperties() override;
		
		virtual void BeginDestroy() override;

		void SetCommand(UIBBCommand * NewCommand);

	protected:
		UPROPERTY()
		UIBBCommand * Command;

		FScriptDelegate ClickDelegate;

		UFUNCTION()
		void ExecuteCommand();
};