// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "BBGameStateStub.generated.h"

/**
 * 
 */

class UIBBAbilityData;
class UIBBAbilityTask;

USTRUCT(BlueprintType)

struct FBBConsumerCategory
{
	GENERATED_BODY()

	public:
		UPROPERTY()
		TArray<UIBBWorkComponent*> Available;

		UPROPERTY()
		TArray<UIBBWorkComponent*> Busy;

		FBBConsumerCategory()
		{
			Available.Empty();
			Busy.Empty();
		}

		~FBBConsumerCategory()
		{
			Available.Empty();
			Busy.Empty();
		}
};

USTRUCT(BlueprintType)

struct FBBTaskCategory
{
	GENERATED_BODY()

	public:
		UPROPERTY()
		TArray<UIBBAbilityTask*> Unassigned;

		UPROPERTY()
		TArray<UIBBAbilityTask*> Assigned;

		FBBTaskCategory()
		{
			Unassigned.Empty();
			Assigned.Empty();
		}

		~FBBTaskCategory()
		{
			Unassigned.Empty();
			Assigned.Empty();
		}
};

UCLASS(Blueprintable)

class ABBGameStateStub : public AIBBGameState
{
	GENERATED_BODY()

	public:
		ABBGameStateStub();

		virtual void BeginPlay() override;

		virtual void Initialize(AIBBLevelScriptActor* LevelScriptActor) override;

		virtual void Finalize(AIBBLevelScriptActor* LevelScriptActor) override;

		virtual void Tick(float DeltaTime);

		virtual UIBBGameClock * GetGameClock() const override;

		void SetGameClock(UIBBGameClock* NewGameClock);

		virtual void AddConsumer(UIBBWorkComponent* Consumer, EBBJob Job) override;

		virtual void RemoveConsumer(UIBBWorkComponent* Consumer, EBBJob Job) override;

		virtual void AddProducer(UIBBPlayerAbilityComponent* PlayerAbilityComponent) override;

		virtual void RemoveProducer(UIBBPlayerAbilityComponent* PlayerAbilityComponent) override;

		virtual TArray<UIBBWorkComponent*> GetConsumers(EBBJob Work);

		EBBGameMode GetActiveMode();

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

		virtual void HandleFloorChangeRequest(const int TargetFloorDelta, float& TargetFloorHeight) override;

		int GetRequestedTargetFloorDelta();

		float GetRequestedTargetFloorHeight();

	protected:
		UPROPERTY()
		UIBBGameClock* GameClock;

		UPROPERTY()
		TMap<EBBJob, FBBConsumerCategory> ConsumersMap;

		UPROPERTY()
		TMap<EBBJob, FBBTaskCategory> TasksMap;

		UPROPERTY()
		TArray<UIBBPlayerAbilityComponent*> Producers;

		EBBGameMode ActiveGameMode;

		int FloorDelta;

		float FloorHeight;

		UFUNCTION()
		void QueueWork(const UIBBAbilityData * AbilityData);
};