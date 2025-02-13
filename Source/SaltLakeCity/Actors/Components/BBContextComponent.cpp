// SaltLakeCity 4.27

#include "BBContextComponent.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GameStates/Interfaces/IBBSetContextCommand.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "Commands/GUI/Interfaces/IBBOpenWidgetCommand.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBContextComponent::UBBContextComponent() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;

	Contextualizable = TScriptInterface<IBBContextualizable>();
	ContextCommand = nullptr;
	OpenCommand = nullptr;
	CloseCommand = nullptr;
}

void UBBContextComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBBContextComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBContextComponent::Initialize(TScriptInterface<IBBContextualizable> && NewContextualizable)
{
	verifyf(IsValid(NewContextualizable.GetObject()), TEXT("New Contextualizable is invalid."));

	UIBBGameInstance * GameInstance = NewContextualizable->ToActor()->GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	AIBBHUD * HUD = GameInstance->GetHUD();

	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	Subscribe(Forward<TScriptInterface<IBBContextualizable>>(NewContextualizable));

	const UIBBCommandFactory * CommandFactory = GameInstance->GetCommandFactory();

	verifyf(IsValid(CommandFactory), TEXT("CommandFactory is invalid."));

	const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory = HUD->GetWidgetSpecificationFactory();

	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	InitializeCommands(* CommandFactory, * WidgetSpecificationFactory);
}

void UBBContextComponent::Finalize()
{
	FinalizeCommands();

	Unsubscribe(Contextualizable);
}

bool UBBContextComponent::IsOption(EBBContext Option) const
{
	verifyf(IsValid(Contextualizable.GetObject()), TEXT("Contextualizable is invalid."));

	return Contextualizable->IsContextOption(Option);
}

const TScriptInterface<IBBWidgetTarget> UBBContextComponent::GetWidgetTarget() const
{
	return IsValid(Contextualizable.GetObject()) ? Contextualizable->ToWidgetTarget() : TScriptInterface<IBBWidgetTarget>(nullptr);
}




void UBBContextComponent::Subscribe(TScriptInterface<IBBContextualizable> && NewContextualizable)
{
	Unsubscribe(Contextualizable);

	Contextualizable = NewContextualizable;

	Contextualizable->OnContextUpdate().AddUObject(this, & UBBContextComponent::ToggleContext);
}

void UBBContextComponent::Unsubscribe(TScriptInterface<IBBContextualizable> & OldContextualizable)
{
	if (IsValid(OldContextualizable.GetObject()))
	{
		OldContextualizable->OnContextUpdate().RemoveAll(this);
	}

	OldContextualizable.SetObject(nullptr);
}

void UBBContextComponent::InitializeCommands(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory)
{
	UIBBWidgetSpecification * ContextWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewContextWidgetSpecification(ContextWidgetSpecification, this);

	InitializeSetContextCommand(CommandFactory, Contextualizable);
	InitializeOpenWidgetCommand(CommandFactory, ContextWidgetSpecification);
	InitializeCloseWidgetCommand(CommandFactory, ContextWidgetSpecification);
}

void UBBContextComponent::InitializeSetContextCommand(const UIBBCommandFactory & CommandFactory, TScriptInterface<IBBContextualizable> & NewContextualizable)
{
	CommandFactory.NewSetContextCommand(ContextCommand, this, NewContextualizable);
}

void UBBContextComponent::InitializeOpenWidgetCommand(const UIBBCommandFactory & CommandFactory, UIBBWidgetSpecification * WidgetSpecification)
{
	CommandFactory.NewOpenWidgetCommand(OpenCommand, this, WidgetSpecification, true);
}

void UBBContextComponent::InitializeCloseWidgetCommand(const UIBBCommandFactory & CommandFactory, UIBBWidgetSpecification * WidgetSpecification)
{
	CommandFactory.NewCloseWidgetCommand(CloseCommand, this, WidgetSpecification);
}

void UBBContextComponent::FinalizeCommands()
{
	FinalizeCloseWidgetCommand();
	FinalizeOpenWidgetCommand();
	FinalizeSetContextCommand();
}

void UBBContextComponent::FinalizeOpenWidgetCommand()
{
	if (IsValid(OpenCommand))
	{
		OpenCommand->MarkPendingKill();
	}

	OpenCommand = nullptr;
}

void UBBContextComponent::FinalizeCloseWidgetCommand()
{
	if (IsValid(CloseCommand))
	{
		CloseCommand->MarkPendingKill();
	}

	CloseCommand = nullptr;
}

void UBBContextComponent::FinalizeSetContextCommand()
{
	if (IsValid(ContextCommand))
	{
		ContextCommand->MarkPendingKill();
	}

	ContextCommand = nullptr;
}

void UBBContextComponent::ToggleContext(bool Contextualized)
{
	verifyf(IsValid(ContextCommand), TEXT("Context Command is invalid."));
	verifyf(IsValid(OpenCommand), TEXT("Open Command is invalid."));
	verifyf(IsValid(CloseCommand), TEXT("Close Command is invalid."));

	ContextCommand->Execute();

	Contextualized ? OpenCommand->Execute() : CloseCommand->Execute();
}