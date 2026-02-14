// SaltLakeCity 5.7

#include "BBHUDStub.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "GameInstances/Subsystems/Interfaces/IBBUINotificationSubsystem.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"

ABBHUDStub::ABBHUDStub() :
	Super()
{
	AttachmentWidget = nullptr;

	PresentationSubsystem = nullptr;
	WidgetManager = nullptr;

	ActiveGameMode = EBBGameMode::None;

	WidgetPopUp = false;
}

void ABBHUDStub::BeginPlay()
{
	Super::BeginPlay();
}

void ABBHUDStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBHUDStub::Initialize(UIBBPresentationSubsystem* NewPresentationSubsystem, UIBBWidgetManager* NewWidgetManager)
{
	PresentationSubsystem = NewPresentationSubsystem;
	WidgetManager = NewWidgetManager;
}

void ABBHUDStub::Finalize()
{
	PresentationSubsystem = nullptr;
	WidgetManager = nullptr;
}

/*void ABBHUDStub::CloseWidget(UIBBWidgetSpecification* Specification)
{
	WidgetSpecification = Specification;
}

void ABBHUDStub::OpenWidget(UIBBWidgetSpecification* Specification, bool PopUp)
{
	WidgetSpecification = Specification;
	WidgetPopUp = PopUp;
}*/

void ABBHUDStub::AttachWidget(UIBBWidgetSpecification* Specification, UIBBWidgetComponent* WidgetComponent)
{
	if (IsValid(WidgetComponent))
	{
		WidgetComponent->SetWidget(AttachmentWidget.Get());
	}
}

void ABBHUDStub::DetachWidget(UIBBWidgetComponent* WidgetComponent)
{
}

void ABBHUDStub::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	ActiveGameMode = NewActiveMode;
}

EBBGameMode ABBHUDStub::GetActiveMode()
{
	return ActiveGameMode;
}

UIBBWidgetSpecification* ABBHUDStub::GetWidgetSpecification()
{
	return WidgetSpecification.Get();
}

bool ABBHUDStub::GetPopUp()
{
	return WidgetPopUp;
}

void ABBHUDStub::SetAttachmentWidget(UUserWidget* NewAttachmentWidget)
{
	AttachmentWidget = NewAttachmentWidget;
}

void ABBHUDStub::BroadcastContextUpdate(UIBBContextComponent* ContextComponent)
{
	OnContextUpdate().Broadcast(ContextComponent);
}

void ABBHUDStub::BroadcastProgressUpdate(UIBBProgressComponent* ProgressComponent)
{
	OnProgressUpdate().Broadcast(ProgressComponent);
}

void ABBHUDStub::BroadcastSelectionUpdate(UIBBSelectionComponent* SelectionComponent)
{
	OnSelectionUpdate().Broadcast(SelectionComponent);
}

void ABBHUDStub::BroadcastConsumerUpdate(UIBBWorkComponent* WorkComponent)
{
	OnConsumerUpdate().Broadcast(WorkComponent);
}



void ABBHUDStub::OnOpenRequest_Implementation(const FUIRequestPayload& Payload)
{
}


void ABBHUDStub::OnCloseRequest_Implementation(const FUIRequestPayload& Payload)
{
}