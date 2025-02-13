// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Containers/SortedMap.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "BBModesWidget.generated.h"

/**
 * 
 */

class UIBBRadioBox;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBModesWidget : public UIBBModesWidget
{
	GENERATED_BODY()
	
	public:
		UBBModesWidget(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void NativeDestruct() override;

		virtual EBBWidget GetType() const override;

		virtual void SetPlayModeCommand(UIBBCommand * Command) override;

		virtual void SetBuildModeCommand(UIBBCommand * Command) override;

		virtual void SetActiveMode(EBBGameMode GameMode) override;
	
	protected:
		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox * PlayButton;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox * BuildButton;

		TSortedMap<EBBGameMode, UIBBRadioBox *, FDefaultAllocator, TLess<EBBGameMode>> Modes;

		void InitializeModes();

		void FinalizeModes();

		UFUNCTION()
		void ChangeRadioState(int Index);
};