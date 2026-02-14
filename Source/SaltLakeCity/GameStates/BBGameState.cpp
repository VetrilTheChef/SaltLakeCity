// SaltLakeCity 5.7

#include "BBGameState.h"
#include "Landscape.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"
#include "Actors/Components/Interfaces/IBBPlayerAbilityComponent.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Actors/Grids/Interfaces/IBBGameGrid.h"
#include "Components/Interfaces/IBBGameAbilityComponent.h"
#include "Controllers/BBPlayerController.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GameModes/BBGameMode.h"
#include "GameStates/Components/BBGameClock.h"
#include "Jobs/Managers/Interfaces/IBBJobManager.h"
#include "Levels/Interfaces/IBBLevelScriptActor.h"
#include "Levels/WorldSettings/Interfaces/IBBWorldSettings.h"

ABBGameState::ABBGameState() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;
	bAllowTickBeforeBeginPlay = false;

	GameAbilityComponent = nullptr;
	Contextualizable = TScriptInterface<IBBContextualizable>(nullptr);
	Selectable = TScriptInterface<IBBSelectable>(nullptr);
	Workable = TScriptInterface<IBBWorkable>(nullptr);
	GameGrid = nullptr;
	GameClock = nullptr;

	JobManagers.Empty();
}

void ABBGameState::BeginPlay()
{
	Super::BeginPlay();

	CreateGameClock();
	CreateJobManagers();
}

void ABBGameState::BeginDestroy()
{
	DestroyJobManagers();
	DestroyGameClock();

	Super::BeginDestroy();
}

void ABBGameState::HandleEndPlay()
{
	AIBBWorldSettings * WorldSettings = Cast<AIBBWorldSettings>(GetWorldSettings());

	verifyf(IsValid(WorldSettings), TEXT("World Settings is invalid."));

	WorldSettings->NotifyEndPlay();
}

void ABBGameState::Initialize(AIBBLevelScriptActor * LevelScriptActor)
{
	verifyf(IsValid(LevelScriptActor), TEXT("Level Script Actor is invalid."));

	InitializeGameGrid(* LevelScriptActor);
	InitializeLevelScriptActor(* LevelScriptActor);
}

void ABBGameState::Finalize(AIBBLevelScriptActor * LevelScriptActor)
{
	FinalizeLevelScriptActor(LevelScriptActor);
	FinalizeGameGrid();
}

void ABBGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickGameClock(DeltaSeconds);
}

UAbilitySystemComponent * ABBGameState::GetAbilitySystemComponent() const
{
	return GameAbilityComponent;
}

int ABBGameState::GetStartingYear() const
{
	return StartingYear;
}

float ABBGameState::GetTimeUnit() const
{
	return TimeUnit;
}

UIBBGameClock * ABBGameState::GetGameClock() const
{
	return GameClock;
}

TScriptInterface<IBBContextualizable> ABBGameState::GetContext() const
{
	return Contextualizable;
}

void ABBGameState::SetContext(TScriptInterface<IBBContextualizable> && NewContextualizable)
{
	if (Contextualizable != NewContextualizable)
	{
		Contextualizable = NewContextualizable;

		OnContextUpdate().Broadcast(Forward<TScriptInterface<IBBContextualizable>>(Contextualizable));
	}
}

TScriptInterface<IBBSelectable> ABBGameState::GetSelection() const
{
	return Selectable;
}

void ABBGameState::SetSelection(TScriptInterface<IBBSelectable> && NewSelectable)
{
	if (Selectable != NewSelectable)
	{
		Selectable = NewSelectable;

		OnSelectionUpdate().Broadcast(Forward<TScriptInterface<IBBSelectable>>(Selectable));
	}
}

const int ABBGameState::GetGridActiveLayer() const
{
	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));

	return GameGrid->GetActiveLayer();
}

bool ABBGameState::SetGridActiveLayer(const int NewActiveLayerIndex)
{
	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));

	return GameGrid->SetActiveLayer(NewActiveLayerIndex);
}

void ABBGameState::SetGridVisibility(bool Visible)
{
	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));

	GameGrid->SetGridVisibility(Visible);
}

bool ABBGameState::GetGridPosition(const FVector InPosition, FVector & OutPosition, bool & IsBuildable) const
{
	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));

	FVector2D InPosition2D = FVector2D(InPosition.X, InPosition.Y);
	FIntPoint GridPosition2D;
	float GridSize;
	float GridHeight;

	if (GameGrid->GetGridPosition(InPosition2D, GridPosition2D) &&
		GameGrid->GetGridSize(GridSize) &&
		GameGrid->GetGridHeight(GridHeight))
	{
		OutPosition.X = GridPosition2D.X * GridSize;
		OutPosition.Y = GridPosition2D.Y * GridSize;
		OutPosition.Z = GridHeight;

		IsBuildable = GameGrid->IsGridPositionBuildable(GridPosition2D);

		return true;
	}

	return false;
}

const float ABBGameState::GetGridHeight() const
{
	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));
	
	float OutHeight = 0.0f;

	GameGrid->GetGridHeight(OutHeight);

	return OutHeight;
}

void ABBGameState::AddConsumer(UIBBWorkComponent * Consumer, EBBJob Job)
{
	verifyf(IsValid(Consumer), TEXT("Consumer is invalid."));

	UIBBJobManager * JobManager = JobManagers.FindChecked(Job);

	verifyf(IsValid(JobManager), TEXT("Manager is invalid."));

	JobManager->AddConsumer(Consumer);
}

void ABBGameState::RemoveConsumer(UIBBWorkComponent * Consumer, EBBJob Job)
{
	verifyf(IsValid(Consumer), TEXT("Consumer is invalid."));

	UIBBJobManager * JobManager = JobManagers.FindChecked(Job);

	verifyf(IsValid(JobManager), TEXT("Manager is invalid."));

	JobManager->RemoveConsumer(Consumer);
}

void ABBGameState::AddProducer(UIBBPlayerAbilityComponent * PlayerAbilityComponent)
{
	verifyf(IsValid(PlayerAbilityComponent), TEXT("Player Ability Component is invalid."));

	PlayerAbilityComponent->OnJobQueued.AddDynamic(this, & ABBGameState::QueueTask);
}

void ABBGameState::RemoveProducer(UIBBPlayerAbilityComponent * PlayerAbilityComponent)
{
	verifyf(IsValid(PlayerAbilityComponent), TEXT("Player Ability Component is invalid."));

	PlayerAbilityComponent->OnJobQueued.RemoveDynamic(this, & ABBGameState::QueueTask);
}

void ABBGameState::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));

	GameGrid->SetGridVisibility(NewActiveMode == EBBGameMode::Build);
}

void ABBGameState::UpdateConsumer(TScriptInterface<IBBWorkable> NewWorkable)
{
	Workable = NewWorkable;

	OnConsumerUpdate().Broadcast(Forward<TScriptInterface<IBBWorkable>>(Workable));
}

void ABBGameState::UpdateContext(TScriptInterface<IBBContextualizable> NewContextualizable)
{
	SetContext(Forward<TScriptInterface<IBBContextualizable>>(NewContextualizable));
}

void ABBGameState::UpdateSelection(TScriptInterface<IBBSelectable> NewSelectable)
{
	SetSelection(Forward<TScriptInterface<IBBSelectable>>(NewSelectable));
}

void ABBGameState::HandleFloorChangeRequest(const int TargetFloorDelta, float & TargetFloorHeight)
{
	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));

	int TargetFloor = FMath::Clamp(GameGrid->GetActiveLayer() + TargetFloorDelta, 0, GameGrid->GetNumLayers());

	if (GameGrid->SetActiveLayer(TargetFloor))
	{
		GameGrid->GetGridHeight(TargetFloorHeight);
	}
}



void ABBGameState::CreateGameClock()
{
	verifyf(!GameClockClass.IsNull(), TEXT("Game Clock Class is null."));

	GameClock = NewObject<UIBBGameClock>(this, GameClockClass.LoadSynchronous());

	verifyf(IsValid(GameClock), TEXT("Game Clock is invalid."));

	int Month = FMath::RandRange(1, 12);
	int Day = FMath::RandRange(1, FDateTime::DaysInMonth(StartingYear, Month));

	UE_LOG(LogTemp, Warning, TEXT("Starting Month: %i"), Month);
	UE_LOG(LogTemp, Warning, TEXT("Starting Day: %i"), Day);

	GameClock->Initialize(StartingYear, Month, Day, 9, 0, TimeUnit);
}

void ABBGameState::CreateJobManagers()
{
	for (TPair<EBBJob, TSoftClassPtr<UIBBJobManager>> & JobManagerClass : JobManagerClasses)
	{
		verifyf(!JobManagerClass.Value.IsNull(), TEXT("Job Manager Class is null."));

		UIBBJobManager * JobManager = NewObject<UIBBJobManager>(this, JobManagerClass.Value.LoadSynchronous());

		verifyf(IsValid(JobManager), TEXT("Job Manager is invalid."));

		JobManager->Initialize();

		JobManagers.Add(JobManagerClass.Key, JobManager);
	}
}

void ABBGameState::DestroyGameClock()
{
	if (IsValid(GameClock))
	{
		GameClock->MarkAsGarbage();
	}

	GameClock = nullptr;
}

void ABBGameState::DestroyJobManagers()
{
	for (TPair<EBBJob, UIBBJobManager *> JobManager : JobManagers)
	{
		JobManager.Value->Finalize();
		JobManager.Value->MarkAsGarbage();
	}

	JobManagers.Empty();
}

void ABBGameState::InitializeGameGrid(const AIBBLevelScriptActor & LevelScriptActor)
{
	verifyf(!GameGridClass.IsNull(), TEXT("Game Grid class is null."));

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	ALandscape * Landscape = LevelScriptActor.GetLandscape();

	verifyf(IsValid(Landscape), TEXT("Landscape is invalid."));

	FVector LevelBounds = LevelScriptActor.GetLevelBounds();
	LevelBounds.X = 0.02f * LevelBounds.X;
	LevelBounds.Y = 0.02f * LevelBounds.Y;
	LevelBounds.Z = 1.0f;

	FVector Location = Landscape->GetActorLocation();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GameGrid = World->SpawnActor<AIBBGameGrid>(GameGridClass.LoadSynchronous(), SpawnParameters);

	verifyf(IsValid(GameGrid), TEXT("Game Grid is invalid."));

	Location.X = GameGrid->GetActorLocation().X;
	Location.Y = GameGrid->GetActorLocation().Y;

	GameGrid->SetActorLocation(Location);
	GameGrid->SetActorScale3D(LevelBounds);
	GameGrid->SetVisibility(true);

	GameGrid->Initialize();

	GameGrid->AddToLayer(Landscape, GameGrid->GetGroundLayer());
}

void ABBGameState::InitializeLevelScriptActor(AIBBLevelScriptActor & LevelScriptActor)
{
	LevelScriptActor.Initialize(GameClock);
}

void ABBGameState::FinalizeGameGrid()
{
	if (IsValid(GameGrid))
	{
		GameGrid->Finalize();
		GameGrid->MarkAsGarbage();
	}
}

void ABBGameState::FinalizeLevelScriptActor(AIBBLevelScriptActor * LevelScriptActor)
{
	if (IsValid(LevelScriptActor))
	{
		LevelScriptActor->Finalize();
	}
}

void ABBGameState::TickGameClock(float DeltaSeconds)
{
	verifyf(IsValid(GameClock), TEXT("Game Clock is invalid."));

	GameClock->Tick(DeltaSeconds);
}

void ABBGameState::QueueTask(const UIBBAbilityData * AbilityData)
{
	verifyf(IsValid(AbilityData), TEXT("Ability Data is not valid."));

	UIBBJobManager * JobManager = JobManagers.FindRef(AbilityData->GetJobType());

	JobManager->AddTask(AbilityData);
}