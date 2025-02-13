// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBAttributeEnum.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "IBBAIAbilityComponent.generated.h"

class UDataTable;
class UIBBAttributeSet;

USTRUCT(BlueprintType)

struct FBBAttributeSetData
{
	GENERATED_BODY()

	public:
		UPROPERTY(Category = "Attribute Set", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UIBBAttributeSet> Class;

		UPROPERTY(Category = "Attribute Set", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> DataTable;

		FBBAttributeSetData() :
			Class(TSoftClassPtr<UIBBAttributeSet>()),
			DataTable(TSoftObjectPtr<UDataTable>())
		{
		}

		FBBAttributeSetData(TSoftClassPtr<UIBBAttributeSet> NewClass, TSoftObjectPtr<UDataTable> NewDataTable) :
				Class(NewClass),
				DataTable(NewDataTable)
		{
		}

		~FBBAttributeSetData()
		{
		}
};

class AIBBAIController;
class UBehaviorTree;
class UIBBAbilityTask;

UCLASS(Abstract, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UIBBAIAbilityComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	public:	
		UIBBAIAbilityComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(AIBBAIController * NewAIController, const TArray<FBBAttributeSetData> & SetsData) PURE_VIRTUAL(UIBBAIAbilityComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBAIAbilityComponent::Finalize, );

		virtual void SetAIController(AIBBAIController * NewAIController) PURE_VIRTUAL(UIBBAIAbilityComponent::SetAIController, );

		virtual const TArray<FBBAttributeSetData> GetAttributeSetsData() const PURE_VIRTUAL(UIBBAIAbilityComponent::GetAttributeSetsData, return TArray<FBBAttributeSetData>(); );

		virtual float GetAttribute(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBAIAbilityComponent::GetAttribute, return -1.0f; );

		virtual void SetAttribute(EBBAttribute Attribute, float NewValue) const PURE_VIRTUAL(UIBBAIAbilityComponent::SetAttribute, );

		virtual float GetNeed(EBBNeed Need) const PURE_VIRTUAL(UIBBAIAbilityComponent::GetNeed, return -1.0f; );

		virtual void SetNeed(EBBNeed Need, float NewValue) PURE_VIRTUAL(UIBBAIAbilityComponent::SetNeed, );

		virtual float GetSkill(EBBSkill Skill) const PURE_VIRTUAL(UIBBAIAbilityComponent::GetSkill, return -1.0f; );

		virtual void SetSkill(EBBSkill Skill, float NewValue) PURE_VIRTUAL(UIBBAIAbilityComponent::SetSkill, );

		virtual bool StartTask(UIBBAbilityTask * AbilityTask) PURE_VIRTUAL(UIBBAIAbilityComponent::StartTask, return false; );

		virtual bool StopTask(UIBBAbilityTask * AbilityTask) PURE_VIRTUAL(UIBBAIAbilityComponent::StopTask, return false; );

		virtual bool IsRunningTask() const PURE_VIRTUAL(UIBBAIAbilityComponent::IsRunningTask, return false; );

		virtual void RunBehaviorTree(UBehaviorTree * NewBehaviorTree, FName TreeTaskName, UIBBAbilityTask * TreeTask) PURE_VIRTUAL(UIBBAIAbilityComponent::RunBehaviorTree, );
		
		DECLARE_EVENT_TwoParams(UIBBAIAbilityComponent, FCancelTask, UIBBAIAbilityComponent *, const UIBBAbilityTask *);

		virtual FCancelTask & OnTaskCanceled() { return TaskCanceled; };

		DECLARE_EVENT_TwoParams(UIBBAIAbilityComponent, FCompleteTask, UIBBAIAbilityComponent *, const UIBBAbilityTask *);

		virtual FCompleteTask & OnTaskCompleted() { return TaskCompleted; };

	protected:
		FCancelTask TaskCanceled;

		FCompleteTask TaskCompleted;
};