// SaltLakeCity 4.27

#include "BBComponentFactoryStub.h"
#include "Actors/BBActor.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "Actors/Components/Interfaces/IBBDecalComponent.h"
#include "Actors/Components/Interfaces/IBBPlayerAbilityComponent.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Actors/Interfaces/IBBHighlightable.h"
#include "Actors/Interfaces/IBBProgressable.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "Engine/SkeletalMeshSocket.h"
#include "IOC/BBIOC.h"

UBBComponentFactoryStub::UBBComponentFactoryStub() :
	Super()
{
	HUD = nullptr;

	AIAbilityComponents.Empty();
	ContextComponents.Empty();
	DecalComponents.Empty();
	PlayerAbilityComponents.Empty();
	ProgressComponents.Empty();
	SelectionComponents.Empty();
	WidgetComponents.Empty();
	WorkComponents.Empty();
}

void UBBComponentFactoryStub::Initialize(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

void UBBComponentFactoryStub::Finalize()
{
	HUD = nullptr;
}

void UBBComponentFactoryStub::AddAIAbilityComponent(UIBBAIAbilityComponent * Component)
{
	AIAbilityComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewAIAbilityComponent(UIBBAIAbilityComponent * & Component, AIBBAIController * Owner) const
{
	Component = AIAbilityComponents.Num() > 0 ? AIAbilityComponents.Pop() : nullptr;

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, Owner);

		Owner->AddOwnedComponent(Component);
		Component->RegisterComponent();

		Component->Initialize(Owner, Component->GetAttributeSetsData());

		return true;
	}

	return false;
}

void UBBComponentFactoryStub::AddContextComponent(UIBBContextComponent * Component)
{
	ContextComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewContextComponent(UIBBContextComponent * & Component, TScriptInterface<IBBContextualizable> Owner) const
{
	Component = ContextComponents.Num() > 0 ? ContextComponents.Pop() : nullptr;
	AActor * OwnerActor = Owner->ToActor();

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, OwnerActor);

		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();

		Component->Initialize(Forward<TScriptInterface<IBBContextualizable>>(Owner));

		return true;
	}

	return false;
}

void UBBComponentFactoryStub::AddDecalComponent(UIBBDecalComponent * Component)
{
	DecalComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewDecalComponent(UIBBDecalComponent * & Component, TScriptInterface<IBBHighlightable> Owner) const
{
	Component = DecalComponents.Num() > 0 ? DecalComponents.Pop() : nullptr;
	AActor * OwnerActor = Owner->ToActor();

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, OwnerActor);

		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();
		Component->AttachToComponent(OwnerActor->GetRootComponent(), AttachmentRules);

		Component->Initialize(Forward<TScriptInterface<IBBHighlightable>>(Owner));

		return true;
	}

	return false;
}

void UBBComponentFactoryStub::AddPlayerAbilityComponent(UIBBPlayerAbilityComponent * Component)
{
	PlayerAbilityComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewPlayerAbilityComponent(UIBBPlayerAbilityComponent * & Component, AIBBPlayerController * Owner) const
{
	Component = PlayerAbilityComponents.Num() > 0 ? PlayerAbilityComponents.Pop() : nullptr;

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, Owner);

		Owner->AddOwnedComponent(Component);
		Component->RegisterComponent();

		return true;
	}

	return false;
}

void UBBComponentFactoryStub::AddProgressComponent(UIBBProgressComponent * Component)
{
	ProgressComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewProgressComponent(UIBBProgressComponent * & Component, TScriptInterface<IBBProgressable> Owner) const
{
	Component = ProgressComponents.Num() > 0 ? ProgressComponents.Pop() : nullptr;
	AActor * OwnerActor = Owner->ToActor();

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, OwnerActor);

		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();
		Component->AttachToComponent(OwnerActor->GetRootComponent(), AttachmentRules);

		Component->Initialize(Forward<TScriptInterface<IBBProgressable>>(Owner));
		Component->SetWidget(nullptr);

		return true;
	}

	return false;
}

void UBBComponentFactoryStub::AddSelectionComponent(UIBBSelectionComponent * Component)
{
	SelectionComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewSelectionComponent(UIBBSelectionComponent * & Component, TScriptInterface<IBBSelectable> Owner) const
{
	Component = SelectionComponents.Num() > 0 ? SelectionComponents.Pop() : nullptr;
	AActor * OwnerActor = Owner->ToActor();

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, OwnerActor);

		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();

		Component->Initialize(Forward<TScriptInterface<IBBSelectable>>(Owner));

		return true;
	}

	return false;
}

void UBBComponentFactoryStub::AddWidgetComponent(UIBBWidgetComponent * Component)
{
	WidgetComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewWidgetComponent(UIBBWidgetComponent * & Component, AActor * Owner) const
{
	Component = WidgetComponents.Num() > 0 ? WidgetComponents.Pop() : nullptr;

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, Owner);

		Owner->AddOwnedComponent(Component);
		Component->RegisterComponent();

		return true;
	}

	return false;
}

void UBBComponentFactoryStub::AddWorkComponent(UIBBWorkComponent * Component)
{
	WorkComponents.EmplaceAt(0, Component);
}

bool UBBComponentFactoryStub::NewWorkComponent(UIBBWorkComponent * & Component, TScriptInterface<IBBWorkable> Owner, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) const
{
	Component = WorkComponents.Num() > 0 ? WorkComponents.Pop() : nullptr;
	AActor * OwnerActor = Owner->ToActor();

	if (IsValid(Component))
	{
		// Sets the new outer (AddOwnedComponent checks that the actor owns the component)
		Component->Rename(nullptr, OwnerActor);

		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();

		Component->Initialize(Forward<TScriptInterface<IBBWorkable>>(Owner), NewAbilityComponent, NewJob);

		return true;
	}

	return false;
}