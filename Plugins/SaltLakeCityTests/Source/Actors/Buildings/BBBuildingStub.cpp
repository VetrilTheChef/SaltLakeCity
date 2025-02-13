// SaltLakeCity 4.27

#include "BBBuildingStub.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"

ABBBuildingStub::ABBBuildingStub() :
	Super()
{
	SetActorEnableCollision(false);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GameplayTags = FGameplayTagContainer();

	ProgressComponent = nullptr;
	SelectionComponent = nullptr;

	DisplayName = FText::FromString("");

	ContextOptions.Empty();

	Price = -1.0f;
	BuildTime = -1.0f;

	Progress = -1.0f;
}

void ABBBuildingStub::BeginPlay()
{
	Super::BeginPlay();
}

void ABBBuildingStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

UIBBProgressComponent * ABBBuildingStub::GetProgressComponent() const
{
	return ProgressComponent;
}

void ABBBuildingStub::SetProgressComponent(UIBBProgressComponent * NewProgressComponent)
{
	if (IsValid(ProgressComponent))
	{
		ProgressComponent->DestroyComponent();
	}

	ProgressComponent = NewProgressComponent;

	if (IsValid(ProgressComponent))
	{
		AddOwnedComponent(ProgressComponent);
		ProgressComponent->RegisterComponent();
	}
}

float ABBBuildingStub::GetPrice() const
{
	return Price;
}

void ABBBuildingStub::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float ABBBuildingStub::GetBuildTime() const
{
	return BuildTime;
}

void ABBBuildingStub::SetBuildTime(float NewBuildTime)
{
	BuildTime = NewBuildTime;
}

float ABBBuildingStub::GetProgress() const
{
	return Progress;
}

void ABBBuildingStub::SetProgress(float NewProgress)
{
	Progress = NewProgress;
}

void ABBBuildingStub::AddMaterialOverride(UMaterialInterface * NewMaterialOverride)
{
	MaterialOverride = NewMaterialOverride;
}

void ABBBuildingStub::RemoveMaterialOverride()
{
	MaterialOverride = nullptr;
}

void ABBBuildingStub::StartBuilding()
{
	OnProgressInitiation().Broadcast();
}

void ABBBuildingStub::StopBuilding()
{
	OnProgressCompletion().Broadcast();
}

void ABBBuildingStub::UpdateContext(bool Contextualized)
{
	OnContextUpdate().Broadcast(Contextualized);
}

bool ABBBuildingStub::IsContextOption(EBBContext ContextOption) const
{
	return ContextOptions.Contains(ContextOption);
}

void ABBBuildingStub::SetContextOptions(TSet<EBBContext> NewContextOptions)
{
	ContextOptions = NewContextOptions;
}

UMaterialInterface * ABBBuildingStub::GetMaterialOverride()
{
	return MaterialOverride;
}

void ABBBuildingStub::UpdateSelection(bool Selected)
{
	OnSelectionUpdate().Broadcast(Selected);
}

UIBBSelectionComponent * ABBBuildingStub::GetSelectionComponent() const
{
	return SelectionComponent;
}

void ABBBuildingStub::SetSelectionComponent(UIBBSelectionComponent * NewSelectionComponent)
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

FText ABBBuildingStub::GetDisplayName(EBBDisplayName Mode) const
{
	return DisplayName;
}

void ABBBuildingStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}

AActor * ABBBuildingStub::ToActor()
{
	return this;
}

TScriptInterface<IBBWidgetTarget> ABBBuildingStub::ToWidgetTarget()
{
	return TScriptInterface<IBBWidgetTarget>(this);
}

void ABBBuildingStub::GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const
{
	TagContainer = GameplayTags;
}

void ABBBuildingStub::SetOwnedGameplayTags(FGameplayTagContainer & TagContainer)
{
	GameplayTags = TagContainer;
}

bool ABBBuildingStub::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return GameplayTags.HasTag(TagToCheck);
}

bool ABBBuildingStub::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTags.HasAll(TagContainer);
}

bool ABBBuildingStub::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTags.HasAny(TagContainer);
}