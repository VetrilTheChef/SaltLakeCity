// SaltLakeCity 4.25

#include "BBModesWidget.h"
#include "Components/TextBlock.h"
#include "GameInstances/BBGameInstance.h"
#include "GUI/Components/Interfaces/IBBRadioBox.h"

UBBModesWidget::UBBModesWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Modes.Empty();
}

void UBBModesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeModes();
}

void UBBModesWidget::NativeDestruct()
{
	FinalizeModes();

	Super::NativeDestruct();
}

EBBWidget UBBModesWidget::GetType() const
{
	return EBBWidget::Modes;
}

void UBBModesWidget::SetPlayModeCommand(UIBBCommand * Command)
{
	verifyf(IsValid(PlayButton), TEXT("Play Button is invalid."));

	PlayButton->SetCommand(Command);
}

void UBBModesWidget::SetBuildModeCommand(UIBBCommand * Command)
{
	verifyf(IsValid(BuildButton), TEXT("Build Button is invalid."));

	BuildButton->SetCommand(Command);
}

void UBBModesWidget::SetActiveMode(EBBGameMode GameMode)
{
	Modes.FindChecked(GameMode)->SetCheckedState(ECheckBoxState::Checked);
}



void UBBModesWidget::InitializeModes()
{
	Modes.Empty();

	Modes.Emplace(EBBGameMode::Play, PlayButton);
	Modes.Emplace(EBBGameMode::Build, BuildButton);

	for (TPair<EBBGameMode, UIBBRadioBox *> & Mode : Modes)
	{
		UIBBRadioBox * RadioBox = Mode.Value;

		verifyf(IsValid(RadioBox), TEXT("Radio Box is invalid."));

		RadioBox->Initialize((int)Mode.Key);
		RadioBox->OnRadioStateChanged().AddUObject(this, &UBBModesWidget::ChangeRadioState);
	}
}

void UBBModesWidget::FinalizeModes()
{
	for (TPair<EBBGameMode, UIBBRadioBox *> & Mode : Modes)
	{
		UIBBRadioBox * RadioBox = Mode.Value;

		if (IsValid(RadioBox))
		{
			RadioBox->OnRadioStateChanged().RemoveAll(this);
			RadioBox->Finalize();
		}

		Mode.Value = nullptr;
	}

	Modes.Empty();
}

void UBBModesWidget::ChangeRadioState(int Index)
{
	for (TPair<EBBGameMode, UIBBRadioBox *> & Mode : Modes)
	{
		bool Checked = ((int)(Mode.Key) == Index);

		UIBBRadioBox * RadioBox = Mode.Value;

		verifyf(IsValid(RadioBox), TEXT("Radio Box is invalid."));

		RadioBox->SetIsEnabled(!Checked);

		// Do not set the checked state if the radio box is the one which
		// broadcasted the event, otherwise the code will loop
		if (!Checked)
		{
			RadioBox->SetIsChecked(false);
		}
	}
}
