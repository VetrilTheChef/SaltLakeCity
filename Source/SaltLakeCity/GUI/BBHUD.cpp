// SaltLakeCity 5.7

#include "BBHUD.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameInstances/Subsystems/Interfaces/IBBUINotificationSubsystem.h"
#include "GUI/BBUIStatics.h"
#include "GUI/Interfaces/IBBWidgetManager.h"

// PUBLIC

ABBHUD::ABBHUD() :
	Super()
{
	HUDColor = FLinearColor(0.984314, 0.333333, 0.0, 1.0);

	UINotificationSubsystem = nullptr;
	WidgetManager = nullptr;
}

void ABBHUD::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(CloseRequestTag.IsValid(), TEXT("Close Request Tag is invalid."));
	ensureMsgf(OpenRequestTag.IsValid(), TEXT("Open Request Tag is invalid."));
}

void ABBHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Finalize();

	Super::EndPlay(EndPlayReason);
}

void ABBHUD::Initialize(
	UIBBUINotificationSubsystem* NewUINotificationSubsystem,
	UIBBWidgetManager* NewWidgetManager
)
{
	SetUINotificationSubsystemChecked(NewUINotificationSubsystem);
	SetWidgetManagerChecked(NewWidgetManager);

	Subscribe(*NewUINotificationSubsystem);
}

void ABBHUD::Finalize()
{
	Unsubscribe(*GetUINotificationSubsystemChecked());

	UINotificationSubsystem = nullptr;
	WidgetManager = nullptr;
}

void ABBHUD::DrawMarquee(FVector2D MarqueeStart, FVector2D MarqueeEnd)
{
	DrawRect(HUDColor, MarqueeStart.X, MarqueeStart.Y, 0.0f, 0.0f);
	DrawRect(HUDColor, MarqueeEnd.X, MarqueeEnd.Y, 0.0f, 0.0f);

	DrawRect(HUDColor, MarqueeStart.X, MarqueeStart.Y, MarqueeEnd.X - MarqueeStart.X, MarqueeEnd.Y - MarqueeStart.Y);
}

void ABBHUD::AttachWidget(UIBBWidgetSpecification* Specification, UIBBWidgetComponent* WidgetComponent)
{
	verifyf(WidgetManager.IsValid(), TEXT("Widget Manager is invalid."));

	UIBBWidget* Widget = GetWidgetManagerChecked()->GetWidget(Specification);

	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	WidgetComponent->SetWidget(Widget);
}

void ABBHUD::DetachWidget(UIBBWidgetComponent* WidgetComponent)
{
	verifyf(IsValid(WidgetComponent), TEXT("WidgetComponent is invalid."));

	WidgetComponent->SetWidget(nullptr);
}

void ABBHUD::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	if (NewActiveMode == EBBGameMode::Build)
	{
		//UIBBBuildModel * Model = nullptr;

		//ModelPool->GetBuildModel(Model);

		//verifyf(IsValid(Model), TEXT("Build Model is invalid."));

		//UIBBWidget * Widget = Model->GetWidget();

		//verifyf(IsValid(Widget), TEXT("Build Widget is invalid."));

		//Widget->AddToScreen(0);
	}
}

// PROTECTED

void ABBHUD::OnOpenRequest_Implementation(const FUIRequestPayload& Payload)
{
	OpenWidget(Payload.Specification, Payload.bPopUp);
}


void ABBHUD::OnCloseRequest_Implementation(const FUIRequestPayload& Payload)
{
	CloseWidget(Payload.Specification);
}

UIBBWidgetManager* ABBHUD::GetWidgetManagerChecked() const
{
	verifyf(WidgetManager.IsValid(), TEXT("Widget Manager is invalid."));

	return WidgetManager.Get();
}

void ABBHUD::SetWidgetManagerChecked(UIBBWidgetManager* NewWidgetManager)
{
	verifyf(IsValid(NewWidgetManager), TEXT("New Widget Manager is invalid."));

	WidgetManager = NewWidgetManager;
}

UIBBUINotificationSubsystem* ABBHUD::GetUINotificationSubsystemChecked() const
{
	verifyf(UINotificationSubsystem.IsValid(), TEXT("UI Notification Subsystem is invalid."));
	
	return UINotificationSubsystem.Get();
}

void ABBHUD::SetUINotificationSubsystemChecked(UIBBUINotificationSubsystem* NewUINotificationSubsystem)
{
	verifyf(IsValid(NewUINotificationSubsystem), TEXT("New UI Notification Subsystem is invalid."));

	UINotificationSubsystem = NewUINotificationSubsystem;
}

void ABBHUD::AddWidgetToViewport(UIBBWidget& Widget, int32 ZOrder)
{
	Widget.SetVisibility(ESlateVisibility::Visible);
	Widget.AddToScreen(ZOrder);
}

void ABBHUD::Subscribe(UIBBUINotificationSubsystem& NewUINotificationSubsystem)
{
	Unsubscribe(*GetUINotificationSubsystemChecked());

	NewUINotificationSubsystem.RegisterListener<FUIRequestPayload, ABBHUD>
	(
		OpenRequestTag,
		this,
		&ABBHUD::OnOpenRequest
	);
}

void ABBHUD::Unsubscribe(UIBBUINotificationSubsystem& SubscribedUINotificationSubsystem)
{
	SubscribedUINotificationSubsystem.OnUIMessage().RemoveAll(this);
}

void ABBHUD::DisplayWidget(const UWorld* World, UIBBWidget* Widget, bool PopUp)
{
	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	Widget->RemoveFromParent();

	if (PopUp) Widget->SetPositionInViewport(UBBUIStatics::GetPopUpCoordinates(World, Widget), false);

	Widget->AddToScreen(0);
}

void ABBHUD::UpdateConsumer(TScriptInterface<IBBWorkable> Workable)
{
	verifyf(IsValid(Workable.GetObject()), TEXT("Workable is invalid."));

	OnConsumerUpdate().Broadcast(Workable->GetWorkComponent());
}

void ABBHUD::UpdateContext(TScriptInterface<IBBContextualizable> Contextualizable)
{
	verifyf(IsValid(Contextualizable.GetObject()), TEXT("Contextualizable is invalid."));

	OnContextUpdate().Broadcast(Contextualizable->GetContextComponent());
}

void ABBHUD::UpdateSelection(TScriptInterface<IBBSelectable> Selectable)
{
	verifyf(IsValid(Selectable.GetObject()), TEXT("Selectable is invalid."));

	OnSelectionUpdate().Broadcast(Selectable->GetSelectionComponent());
}



// PRIVATE

void ABBHUD::CloseWidget(const UIBBWidgetSpecification* Specification)
{
	verifyf(WidgetManager.IsValid(), TEXT("Widget Manager is invalid."));

	UIBBWidget* Widget = GetWidgetManagerChecked()->GetWidget(Specification);

	if (IsValid(Widget))
	{
		Widget->RemoveFromParent();
	}
}

void ABBHUD::OpenWidget(const UIBBWidgetSpecification* Specification, const bool PopUp)
{
	verifyf(WidgetManager.IsValid(), TEXT("Widget Manager is invalid."));

	UIBBWidget* Widget = GetWidgetManagerChecked()->GetWidget(Specification);

	DisplayWidget(GetWorld(), Widget, PopUp);
}