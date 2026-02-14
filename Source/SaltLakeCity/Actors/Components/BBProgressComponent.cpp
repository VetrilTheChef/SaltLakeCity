// SaltLakeCity 5.7

#include "BBProgressComponent.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GUI/Interfaces/IBBAttachWidgetCommand.h"
#include "Commands/GUI/Interfaces/IBBDetachWidgetCommand.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBProgressComponent::UBBProgressComponent() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;
	bHiddenInGame = true;

	Progressable = TScriptInterface<IBBProgressable>();
	AttachCommand = nullptr;
	DetachCommand = nullptr;

	SelectedColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	DeselectedColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.33f);
}

void UBBProgressComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBBProgressComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBProgressComponent::Initialize(TScriptInterface<IBBProgressable> && NewProgressable)
{
	verifyf(IsValid(NewProgressable.GetObject()), TEXT("New Progressable is invalid."));

	UIBBGameInstance * GameInstance = NewProgressable->ToActor()->GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	UIBBWidgetManager * WidgetManager = GameInstance->GetWidgetManager();

	verifyf(IsValid(WidgetManager), TEXT("Widget Manager is invalid."));

	const UIBBCommandFactory * CommandFactory = GameInstance->GetCommandFactory();

	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory = WidgetManager->GetWidgetSpecificationFactory();

	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	InitializeCommands(* CommandFactory, * WidgetSpecificationFactory);

	Subscribe(Forward<TScriptInterface<IBBProgressable>>(NewProgressable));
}

void UBBProgressComponent::Finalize()
{
	Unsubscribe(Progressable);

	FinalizeCommands();
}

TScriptInterface<IBBProgressable> UBBProgressComponent::GetProgressable() const
{
	return Progressable;
}

void UBBProgressComponent::SetProgressable(TScriptInterface<IBBProgressable> && NewProgressable)
{
	Subscribe(Forward<TScriptInterface<IBBProgressable>>(NewProgressable));
}

void UBBProgressComponent::SetWidget(UUserWidget * NewWidget)
{
	Super::SetWidget(NewWidget);
}

float UBBProgressComponent::GetProgress()
{
	return IsValid(Progressable.GetObject()) ? Progressable->GetProgress() : -1.0f;
}

const TScriptInterface<IBBWidgetTarget> UBBProgressComponent::GetWidgetTarget() const
{
	return IsValid(Progressable.GetObject()) ? Progressable->ToWidgetTarget() : TScriptInterface<IBBWidgetTarget>(nullptr);
}



void UBBProgressComponent::Subscribe(TScriptInterface<IBBProgressable> && NewProgressable)
{
	Unsubscribe(Progressable);

	verifyf(IsValid(NewProgressable.GetObject()), TEXT("New Progressable is invalid."));

	Progressable = NewProgressable;

	Progressable->OnProgressInitiation().AddUObject(this, & UBBProgressComponent::AttachWidget);
	Progressable->OnProgressUpdate().AddUObject(this, & UBBProgressComponent::UpdateProgress);
	Progressable->OnProgressCompletion().AddUObject(this, & UBBProgressComponent::DetachWidget);
}

void UBBProgressComponent::Unsubscribe(TScriptInterface<IBBProgressable> & OldProgressable)
{
	if (IsValid(OldProgressable.GetObject()))
	{
		OldProgressable->OnProgressInitiation().RemoveAll(this);
		OldProgressable->OnProgressUpdate().RemoveAll(this);
		OldProgressable->OnProgressCompletion().RemoveAll(this);
	}

	OldProgressable.SetObject(nullptr);
}

void UBBProgressComponent::InitializeCommands(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory)
{
	InitializeAttachWidgetCommand(CommandFactory, WidgetSpecificationFactory);
	InitializeDetachWidgetCommand(CommandFactory);
}

void UBBProgressComponent::InitializeAttachWidgetCommand(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory)
{
	UIBBWidgetSpecification * ProgressWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewProgressWidgetSpecification(ProgressWidgetSpecification, this);

	CommandFactory.NewAttachWidgetCommand(AttachCommand, this, ProgressWidgetSpecification, this);
}

void UBBProgressComponent::InitializeDetachWidgetCommand(const UIBBCommandFactory & CommandFactory)
{
	CommandFactory.NewDetachWidgetCommand(DetachCommand, this, this);
}

void UBBProgressComponent::FinalizeCommands()
{
	FinalizeAttachWidgetCommand();
	FinalizeDetachWidgetCommand();
}

void UBBProgressComponent::FinalizeAttachWidgetCommand()
{
	if (IsValid(AttachCommand))
	{
		AttachCommand->MarkAsGarbage();
	}

	AttachCommand = nullptr;
}

void UBBProgressComponent::FinalizeDetachWidgetCommand()
{
	if (IsValid(DetachCommand))
	{
		DetachCommand->MarkAsGarbage();
	}

	DetachCommand = nullptr;
}

void UBBProgressComponent::UpdateComponent(UIBBProgressComponent * NewProgressComponent)
{
	if (this == NewProgressComponent)
	{
		SetTintColorAndOpacity(SelectedColor);
	}
	else
	{
		SetTintColorAndOpacity(DeselectedColor);
	}
}

void UBBProgressComponent::AttachWidget()
{
	verifyf(IsValid(AttachCommand), TEXT("Attach Command is invalid."));

	AttachCommand->Execute();
}

void UBBProgressComponent::DetachWidget()
{
	verifyf(IsValid(DetachCommand), TEXT("Detach Command is invalid."));

	DetachCommand->Execute();
}

void UBBProgressComponent::UpdateProgress(float NewProgress)
{
	OnProgressUpdate().Broadcast(NewProgress);
}
