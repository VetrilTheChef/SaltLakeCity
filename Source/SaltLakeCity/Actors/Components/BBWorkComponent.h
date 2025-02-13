// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "BBWorkComponent.generated.h"

class AIBBAIController;
class UIBBAbilityTask;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBWorkComponent : public UIBBWorkComponent
{
	GENERATED_BODY()

	public:	
		UBBWorkComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBWorkable> && NewWorkable, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) override;

		virtual void Finalize() override;

		virtual const EBBJob GetJob() const override;

		virtual void SetJob(EBBJob NewJob) override;

		virtual float GetJobEfficiency(EBBJob ForJob) const override;

		virtual void AssignTask(UIBBAbilityTask * NewTask) override;

		virtual UIBBAbilityTask * UnassignTask() override;

		virtual UIBBAbilityTask * GetTask() const override;

		virtual bool StartTask() override;

		virtual bool StopTask() override;

		virtual bool IsWorking() const override;

		virtual UIBBAbilityTask * CompleteTask() override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBWorkable> Workable;
		
		UPROPERTY()
		UIBBAIAbilityComponent * AbilityComponent;

		UPROPERTY()
		UIBBAbilityTask * Task;

		EBBJob Job;

		TMap<EBBJob, EBBSkill> JobSkillsMap;
};