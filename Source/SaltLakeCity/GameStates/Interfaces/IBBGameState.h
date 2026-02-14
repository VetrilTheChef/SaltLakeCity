// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "Actors/Interfaces/IBBProgressable.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "GameFramework/GameStateBase.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBGameState.generated.h"

/**
*
*/

Expose_TNameOf(AIBBGameState)

class AIBBLevelScriptActor;
class AIBBWorldLayer;
class UIBBGameClock;
class UIBBPlayerAbilityComponent;
class UIBBWorkComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBGameState : public AGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

	public:
		AIBBGameState() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void BeginDestroy() override { Super::BeginDestroy(); };

		virtual void Initialize(AIBBLevelScriptActor* LevelScriptActor)
			PURE_VIRTUAL(AIBBGameState::Initialize, );

		virtual void Finalize(AIBBLevelScriptActor* LevelScriptActor)
			PURE_VIRTUAL(AIBBGameState::Finalize, );

		virtual void Tick(float DeltaTime) override { Super::Tick(DeltaTime); };

		virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
			PURE_VIRTUAL(AIBBGameState::GetAbilitySystemComponent, return nullptr; );

		virtual int GetStartingYear() const
			PURE_VIRTUAL(AIBBGameState::GetStartingYear, return FDateTime::Now().GetYear(););

		virtual float GetTimeUnit() const
			PURE_VIRTUAL(AIBBGameState::GetTimeUnit, return 1.0f;);

		virtual UIBBGameClock* GetGameClock() const
			PURE_VIRTUAL(AIBBGameState::GetGameClock, return nullptr;);

		virtual TScriptInterface<IBBContextualizable> GetContext() const
			PURE_VIRTUAL(AIBBGameState::GetContext, return TScriptInterface<IBBContextualizable>(); );

		virtual void SetContext(TScriptInterface<IBBContextualizable>&& NewContextualizable)
			PURE_VIRTUAL(AIBBGameState::SetContext, );

		virtual TScriptInterface<IBBSelectable> GetSelection() const
			PURE_VIRTUAL(AIBBGameState::GetSelection, return TScriptInterface<IBBSelectable>(); );

		virtual void SetSelection(TScriptInterface<IBBSelectable>&& NewSelectedActor)
			PURE_VIRTUAL(AIBBGameState::SetSelection, );

		virtual const int GetGridActiveLayer() const
			PURE_VIRTUAL(AIBBGameState::GetGridActiveLayer, return -1; );

		virtual bool SetGridActiveLayer(const int NewActiveLayerIndex)
			PURE_VIRTUAL(AIBBGameState::SetGridActiveLayer, return false; );

		virtual void SetGridVisibility(bool Visible)
			PURE_VIRTUAL(AIBBGameState::SetGridVisibility, );

		virtual bool GetGridPosition(const FVector InPosition, FVector& OutPosition, bool& IsBuildable) const
			PURE_VIRTUAL(AIBBGameState::GetGridPosition, return false; );

		virtual const float GetGridHeight() const
			PURE_VIRTUAL(AIBBGameState::GetGridHeight, return 0.0f; );

		virtual void AddConsumer(UIBBWorkComponent* Consumer, EBBJob Job)
			PURE_VIRTUAL(AIBBGameState::AddConsumer, );

		virtual void RemoveConsumer(UIBBWorkComponent* Consumer, EBBJob Job)
			PURE_VIRTUAL(AIBBGameState::RemoveConsumer, );

		virtual void AddProducer(UIBBPlayerAbilityComponent* PlayerAbilityComponent)
			PURE_VIRTUAL(AIBBGameState::AddProducer, );

		virtual void RemoveProducer(UIBBPlayerAbilityComponent* PlayerAbilityComponent)
			PURE_VIRTUAL(AIBBGameState::RemoveProducer, );

		DECLARE_EVENT_OneParam(AIBBGameState, FBBConsumerChanged, TScriptInterface<IBBWorkable>);

		FBBConsumerChanged& OnConsumerChanged() { return ConsumerChange; };

		DECLARE_EVENT_OneParam(AIBBGameState, FBBContextChanged, TScriptInterface<IBBContextualizable>);

		FBBContextChanged& OnContextChanged() { return ContextChange; };

		DECLARE_EVENT_OneParam(AIBBGameState, FBBSelectionChanged, TScriptInterface<IBBSelectable>);

		FBBSelectionChanged& OnSelectionChanged() { return SelectionChange; };

		UFUNCTION()
		virtual void UpdateActiveMode(EBBGameMode NewActiveMode)
			PURE_VIRTUAL(AIBBGameState::UpdateActiveMode, );

		UFUNCTION()
		virtual void HandleFloorChangeRequest(const int TargetFloorDelta, float& TargetFloorHeight)
			PURE_VIRTUAL(AIBBGameState::HandleFloorChangeRequest, );

	private:
		FBBConsumerChanged ConsumerChange;

		FBBContextChanged ContextChange;

		FBBSelectionChanged SelectionChange;
};