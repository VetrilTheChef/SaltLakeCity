// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWidgetTargetComponent.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBWorkComponent.generated.h"

class IBBWorkable;
class UIBBAbilityTask;
class UIBBAIAbilityComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBWorkComponent : public UActorComponent, public IBBWidgetTargetComponent
{
	GENERATED_BODY()

	public:	
		UIBBWorkComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(TScriptInterface<IBBWorkable> && NewWorkable, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob) PURE_VIRTUAL(UIBBWorkComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBWorkComponent::Finalize, );

		virtual const EBBJob GetJob() const PURE_VIRTUAL(UIBBWorkComponent::GetJob, return EBBJob::None; );

		virtual void SetJob(EBBJob NewJob) PURE_VIRTUAL(UIBBWorkComponent::SetJob, );

		virtual float GetJobEfficiency(EBBJob ForJob) const PURE_VIRTUAL(UIBBWorkComponent::GetJobEfficiency, return -1.0f; );

		virtual void AssignTask(UIBBAbilityTask * NewTask) PURE_VIRTUAL(UIBBWorkComponent::AssignTask, );

		virtual UIBBAbilityTask * UnassignTask() PURE_VIRTUAL(UIBBWorkComponent::UnassignTask, return nullptr; );

		virtual UIBBAbilityTask * GetTask() const PURE_VIRTUAL(UIBBWorkComponent::GetTask, return nullptr; );

		virtual bool StartTask() PURE_VIRTUAL(UIBBWorkComponent::StartTask, return false; );

		virtual bool StopTask() PURE_VIRTUAL(UIBBWorkComponent::StopTask, return false; );

		virtual bool IsWorking() const PURE_VIRTUAL(UIBBWorkComponent::IsWorking, return false; );

		virtual UIBBAbilityTask * CompleteTask() PURE_VIRTUAL(UIBBWorkComponent::CompleteTask, return nullptr; );

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override PURE_VIRTUAL(UIBBWorkComponent::GetWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );
		
		DECLARE_DERIVED_EVENT(UIBBWorkComponent, IBBWidgetTargetComponent::FBBWidgetTargetUpdate, FBBWidgetTargetUpdate);

		virtual FBBWidgetTargetUpdate & OnWidgetTargetUpdate() final override { return WidgetTargetUpdate; };

	protected:
		FBBWidgetTargetUpdate WidgetTargetUpdate;
};