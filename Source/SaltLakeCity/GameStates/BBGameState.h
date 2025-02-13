// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "BBGameState.generated.h"

/**
*
*/

class AIBBGameGrid;
class UIBBAbilityData;
class UIBBJobManager;
class UIBBGameAbilityComponent;
class UIBBGameClock;
class UIBBPlayerAbilityComponent;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API ABBGameState : public AIBBGameState
{
	GENERATED_BODY()

	public:
		ABBGameState();

		virtual void BeginPlay() override;

		virtual void BeginDestroy() override;

		virtual void HandleEndPlay();

		virtual void Initialize(AIBBLevelScriptActor * LevelScriptActor) override;

		virtual void Finalize(AIBBLevelScriptActor * LevelScriptActor) override;

		virtual void Tick(float DeltaTime) override;

		virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

		virtual int GetStartingYear() const override;

		virtual float GetTimeUnit() const override;

		virtual UIBBGameClock * GetGameClock() const override;

		virtual TScriptInterface<IBBContextualizable> GetContext() const override;

		virtual void SetContext(TScriptInterface<IBBContextualizable> && NewContextualizable) override;

		virtual TScriptInterface<IBBSelectable> GetSelection() const override;

		virtual void SetSelection(TScriptInterface<IBBSelectable> && NewSelectable) override;

		virtual const int GetGridActiveLayer() const override;

		virtual bool SetGridActiveLayer(const int NewActiveLayerIndex) override;

		virtual void SetGridVisibility(bool Visible) override;

		virtual bool GetGridPosition(const FVector InPosition, FVector & OutPosition, bool & IsBuildable) const override;

		virtual const float GetGridHeight() const override;

		virtual void AddConsumer(UIBBWorkComponent * Consumer, EBBJob Job) override;

		virtual void RemoveConsumer(UIBBWorkComponent * Consumer, EBBJob Job) override;

		virtual void AddProducer(UIBBPlayerAbilityComponent * PlayerAbilityComponent) override;

		virtual void RemoveProducer(UIBBPlayerAbilityComponent * PlayerAbilityComponent) override;

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

		virtual void UpdateConsumer(TScriptInterface<IBBWorkable> NewWorkable) override;

		virtual void UpdateContext(TScriptInterface<IBBContextualizable> NewContextualizable) override;

		virtual void UpdateSelection(TScriptInterface<IBBSelectable> NewSelectable) override;

		virtual void HandleFloorChangeRequest(const int TargetFloorDelta, float & TargetFloorHeight) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TSoftClassPtr<UIBBGameAbilityComponent> GameAbilityComponentClass;

		UPROPERTY(Category = "Game Grid", EditDefaultsOnly, BlueprintReadWrite)
		TSoftClassPtr<AIBBGameGrid> GameGridClass;

		UPROPERTY(EditAnywhere, Category = "Managers")
		TMap<EBBJob, TSoftClassPtr<UIBBJobManager>> JobManagerClasses;

		UPROPERTY(Category = "Time", EditDefaultsOnly, BlueprintReadWrite)
		int StartingYear;

		UPROPERTY(Category = "Time", EditDefaultsOnly, BlueprintReadWrite)
		float TimeUnit;

		UPROPERTY(Category = "Time", EditDefaultsOnly, BlueprintReadWrite)
		TSoftClassPtr<UIBBGameClock> GameClockClass;

		UPROPERTY()
		UIBBGameAbilityComponent * GameAbilityComponent;

		UPROPERTY()
		TScriptInterface<IBBContextualizable> Contextualizable;

		UPROPERTY()
		TScriptInterface<IBBSelectable> Selectable;

		UPROPERTY()
		TScriptInterface<IBBWorkable> Workable;

		UPROPERTY()
		AIBBGameGrid * GameGrid;

		UPROPERTY()
		UIBBGameClock * GameClock;

		UPROPERTY()
		TMap<EBBJob, UIBBJobManager *> JobManagers;

		virtual void CreateGameClock();

		virtual void CreateJobManagers();

		virtual void DestroyGameClock();

		virtual void DestroyJobManagers();

		virtual void InitializeGameGrid(const AIBBLevelScriptActor & LevelScriptActor);

		virtual void InitializeLevelScriptActor(AIBBLevelScriptActor & LevelScriptActor);

		virtual void FinalizeGameGrid();

		virtual void FinalizeLevelScriptActor(AIBBLevelScriptActor * LevelScriptActor);

		void TickGameClock(float DeltaSeconds);

		void CreateUnemployedManager();

		void CreateBuildManager();

		void DestroyUnemployedManager();

		void DestroyBuildManager();

		UFUNCTION()
		void QueueTask(const UIBBAbilityData * AbilityData);
};