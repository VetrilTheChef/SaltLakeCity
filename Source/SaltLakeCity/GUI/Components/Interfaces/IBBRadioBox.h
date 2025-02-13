// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Components/CheckBox.h"
#include "IBBRadioBox.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(Abstract, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UIBBRadioBox : public UCheckBox
{
	GENERATED_BODY()
	
	public:
		DECLARE_EVENT_OneParam(UIBBRadioBox, FChangeRadioState, int);

		UIBBRadioBox(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void Initialize(int NewIndex) PURE_VIRTUAL(UIBBRadioBox::Initialize, );

		virtual void SetCommand(UIBBCommand * NewCommand) PURE_VIRTUAL(UIBBRadioBox::SetCommand, );

		virtual void Finalize() PURE_VIRTUAL(UIBBRadioBox::Finalize, );

		FChangeRadioState & OnRadioStateChanged() { return RadioStateChange; };

	protected:
		virtual TSharedRef<SWidget> RebuildWidget() override { return Super::RebuildWidget(); };

		FChangeRadioState RadioStateChange;
};