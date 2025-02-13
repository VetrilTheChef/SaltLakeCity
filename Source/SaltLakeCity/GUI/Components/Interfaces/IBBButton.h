// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "IBBButton.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(Abstract, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UIBBButton : public UButton
{
	GENERATED_BODY()
	
	public:
		UIBBButton(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); };
		
		virtual void BeginDestroy() override { Super::BeginDestroy(); };

		virtual void SetCommand(UIBBCommand * NewCommand) PURE_VIRTUAL(UIBBButton::SetCommand, );
};