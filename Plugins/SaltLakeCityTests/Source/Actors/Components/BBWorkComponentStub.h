// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "BBWorkComponentStub.generated.h"

UCLASS(NotBlueprintable)

class UBBWorkComponentStub : public UIBBWorkComponent
{
	GENERATED_BODY()

	public:	
		UBBWorkComponentStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBWorkable> && NewWorkable, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) override;

		virtual void Finalize() override;

		virtual TScriptInterface<IBBWorkable> GetWorkable() const;

		virtual void SetWorkable(TScriptInterface<IBBWorkable> && NewWorkable);

		virtual const EBBJob GetJob() const override;

		virtual void SetJob(EBBJob NewJob) override;

		virtual float GetJobEfficiency(EBBJob ForJob) const override;

		virtual void SetJobEfficiency(float NewJobEfficiency);

		virtual void AssignTask(UIBBAbilityTask * NewTask) override;

		virtual UIBBAbilityTask * UnassignTask() override;

		virtual UIBBAbilityTask * GetTask() const override;

		virtual bool StartTask() override;

		virtual bool StopTask() override;

		virtual bool IsWorking() const override;

		virtual void SetIsWorking(bool NewWorking);

		virtual UIBBAbilityTask * CompleteTask() override;

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget);

	protected:
		UPROPERTY()
		TScriptInterface<IBBWorkable> Workable;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		UPROPERTY()
		UIBBAIAbilityComponent * AbilityComponent;

		UPROPERTY()
		UIBBAbilityTask * Task;

		EBBJob Job;

		float JobEfficiency;

		bool Working;
};