// SaltLakeCity 4.27

#include "BBComponentFactory.h"
#include "AbilitySystemComponent.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "Actors/Components/Interfaces/IBBDecalComponent.h"
#include "Actors/Components/Interfaces/IBBPlayerAbilityComponent.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "Actors/Interfaces/IBBHighlightable.h"
#include "Actors/Interfaces/IBBProgressable.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "Controllers/Interfaces/IBBAIController.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "Engine/EngineTypes.h"
#include "Engine/SkeletalMeshSocket.h"


UBBComponentFactory::UBBComponentFactory() :
	Super()
{
	HUD = nullptr;
}

void UBBComponentFactory::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBComponentFactory::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBBComponentFactory::Initialize(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

void UBBComponentFactory::Finalize()
{
	HUD = nullptr;
}



bool UBBComponentFactory::NewAIAbilityComponent(UIBBAIAbilityComponent * & Component, AIBBAIController * Owner) const
{
	verifyf(!AIAbilityComponentClass.IsNull(), TEXT("AI Ability Component Class is null."));

	Component = NewObject<UIBBAIAbilityComponent>(Owner, AIAbilityComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		Owner->AddOwnedComponent(Component);
		Component->RegisterComponent();

		Component->Initialize(Owner, Component->GetAttributeSetsData());

		return true;
	}

	return false;
}

bool UBBComponentFactory::NewContextComponent(UIBBContextComponent * & Component, TScriptInterface<IBBContextualizable> Owner) const
{
	verifyf(!ContextComponentClass.IsNull(), TEXT("Context Component Class is null."));

	AActor * OwnerActor = Owner->ToActor();

	verifyf(IsValid(OwnerActor), TEXT("Owner Actor is invalid."));

	Component = NewObject<UIBBContextComponent>(OwnerActor, ContextComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();

		Component->Initialize(Forward<TScriptInterface<IBBContextualizable>>(Owner));

		return true;
	}

	return false;
}

bool UBBComponentFactory::NewDecalComponent(UIBBDecalComponent * & Component, TScriptInterface<IBBHighlightable> Owner) const
{
	verifyf(!DecalComponentClass.IsNull(), TEXT("Decal Component Class is null."));

	AActor * OwnerActor = Owner->ToActor();

	verifyf(IsValid(OwnerActor), TEXT("Owner Actor is invalid."));

	Component = NewObject<UIBBDecalComponent>(OwnerActor, DecalComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();
		Component->AttachToComponent(OwnerActor->GetRootComponent(), AttachmentRules);

		Component->Initialize(Forward<TScriptInterface<IBBHighlightable>>(Owner));

		return true;
	}

	return false;
}

bool UBBComponentFactory::NewPlayerAbilityComponent(UIBBPlayerAbilityComponent * & Component, AIBBPlayerController * Owner) const
{
	verifyf(!PlayerAbilityComponentClass.IsNull(), TEXT("Player Ability Component Class is null."));
	verifyf(IsValid(Owner), TEXT("Component Owner is invalid."));

	Component = NewObject<UIBBPlayerAbilityComponent>(Owner, PlayerAbilityComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		Owner->AddOwnedComponent(Component);
		Component->RegisterComponent();

		return true;
	}

	return false;
}

bool UBBComponentFactory::NewProgressComponent(UIBBProgressComponent * & Component, TScriptInterface<IBBProgressable> Owner) const
{
	verifyf(!ProgressComponentClass.IsNull(), TEXT("Progress Component Class is null."));

	AActor * OwnerActor = Owner->ToActor();

	verifyf(IsValid(OwnerActor), TEXT("Owner Actor is invalid."));

	Component = NewObject<UIBBProgressComponent>(OwnerActor, ProgressComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();
		Component->AttachToComponent(OwnerActor->GetRootComponent(), AttachmentRules);

		Component->Initialize(Forward<TScriptInterface<IBBProgressable>>(Owner));

		return true;
	}

	return false;
}

bool UBBComponentFactory::NewSelectionComponent(UIBBSelectionComponent * & Component, TScriptInterface<IBBSelectable> Owner) const
{
	verifyf(!SelectionComponentClass.IsNull(), TEXT("Selection Component Class is null."));

	AActor * OwnerActor = Owner->ToActor();

	verifyf(IsValid(OwnerActor), TEXT("Owner Actor is invalid."));

	Component = NewObject<UIBBSelectionComponent>(OwnerActor, SelectionComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();
		Component->AddRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
		Component->AttachToComponent(OwnerActor->GetRootComponent(), AttachmentRules);

		Component->Initialize(Forward<TScriptInterface<IBBSelectable>>(Owner));

		return true;
	}

	return false;
}

bool UBBComponentFactory::NewWidgetComponent(UIBBWidgetComponent * & Component, AActor * Owner) const
{
	verifyf(!WidgetComponentClass.IsNull(), TEXT("Widget Component Class is null."));
	verifyf(IsValid(Owner), TEXT("Component Owner is invalid."));

	Component = NewObject<UIBBWidgetComponent>(Owner, WidgetComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		Owner->AddOwnedComponent(Component);
		Component->RegisterComponent();
		Component->AttachToComponent(Owner->GetRootComponent(), AttachmentRules);

		return true;
	}

	return false;
}

bool UBBComponentFactory::NewWorkComponent(UIBBWorkComponent * & Component, TScriptInterface<IBBWorkable> Owner, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) const
{
	verifyf(!WorkComponentClass.IsNull(), TEXT("Work Component Class is null."));

	AActor * OwnerActor = Owner->ToActor();

	verifyf(IsValid(OwnerActor), TEXT("Owner Actor is invalid."));

	Component = NewObject<UIBBWorkComponent>(OwnerActor, WorkComponentClass.LoadSynchronous());

	if (IsValid(Component))
	{
		OwnerActor->AddOwnedComponent(Component);
		Component->RegisterComponent();

		Component->Initialize(Forward<TScriptInterface<IBBWorkable>>(Owner), NewAbilityComponent, NewJob);

		return true;
	}

	return false;
}