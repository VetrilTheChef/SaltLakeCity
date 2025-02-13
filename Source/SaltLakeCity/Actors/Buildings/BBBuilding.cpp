// SaltLakeCity 4.27

#include "BBBuilding.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

ABBBuilding::ABBBuilding() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(false);
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GameplayTags = FGameplayTagContainer();

	//ContextComponent = CreateDefaultSubobject<UIBBContextComponent, UBBContextComponent>(TEXT("BuildingContext"));
	//ProgressComponent = CreateDefaultSubobject<UIBBProgressComponent, UBBProgressComponent>(TEXT("BuildingProgress"));
	//SelectionComponent = CreateDefaultSubobject<UIBBSelectionComponent, UBBSelectionComponent>(TEXT("BuildingSelection"));
	ContextComponent = nullptr;
	ProgressComponent = nullptr;
	SelectionComponent = nullptr;

	DisplayName = FText::FromString("");

	ContextOptions.Empty();

	Price = -1.0f;
	BuildTime = -1.0f;

	Progress = -1.0f;
}

void ABBBuilding::BeginPlay()
{
	Super::BeginPlay();

	UIBBGameInstance * GameInstance = GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	const UIBBComponentFactory * ComponentFactory = GameInstance->GetComponentFactory();

	verifyf(IsValid(ComponentFactory), TEXT("Component Factory is invalid."));

	CreateContextComponent(* ComponentFactory);
	CreateSelectionComponent(* ComponentFactory);
	CreateProgressComponent(* ComponentFactory);
}

void ABBBuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyProgressComponent();
	DestroySelectionComponent();
	DestroyContextComponent();

	Super::EndPlay(EndPlayReason);
}

float ABBBuilding::GetPrice() const
{
	return Price;
}

void ABBBuilding::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float ABBBuilding::GetBuildTime() const
{
	return BuildTime;
}

void ABBBuilding::SetBuildTime(float NewBuildTime)
{
	BuildTime = NewBuildTime;
}

float ABBBuilding::GetProgress() const
{
	return Progress;
}

void ABBBuilding::SetProgress(float NewProgress)
{
	Progress = NewProgress;

	OnProgressUpdate().Broadcast(Progress);
}

void ABBBuilding::AddMaterialOverride(UMaterialInterface * NewMaterialOverride)
{
	verifyf(IsValid(NewMaterialOverride), TEXT("New Material override is invalid."));

	UStaticMeshComponent * Mesh = GetStaticMeshComponent();

	verifyf(IsValid(Mesh), TEXT("Static Mesh Component is invalid."));

	for (int i = 0; i < Mesh->GetNumMaterials(); i++)
	{
		Mesh->SetMaterial(i, NewMaterialOverride);
	}
}

void ABBBuilding::RemoveMaterialOverride()
{
	UStaticMeshComponent * Mesh = GetStaticMeshComponent();

	verifyf(IsValid(Mesh), TEXT("Static Mesh Component is invalid."));

	for (int i = 0; i < Mesh->GetNumMaterials(); i++)
	{
		Mesh->SetMaterial(i, nullptr);
	}
}

void ABBBuilding::StartBuilding()
{
	OnProgressInitiation().Broadcast();
}

void ABBBuilding::StopBuilding()
{
	OnProgressCompletion().Broadcast();
}

void ABBBuilding::UpdateContext(bool Contextualized)
{
	OnContextUpdate().Broadcast(Contextualized);
}


bool ABBBuilding::IsContextOption(EBBContext ContextOption) const
{
	return ContextOptions.Contains(ContextOption);
}

UIBBContextComponent * ABBBuilding::GetContextComponent() const
{
	return ContextComponent;
}

void ABBBuilding::UpdateSelection(bool Selected)
{
	OnSelectionUpdate().Broadcast(Selected);

	verifyf(IsValid(SelectionComponent), TEXT("Selection Component is invalid."));

	SelectionComponent->SetVisibility(Selected);

	verifyf(IsValid(ProgressComponent), TEXT("Progress Component is invalid."));

	ProgressComponent->SetVisibility(Selected);
}

UIBBSelectionComponent * ABBBuilding::GetSelectionComponent() const
{
	return SelectionComponent;
}

FText ABBBuilding::GetDisplayName(EBBDisplayName Mode) const
{
	return DisplayName;
}

AActor * ABBBuilding::ToActor()
{
	return this;
}

TScriptInterface<IBBWidgetTarget> ABBBuilding::ToWidgetTarget()
{
	return TScriptInterface<IBBWidgetTarget>(this);
}

void ABBBuilding::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayTags;
}

bool ABBBuilding::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return GameplayTags.HasTag(TagToCheck);
}

bool ABBBuilding::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTags.HasAll(TagContainer);
}

bool ABBBuilding::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTags.HasAny(TagContainer);
}



void ABBBuilding::CreateContextComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroyContextComponent();

	ComponentFactory.NewContextComponent(ContextComponent, TScriptInterface<IBBContextualizable>(this));
}

void ABBBuilding::CreateProgressComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroyProgressComponent();

	ComponentFactory.NewProgressComponent(ProgressComponent, TScriptInterface<IBBProgressable>(this));
}

void ABBBuilding::CreateSelectionComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroySelectionComponent();

	ComponentFactory.NewSelectionComponent(SelectionComponent, TScriptInterface<IBBSelectable>(this));
}

void ABBBuilding::DestroyContextComponent()
{
	if (IsValid(ContextComponent))
	{
		ContextComponent->Finalize();

		ContextComponent->DestroyComponent();
	}

	ContextComponent = nullptr;
}

void ABBBuilding::DestroyProgressComponent()
{
	if (IsValid(ProgressComponent))
	{
		ProgressComponent->Finalize();

		ProgressComponent->DestroyComponent();
	}

	ProgressComponent = nullptr;
}

void ABBBuilding::DestroySelectionComponent()
{
	if (IsValid(SelectionComponent))
	{
		SelectionComponent->Finalize();

		SelectionComponent->DestroyComponent();
	}

	SelectionComponent = nullptr;
}