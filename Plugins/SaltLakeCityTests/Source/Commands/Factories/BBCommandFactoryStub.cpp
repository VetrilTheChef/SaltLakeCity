// SaltLakeCity 4.27

#include "BBCommandFactoryStub.h"
#include "Abilities/Data/BBBuildDataStub.h"
#include "Commands/Controllers/Interfaces/IBBOrderBuildCommand.h"
#include "Commands/Controllers/Interfaces/IBBPauseCommand.h"
#include "Commands/Controllers/Interfaces/IBBSpeedCommand.h"
#include "Commands/GameModes/Interfaces/IBBGameModeCommand.h"
#include "Commands/GameStates/Interfaces/IBBSelectCommand.h"
#include "Commands/GameStates/Interfaces/IBBSetContextCommand.h"
#include "Commands/GUI/Interfaces/IBBAttachWidgetCommand.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "Commands/GUI/Interfaces/IBBDetachWidgetCommand.h"
#include "Commands/GUI/Interfaces/IBBOpenWidgetCommand.h"
#include "Commands/Jobs/Interfaces/IBBSetJobCommand.h"
#include "Commands/Metacommands/Interfaces/IBBCompositeCommand.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"

UBBCommandFactoryStub::UBBCommandFactoryStub() :
	Super()
{
	GameInstance = nullptr;

	AttachWidgetCommands.Empty();
	CloseWidgetCommands.Empty();
	CompositeCommands.Empty();
	DetachWidgetCommands.Empty();
	GameModeCommands.Empty();
	OpenWidgetCommands.Empty();
	OrderBuildCommands.Empty();
	PauseCommands.Empty();
	SelectCommands.Empty();
	SetContextCommands.Empty();
	SetJobCommands.Empty();
	SpeedCommands.Empty();
}

void UBBCommandFactoryStub::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBCommandFactoryStub::Initialize(UIBBGameInstance * NewGameInstance)
{
	GameInstance = NewGameInstance;
}

void UBBCommandFactoryStub::Finalize()
{
	GameInstance = nullptr;
}

void UBBCommandFactoryStub::AddOrderBuildCommand(UIBBOrderBuildCommand * NewOrderBuildCommand)
{
	OrderBuildCommands.EmplaceAt(0, NewOrderBuildCommand);
}

bool UBBCommandFactoryStub::NewOrderBuildCommand(UIBBOrderBuildCommand * & Command, UObject * Outer, const TSoftClassPtr<UIBBBuildData> BuildDataClass, const TSoftClassPtr<AIBBTargetingActor> TargetingClass, const TArray<FBBBuildablePtr> BuildableClasses, float Price, float Time) const
{
	Command = OrderBuildCommands.Num() > 0 ? OrderBuildCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetOuter(Outer);
		Command->SetBuildDataClass(BuildDataClass);
		Command->SetTargetingClass(TargetingClass);
		Command->SetBuildableClasses(BuildableClasses);
		Command->SetPrice(Price);
		Command->SetTime(Time);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddPauseCommand(UIBBPauseCommand * NewPauseCommand)
{
	PauseCommands.EmplaceAt(0, NewPauseCommand);
}

bool UBBCommandFactoryStub::NewPauseCommand(UIBBPauseCommand * & Command, UObject * Outer) const
{
	Command = PauseCommands.Num() > 0 ? PauseCommands.Pop() : nullptr;

	return IsValid(Command);
}

void UBBCommandFactoryStub::AddSpeedCommand(UIBBSpeedCommand * NewSpeedCommand)
{
	SpeedCommands.EmplaceAt(0, NewSpeedCommand);
}

bool UBBCommandFactoryStub::NewSpeedCommand(UIBBSpeedCommand * & Command, UObject * Outer, float TimeDilation) const
{
	Command = SpeedCommands.Num() > 0 ? SpeedCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetTimeDilation(TimeDilation);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddOpenWidgetCommand(UIBBOpenWidgetCommand * NewOpenWidgetCommand)
{
	OpenWidgetCommands.EmplaceAt(0, NewOpenWidgetCommand);
}

bool UBBCommandFactoryStub::NewOpenWidgetCommand(UIBBOpenWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, bool PopUp) const
{
	Command = OpenWidgetCommands.Num() > 0 ? OpenWidgetCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetSpecification(Specification);
		Command->SetPopUp(PopUp);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddCloseWidgetCommand(UIBBCloseWidgetCommand * NewCloseWidgetCommand)
{
	CloseWidgetCommands.EmplaceAt(0, NewCloseWidgetCommand);
}

bool UBBCommandFactoryStub::NewCloseWidgetCommand(UIBBCloseWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification) const
{
	Command = CloseWidgetCommands.Num() > 0 ? CloseWidgetCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetSpecification(Specification);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddAttachWidgetCommand(UIBBAttachWidgetCommand * NewAttachWidgetCommand)
{
	AttachWidgetCommands.EmplaceAt(0, NewAttachWidgetCommand);
}

bool UBBCommandFactoryStub::NewAttachWidgetCommand(UIBBAttachWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, UIBBWidgetComponent * Component) const
{
	Command = AttachWidgetCommands.Num() > 0 ? AttachWidgetCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetSpecification(Specification);
		Command->SetWidgetComponent(Component);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddDetachWidgetCommand(UIBBDetachWidgetCommand * NewDetachWidgetCommand)
{
	DetachWidgetCommands.EmplaceAt(0, NewDetachWidgetCommand);
}

bool UBBCommandFactoryStub::NewDetachWidgetCommand(UIBBDetachWidgetCommand * & Command, UObject * Outer, UIBBWidgetComponent * Component) const
{
	Command = DetachWidgetCommands.Num() > 0 ? DetachWidgetCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetWidgetComponent(Component);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddGameModeCommand(UIBBGameModeCommand * NewGameModeCommand)
{
	GameModeCommands.EmplaceAt(0, NewGameModeCommand);
}

bool UBBCommandFactoryStub::NewGameModeCommand(UIBBGameModeCommand * & Command, UObject * Outer, EBBGameMode ActiveGameMode) const
{
	Command = GameModeCommands.Num() > 0 ? GameModeCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetActiveGameMode(ActiveGameMode);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddSelectCommand(UIBBSelectCommand * NewSelectCommand)
{
	SelectCommands.EmplaceAt(0, NewSelectCommand);
}

bool UBBCommandFactoryStub::NewSelectCommand(UIBBSelectCommand * & Command, UObject * Outer, TScriptInterface<IBBSelectable> Selectable) const
{
	Command = SelectCommands.Num() > 0 ? SelectCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetSelectable(Forward<TScriptInterface<IBBSelectable>>(Selectable));

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddSetContextCommand(UIBBSetContextCommand * NewSetContextCommand)
{
	SetContextCommands.EmplaceAt(0, NewSetContextCommand);
}

bool UBBCommandFactoryStub::NewSetContextCommand(UIBBSetContextCommand * & Command, UObject * Outer, TScriptInterface<IBBContextualizable> Contextualizable) const
{
	Command = SetContextCommands.Num() > 0 ? SetContextCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetContextualizable(Forward<TScriptInterface<IBBContextualizable>>(Contextualizable));

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddSetJobCommand(UIBBSetJobCommand * NewSetJobCommand)
{
	SetJobCommands.EmplaceAt(0, NewSetJobCommand);
}

bool UBBCommandFactoryStub::NewSetJobCommand(UIBBSetJobCommand * & Command, UObject * Outer, UIBBWorkComponent * WorkComponent, EBBJob Job) const
{
	Command = SetJobCommands.Num() > 0 ? SetJobCommands.Pop() : nullptr;

	if (IsValid(Command))
	{
		Command->Rename(nullptr, Outer);

		Command->SetWorkComponent(WorkComponent);
		Command->SetJob(Job);

		return true;
	}

	return false;
}

void UBBCommandFactoryStub::AddCompositeCommand(UIBBCompositeCommand * NewCompositeCommand)
{
	CompositeCommands.EmplaceAt(0, NewCompositeCommand);
}

bool UBBCommandFactoryStub::NewCompositeCommand(UIBBCompositeCommand * & Command, UObject * Outer) const
{
	Command = CompositeCommands.Num() > 0 ? CompositeCommands.Pop() : nullptr;

	return IsValid(Command);
}