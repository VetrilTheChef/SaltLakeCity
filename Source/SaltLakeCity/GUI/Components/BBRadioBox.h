// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Interfaces/IBBRadioBox.h"
#include "BBRadioBox.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBRadioBox : public UIBBRadioBox
{
	GENERATED_BODY()
	
	public:
		UBBRadioBox(const FObjectInitializer & ObjectInitializer);

		virtual void Initialize(int NewIndex) override;

		virtual void SetCommand(UIBBCommand * NewCommand) override;
		
		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBCommand * Command;

		int Index;

		virtual TSharedRef<SWidget> RebuildWidget() override;

		UFUNCTION()
		void ChangeCheckState(bool bIsChecked);
};