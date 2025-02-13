// SaltLakeCity 4.27

#include "BBHUDStub.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"

ABBHUDStub::ABBHUDStub() :
	Super()
{
	WidgetFactory = nullptr;
	WidgetSpecificationFactory = nullptr;
	WidgetSpecification = nullptr;
	AttachmentWidget = nullptr;

	ActiveGameMode = EBBGameMode::None;
}

void ABBHUDStub::BeginPlay()
{
	Super::BeginPlay();
}

void ABBHUDStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBHUDStub::Initialize(UIBBGameInstance * GameInstance, AIBBGameMode * GameMode, AIBBGameState * GameState, APlayerController * PlayerController)
{
}

void ABBHUDStub::Finalize()
{
}

const UIBBWidgetFactory * ABBHUDStub::GetWidgetFactory() const
{
	return WidgetFactory;
}

void ABBHUDStub::SetWidgetFactory(UIBBWidgetFactory * NewWidgetFactory)
{
	WidgetFactory = NewWidgetFactory;
}

const UIBBWidgetSpecificationFactory * ABBHUDStub::GetWidgetSpecificationFactory() const
{
	return WidgetSpecificationFactory;
}

void ABBHUDStub::SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory)
{
	WidgetSpecificationFactory = NewWidgetSpecificationFactory;
}

void ABBHUDStub::CloseWidget(UIBBWidgetSpecification * Specification)
{
	WidgetSpecification = Specification;
}

void ABBHUDStub::OpenWidget(UIBBWidgetSpecification * Specification, bool PopUp)
{
	WidgetSpecification = Specification;
	WidgetPopUp = PopUp;
}

void ABBHUDStub::AttachWidget(UIBBWidgetSpecification * Specification, UIBBWidgetComponent * WidgetComponent)
{
	if (IsValid(WidgetComponent))
	{
		WidgetComponent->SetWidget(AttachmentWidget);
	}
}

void ABBHUDStub::DetachWidget(UIBBWidgetComponent * WidgetComponent)
{
}

bool ABBHUDStub::ConvertToPIEViewportSpace(FVector2D & Position)
{
	return false;
}

void ABBHUDStub::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	ActiveGameMode = NewActiveMode;
}

EBBGameMode ABBHUDStub::GetActiveMode()
{
	return ActiveGameMode;
}

UIBBWidgetSpecification * ABBHUDStub::GetWidgetSpecification()
{
	return WidgetSpecification;
}

bool ABBHUDStub::GetPopUp()
{
	return WidgetPopUp;
}

void ABBHUDStub::SetAttachmentWidget(UUserWidget * NewAttachmentWidget)
{
	AttachmentWidget = NewAttachmentWidget;
}

void ABBHUDStub::BroadcastContextUpdate(UIBBContextComponent * ContextComponent)
{
	OnContextUpdate().Broadcast(ContextComponent);
}

void ABBHUDStub::BroadcastProgressUpdate(UIBBProgressComponent * ProgressComponent)
{
	OnProgressUpdate().Broadcast(ProgressComponent);
}

void ABBHUDStub::BroadcastSelectionUpdate(UIBBSelectionComponent * SelectionComponent)
{
	OnSelectionUpdate().Broadcast(SelectionComponent);
}

void ABBHUDStub::BroadcastConsumerUpdate(UIBBWorkComponent * WorkComponent)
{
	OnConsumerUpdate().Broadcast(WorkComponent);
}