// SaltLakeCity 4.27

#include "BBGameStateStub.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"

ABBGameStateStub::ABBGameStateStub() :
	Super()
{
	GameClock = nullptr;

	Contextualizable = TScriptInterface<IBBContextualizable>();
	Selectable = TScriptInterface<IBBSelectable>();
	Workable = TScriptInterface<IBBWorkable>();

	ConsumersMap.Empty();
	TasksMap.Empty();
	Producers.Empty();

	ActiveGameMode = EBBGameMode::None;
	FloorDelta = 0;
	FloorHeight = 0;
}

void ABBGameStateStub::BeginPlay()
{
	Super::BeginPlay();

	ConsumersMap.Empty();
	ConsumersMap.Emplace(EBBJob::None, FBBConsumerCategory());
	ConsumersMap.Emplace(EBBJob::Idle, FBBConsumerCategory());
	ConsumersMap.Emplace(EBBJob::Builder, FBBConsumerCategory());

	TasksMap.Empty();
	TasksMap.Emplace(EBBJob::None, FBBTaskCategory());
	TasksMap.Emplace(EBBJob::Idle, FBBTaskCategory());
	TasksMap.Emplace(EBBJob::Builder, FBBTaskCategory());

	Producers.Empty();
}

void ABBGameStateStub::Initialize(AIBBLevelScriptActor * LevelScriptActor)
{
}

void ABBGameStateStub::Finalize(AIBBLevelScriptActor * LevelScriptActor)
{
}

void ABBGameStateStub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UIBBGameClock * ABBGameStateStub::GetGameClock() const
{
	return GameClock;
}

void ABBGameStateStub::SetGameClock(UIBBGameClock * NewGameClock)
{
	GameClock = NewGameClock;
}

TScriptInterface<IBBContextualizable> ABBGameStateStub::GetContext() const
{
	return Contextualizable;
}

void ABBGameStateStub::SetContext(TScriptInterface<IBBContextualizable> && NewContextualizable)
{
	if (Contextualizable != NewContextualizable)
	{
		Contextualizable = NewContextualizable;

		OnContextUpdate().Broadcast(Forward<TScriptInterface<IBBContextualizable>>(Contextualizable));
	}
}

TScriptInterface<IBBSelectable> ABBGameStateStub::GetSelection() const
{
	return Selectable;
}

void ABBGameStateStub::SetSelection(TScriptInterface<IBBSelectable> && NewSelectable)
{
	if (Selectable != NewSelectable)
	{
		Selectable = NewSelectable;

		OnSelectionUpdate().Broadcast(Forward<TScriptInterface<IBBSelectable>>(Selectable));
	}
}

void ABBGameStateStub::AddConsumer(UIBBWorkComponent * Consumer, EBBJob Job)
{
	FBBConsumerCategory & ConsumerCategory = ConsumersMap.FindChecked(Job);

	ConsumerCategory.Available.Emplace(Consumer);
}

void ABBGameStateStub::RemoveConsumer(UIBBWorkComponent * Consumer, EBBJob Job)
{
	FBBConsumerCategory & ConsumerCategory = ConsumersMap.FindChecked(Job);

	ConsumerCategory.Available.Remove(Consumer);
	ConsumerCategory.Busy.Remove(Consumer);
}

void ABBGameStateStub::AddProducer(UIBBPlayerAbilityComponent * PlayerAbilityComponent)
{
	Producers.Emplace(PlayerAbilityComponent);
}

void ABBGameStateStub::RemoveProducer(UIBBPlayerAbilityComponent * PlayerAbilityComponent)
{
	Producers.Remove(PlayerAbilityComponent);
}

TArray<UIBBWorkComponent *> ABBGameStateStub::GetConsumers(EBBJob Work)
{
	TArray<UIBBWorkComponent *> Consumers = ConsumersMap.FindRef(Work).Available;
	Consumers.Append(ConsumersMap.FindRef(Work).Busy);

	return Consumers;
}

EBBGameMode ABBGameStateStub::GetActiveMode()
{
	return ActiveGameMode;
}

void ABBGameStateStub::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	ActiveGameMode = NewActiveMode;
}

void ABBGameStateStub::UpdateConsumer(TScriptInterface<IBBWorkable> NewWorkable)
{
	Workable = NewWorkable;

	OnConsumerUpdate().Broadcast(Forward<TScriptInterface<IBBWorkable>>(Workable));
}

void ABBGameStateStub::UpdateContext(TScriptInterface<IBBContextualizable> NewContextualizable)
{
	SetContext(Forward<TScriptInterface<IBBContextualizable>>(NewContextualizable));
}

void ABBGameStateStub::UpdateSelection(TScriptInterface<IBBSelectable> NewSelectable)
{
	SetSelection(Forward<TScriptInterface<IBBSelectable>>(NewSelectable));
}

void ABBGameStateStub::HandleFloorChangeRequest(const int TargetFloorDelta, float & TargetFloorHeight)
{
	FloorDelta = TargetFloorDelta;
	FloorHeight = TargetFloorHeight;
}

int ABBGameStateStub::GetRequestedTargetFloorDelta()
{
	return FloorDelta;
}

float ABBGameStateStub::GetRequestedTargetFloorHeight()
{
	return FloorHeight;
}



void ABBGameStateStub::QueueWork(const UIBBAbilityData * AbilityData)
{
}