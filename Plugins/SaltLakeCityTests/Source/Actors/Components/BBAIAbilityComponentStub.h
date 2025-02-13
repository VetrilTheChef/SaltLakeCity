// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "BBAIAbilityComponentStub.generated.h"

class UIBBAbilityTask;
class UIBBBaseAttributeSet;

UCLASS(NotBlueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class UBBAIAbilityComponentStub : public UIBBAIAbilityComponent
{
	GENERATED_BODY()

	public:	
		UBBAIAbilityComponentStub();

		virtual void Initialize(AIBBAIController * NewController, const TArray<FBBAttributeSetData> & SetsData) override;

		virtual void Finalize() override;

		virtual void SetAIController(AIBBAIController * NewAIController) override;

		virtual const TArray<FBBAttributeSetData> GetAttributeSetsData() const override;

		void SetAttributeSetsData(TArray<FBBAttributeSetData> NewAttributeSetsData);

		void AddAttributeSet(UIBBBaseAttributeSet * Set);

		void RemoveAttributeSet(UIBBBaseAttributeSet * Set);

		virtual bool StartTask(UIBBAbilityTask * AbilityTask) override;

		virtual bool StopTask(UIBBAbilityTask * AbilityTask) override;

		virtual bool IsRunningTask() const;

		void SetIsRunningTask(bool NewRunningTask);

		UIBBAbilityTask * GetCurrentTask() const;

		virtual void RunBehaviorTree(UBehaviorTree * NewBehaviorTree, FName TreeTaskName, UIBBAbilityTask * TreeTask) override;

		FName GetTaskName();

		UIBBAbilityTask * GetTask();

		UBehaviorTree * GetBehaviorTree();

	protected:
		UPROPERTY()
		AIBBAIController * Controller;

		UPROPERTY()
		TArray<FBBAttributeSetData> AttributeSetsData;

		UPROPERTY()
		UIBBAbilityTask * Task;

		UPROPERTY()
		UBehaviorTree * BehaviorTree;

		UPROPERTY()
		UIBBAbilityTask * BehaviorTreeTask;

		FName BehaviorTreeTaskName;

		bool RunningTask;
};