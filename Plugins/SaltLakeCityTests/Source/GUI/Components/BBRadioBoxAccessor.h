// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Interfaces/IBBRadioBox.h"
#include "BBRadioBoxAccessor.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class UBBRadioBoxAccessor : public UIBBRadioBox
{
	GENERATED_BODY()

	public:
		UBBRadioBoxAccessor(const FObjectInitializer & ObjectInitializer);

		void Decorate(UIBBRadioBox * NewRadioBox);

		virtual void Initialize(int NewIndex) override;

		virtual void SetCommand(UIBBCommand * NewCommand) override;

		virtual void Finalize() override;
		
		void RebuildWidgetPublic();

		void BroadcastOnCheckStateChanged(bool bIsChecked);

	protected:
		UPROPERTY()
		UIBBRadioBox * RadioBox;
};