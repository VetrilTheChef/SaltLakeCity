// SaltLakeCity 4.27

#include "BBCommandFactory.h"
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

UBBCommandFactory::UBBCommandFactory() :
	Super()
{
	GameInstance = nullptr;
}

void UBBCommandFactory::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBCommandFactory::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBBCommandFactory::Initialize(UIBBGameInstance * NewGameInstance)
{
	GameInstance = NewGameInstance;
}

void UBBCommandFactory::Finalize()
{
	GameInstance = nullptr;
}

bool UBBCommandFactory::NewOrderBuildCommand(UIBBOrderBuildCommand * & Command, UObject * Outer, const TSoftClassPtr<UIBBBuildData> BuildDataClass, const TSoftClassPtr<AIBBTargetingActor> TargetingClass, const TArray<FBBBuildablePtr> BuildableClasses, float Price, float Time) const
{
	verifyf(!OrderBuildCommandClass.IsNull(), TEXT("Order Build Command Class is null."));

	Command = NewObject<UIBBOrderBuildCommand>(Outer, OrderBuildCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetController(GameInstance->GetPlayerController());
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

bool UBBCommandFactory::NewPauseCommand(UIBBPauseCommand * & Command, UObject * Outer) const
{
	verifyf(!PauseCommandClass.IsNull(), TEXT("Pause Command Class is null."));
	
	Command = NewObject<UIBBPauseCommand>(Outer, PauseCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetController(GameInstance->GetPlayerController());

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewSpeedCommand(UIBBSpeedCommand * & Command, UObject * Outer, float TimeDilation) const
{
	verifyf(!SpeedCommandClass.IsNull(), TEXT("Speed Command Class is null."));

	Command = NewObject<UIBBSpeedCommand>(Outer, SpeedCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetController(GameInstance->GetPlayerController());
		Command->SetTimeDilation(TimeDilation);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewOpenWidgetCommand(UIBBOpenWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, bool PopUp) const
{
	verifyf(!OpenWidgetCommandClass.IsNull(), TEXT("Open Widget Command Class is null."));

	Command = NewObject<UIBBOpenWidgetCommand>(Outer, OpenWidgetCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetHUD(GameInstance->GetHUD());
		Command->SetSpecification(Specification);
		Command->SetPopUp(PopUp);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewCloseWidgetCommand(UIBBCloseWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification) const
{
	verifyf(!CloseWidgetCommandClass.IsNull(), TEXT("Close Widget Command Class is null."));

	Command = NewObject<UIBBCloseWidgetCommand>(Outer, CloseWidgetCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetHUD(GameInstance->GetHUD());
		Command->SetSpecification(Specification);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewAttachWidgetCommand(UIBBAttachWidgetCommand * & Command, UObject * Outer, UIBBWidgetSpecification * Specification, UIBBWidgetComponent * Component) const
{
	verifyf(!AttachWidgetCommandClass.IsNull(), TEXT("Attach Widget Command Class is null."));

	Command = NewObject<UIBBAttachWidgetCommand>(Outer, AttachWidgetCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetHUD(GameInstance->GetHUD());
		Command->SetSpecification(Specification);
		Command->SetWidgetComponent(Component);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewDetachWidgetCommand(UIBBDetachWidgetCommand * & Command, UObject * Outer, UIBBWidgetComponent * Component) const
{
	verifyf(!DetachWidgetCommandClass.IsNull(), TEXT("Detach Widget Command Class is null."));

	Command = NewObject<UIBBDetachWidgetCommand>(Outer, DetachWidgetCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetHUD(GameInstance->GetHUD());
		Command->SetWidgetComponent(Component);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewGameModeCommand(UIBBGameModeCommand * & Command, UObject * Outer, EBBGameMode ActiveGameMode) const
{
	verifyf(!GameModeCommandClass.IsNull(), TEXT("Game Mode Command Class is null."));

	Command = NewObject<UIBBGameModeCommand>(Outer, GameModeCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetGameMode(GameInstance->GetGameMode());
		Command->SetActiveGameMode(ActiveGameMode);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewSelectCommand(UIBBSelectCommand * & Command, UObject * Outer, TScriptInterface<IBBSelectable> Selectable) const
{
	verifyf(!SelectCommandClass.IsNull(), TEXT("Select Command Class is null."));

	Command = NewObject<UIBBSelectCommand>(Outer, SelectCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetGameState(GameInstance->GetGameState());
		Command->SetSelectable(Selectable);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewSetContextCommand(UIBBSetContextCommand * & Command, UObject * Outer, TScriptInterface<IBBContextualizable> Contextualizable) const
{
	verifyf(!SetContextCommandClass.IsNull(), TEXT("Set Context Command Class is null."));

	Command = NewObject<UIBBSetContextCommand>(Outer, SetContextCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetGameState(GameInstance->GetGameState());
		Command->SetContextualizable(Contextualizable);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewSetJobCommand(UIBBSetJobCommand * & Command, UObject * Outer, UIBBWorkComponent * WorkComponent, EBBJob Job) const
{
	verifyf(!SetJobCommandClass.IsNull(), TEXT("Set Job Command Class is null."));

	Command = NewObject<UIBBSetJobCommand>(Outer, SetJobCommandClass.LoadSynchronous());

	if (IsValid(Command))
	{
		Command->SetWorkComponent(WorkComponent);
		Command->SetJob(Job);

		return true;
	}

	return false;
}

bool UBBCommandFactory::NewCompositeCommand(UIBBCompositeCommand * & Command, UObject * Outer) const
{
	verifyf(!CompositeCommandClass.IsNull(), TEXT("Composite Command Class is null."));

	Command = NewObject<UIBBCompositeCommand>(Outer, CompositeCommandClass.LoadSynchronous());

	return IsValid(Command);
}