// SaltLakeCity 4.27

#include "BBCharacterStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "Actors/Components/Interfaces/IBBDecalComponent.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"

ABBCharacterStub::ABBCharacterStub() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;

	JumpMaxCount = 0;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = nullptr;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	SetActorEnableCollision(true);

	AbilityComponent = nullptr;
	ContextComponent = nullptr;
	DecalComponent = nullptr;
	SelectionComponent = nullptr;
	WorkComponent = nullptr;

	DisplayName = FText::FromString("");

	ContextOptions.Empty();
	Task = nullptr;
}

void ABBCharacterStub::BeginPlay()
{
	Super::BeginPlay();
}

void ABBCharacterStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBCharacterStub::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);
}

void ABBCharacterStub::UnPossessed()
{
	Super::UnPossessed();
}

UAbilitySystemComponent * ABBCharacterStub::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

void ABBCharacterStub::SetAbilitySystemComponent(UAbilitySystemComponent * NewAbilityComponent)
{
	if (IsValid(AbilityComponent))
	{
		AbilityComponent->DestroyComponent();
	}

	AbilityComponent = NewAbilityComponent;

	if (IsValid(AbilityComponent))
	{
		AddOwnedComponent(AbilityComponent);
		AbilityComponent->RegisterComponent();
	}
}

void ABBCharacterStub::UpdateContext(bool Contextualized)
{
	OnContextUpdate().Broadcast(Contextualized);
}

bool ABBCharacterStub::IsContextOption(EBBContext ContextOption) const
{
	return ContextOptions.Contains(ContextOption);
}

void ABBCharacterStub::SetContextOptions(TSet<EBBContext> NewContextOptions)
{
	ContextOptions = NewContextOptions;
}

UIBBContextComponent * ABBCharacterStub::GetContextComponent() const
{
	return ContextComponent;
}

void ABBCharacterStub::SetContextComponent(UIBBContextComponent * NewContextComponent)
{
	if (IsValid(ContextComponent))
	{
		ContextComponent->DestroyComponent();
	}

	ContextComponent = NewContextComponent;

	if (IsValid(ContextComponent))
	{
		AddOwnedComponent(ContextComponent);
		ContextComponent->RegisterComponent();
	}
}

void ABBCharacterStub::UpdateHighlight(bool Highlighted)
{
	OnHighlightUpdate().Broadcast(Highlighted);
}

UIBBDecalComponent * ABBCharacterStub::GetDecalComponent() const
{
	return DecalComponent;
}

void ABBCharacterStub::SetDecalComponent(UIBBDecalComponent * NewDecalComponent)
{
	if (IsValid(DecalComponent))
	{
		DecalComponent->DestroyComponent();
	}

	DecalComponent = NewDecalComponent;

	if (IsValid(DecalComponent))
	{
		AddOwnedComponent(DecalComponent);
		DecalComponent->RegisterComponent();
	}
}

void ABBCharacterStub::UpdateSelection(bool Selected)
{
	OnSelectionUpdate().Broadcast(Selected);

	UpdateHighlight(Selected);
}

UIBBSelectionComponent * ABBCharacterStub::GetSelectionComponent() const
{
	return SelectionComponent;
}

void ABBCharacterStub::SetSelectionComponent(UIBBSelectionComponent * NewSelectionComponent)
{
	if (IsValid(SelectionComponent))
	{
		SelectionComponent->DestroyComponent();
	}

	SelectionComponent = NewSelectionComponent;

	if (IsValid(SelectionComponent))
	{
		AddOwnedComponent(SelectionComponent);
		SelectionComponent->RegisterComponent();
	}
}

UIBBWorkComponent * ABBCharacterStub::GetWorkComponent() const
{
	return WorkComponent;
}

void ABBCharacterStub::SetWorkComponent(UIBBWorkComponent * NewWorkComponent)
{
	if (IsValid(WorkComponent))
	{
		WorkComponent->DestroyComponent();
	}

	WorkComponent = NewWorkComponent;

	if (IsValid(WorkComponent))
	{
		AddOwnedComponent(WorkComponent);
		WorkComponent->RegisterComponent();
	}
}

FText ABBCharacterStub::GetDisplayName(EBBDisplayName Mode) const
{
	return DisplayName;
}

void ABBCharacterStub::SetFirstName(FText NewFirstName)
{
	SetDisplayName(NewFirstName);
}

void ABBCharacterStub::SetCodeName(FText NewCodeName)
{
	SetDisplayName(NewCodeName);
}

void ABBCharacterStub::SetLastName(FText NewLastName)
{
	SetDisplayName(NewLastName);
}

void ABBCharacterStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;

	OnWidgetTargetUpdate().Broadcast();
}

AActor * ABBCharacterStub::ToActor()
{
	return this;
}

TScriptInterface<IBBWidgetTarget> ABBCharacterStub::ToWidgetTarget()
{
	return TScriptInterface<IBBWidgetTarget>(this);
}

void ABBCharacterStub::LeftClick()
{
	OnClicked.Broadcast(this, EKeys::LeftMouseButton);
}

void ABBCharacterStub::RightClick()
{
	OnClicked.Broadcast(this, EKeys::RightMouseButton);
}