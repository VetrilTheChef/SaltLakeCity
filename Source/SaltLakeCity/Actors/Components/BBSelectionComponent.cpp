// SaltLakeCity 5.7

#include "BBSelectionComponent.h"
#include "InputCoreTypes.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GameStates/Interfaces/IBBSelectCommand.h"
#include "Commands/GUI/Interfaces/IBBAttachWidgetCommand.h"
#include "Commands/GUI/Interfaces/IBBDetachWidgetCommand.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBSelectionComponent::UBBSelectionComponent() :
	Super()
{
	bWindowFocusable = false;
	WindowVisibility = EWindowVisibility::Visible;
	PrimaryComponentTick.bCanEverTick = true;
	BlendMode = EWidgetBlendMode::Opaque;
	bDrawAtDesiredSize = true;

	Selectable = TScriptInterface<IBBSelectable>();
	SelectCommand = nullptr;
	AttachCommand = nullptr;
	DetachCommand = nullptr;
}

void UBBSelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	SetTickMode(ETickMode::Disabled);
	SetWidgetSpace(EWidgetSpace::Screen);
}

void UBBSelectionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBSelectionComponent::Initialize(TScriptInterface<IBBSelectable> && NewSelectable)
{
	verifyf(IsValid(NewSelectable.GetObject()), TEXT("New Selectable is invalid."));

	AActor * SelectableActor = NewSelectable->ToActor();

	UIBBGameInstance * GameInstance = SelectableActor->GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	UIBBWidgetManager * WidgetManager = GameInstance->GetWidgetManager();

	verifyf(IsValid(WidgetManager), TEXT("Widget Manager is invalid."));

	const UIBBCommandFactory * CommandFactory = GameInstance->GetCommandFactory();

	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory = WidgetManager->GetWidgetSpecificationFactory();

	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	InitializeCommands(* CommandFactory, * WidgetSpecificationFactory, Forward<TScriptInterface<IBBSelectable>>(NewSelectable));

	Subscribe(Forward<TScriptInterface<IBBSelectable>>(NewSelectable));
}

void UBBSelectionComponent::Finalize()
{
	Unsubscribe(Selectable);

	FinalizeCommands();
}

TScriptInterface<IBBSelectable> UBBSelectionComponent::GetSelectable() const
{
	return Selectable;
}

void UBBSelectionComponent::SetSelectable(TScriptInterface<IBBSelectable> && NewSelectable)
{
	verifyf(IsValid(NewSelectable.GetObject()), TEXT("New Selectable is invalid."));
	
	Subscribe(Forward<TScriptInterface<IBBSelectable>>(NewSelectable));
}

const TScriptInterface<IBBWidgetTarget> UBBSelectionComponent::GetWidgetTarget() const
{
	return IsValid(Selectable.GetObject()) ? Selectable->ToWidgetTarget() : TScriptInterface<IBBWidgetTarget>(nullptr);
}



void UBBSelectionComponent::Subscribe(TScriptInterface<IBBSelectable> && NewSelectable)
{
	Unsubscribe(Selectable);

	verifyf(IsValid(NewSelectable.GetObject()), TEXT("New Selectable is invalid."));

	Selectable = NewSelectable;

	verifyf(IsValid(SelectCommand), TEXT("Select Command is invalid."));

	SelectCommand->SetSelectable(Forward<TScriptInterface<IBBSelectable>>(Selectable));

	Selectable->ToActor()->OnClicked.AddDynamic(this, & UBBSelectionComponent::Click);
	Selectable->OnSelectionUpdate().AddUObject(this, & UBBSelectionComponent::ToggleWidget);
}

void UBBSelectionComponent::Unsubscribe(TScriptInterface<IBBSelectable> & OldSelectable)
{
	if (IsValid(OldSelectable.GetObject()))
	{
		OldSelectable->ToActor()->OnClicked.RemoveDynamic(this, & UBBSelectionComponent::Click);
		OldSelectable->OnSelectionUpdate().RemoveAll(this);
	}

	OldSelectable.SetObject(nullptr);

	if (IsValid(SelectCommand))
	{
		SelectCommand->SetSelectable(nullptr);
	}
}

void UBBSelectionComponent::InitializeCommands(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, TScriptInterface<IBBSelectable> && NewSelectable)
{
	InitializeSelectCommand(CommandFactory, Forward<TScriptInterface<IBBSelectable>>(NewSelectable));
	InitializeAttachWidgetCommand(CommandFactory, WidgetSpecificationFactory);
	InitializeDetachWidgetCommand(CommandFactory);
}

void UBBSelectionComponent::InitializeSelectCommand(const UIBBCommandFactory & CommandFactory, TScriptInterface<IBBSelectable>&& NewSelectable)
{
	CommandFactory.NewSelectCommand(SelectCommand, this, NewSelectable);
}

void UBBSelectionComponent::InitializeAttachWidgetCommand(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory)
{
	UIBBWidgetSpecification * SelectionWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewSelectionWidgetSpecification(SelectionWidgetSpecification, this);

	CommandFactory.NewAttachWidgetCommand(AttachCommand, this, SelectionWidgetSpecification, this);
}

void UBBSelectionComponent::InitializeDetachWidgetCommand(const UIBBCommandFactory & CommandFactory)
{
	CommandFactory.NewDetachWidgetCommand(DetachCommand, this, this);
}

void UBBSelectionComponent::FinalizeCommands()
{
	FinalizeSelectCommand();
	FinalizeAttachWidgetCommand();
	FinalizeDetachWidgetCommand();
}

void UBBSelectionComponent::FinalizeSelectCommand()
{
	if (IsValid(SelectCommand))
	{
		SelectCommand->MarkAsGarbage();
	}

	SelectCommand = nullptr;
}

void UBBSelectionComponent::FinalizeAttachWidgetCommand()
{
	if (IsValid(AttachCommand))
	{
		AttachCommand->MarkAsGarbage();
	}

	AttachCommand = nullptr;
}

void UBBSelectionComponent::FinalizeDetachWidgetCommand()
{
	if (IsValid(DetachCommand))
	{
		DetachCommand->MarkAsGarbage();
	}

	DetachCommand = nullptr;
}

void UBBSelectionComponent::Click(AActor * Actor, FKey ButtonPressed)
{
	verifyf(Actor == Selectable.GetObject(), TEXT("Clicked Actor is not the selected Actor."));

	if (ButtonPressed == EKeys::LeftMouseButton)
	{
		verifyf(IsValid(SelectCommand), TEXT("Select Command is invalid."));

		SelectCommand->Execute();
	}
}

void UBBSelectionComponent::ToggleWidget(bool Attached)
{
	if (Attached)
	{
		verifyf(IsValid(AttachCommand), TEXT("Attach Command is invalid."));

		SetTickMode(ETickMode::Enabled);
		AttachCommand->Execute();
	}
	else
	{
		verifyf(IsValid(DetachCommand), TEXT("Detach Command is invalid."));

		DetachCommand->Execute();
		SetTickMode(ETickMode::Disabled);
	}
}