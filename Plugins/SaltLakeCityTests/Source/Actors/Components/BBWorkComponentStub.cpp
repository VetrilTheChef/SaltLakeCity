// SaltLakeCity 4.27

#include "BBWorkComponentStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Interfaces/IBBWorkable.h"

UBBWorkComponentStub::UBBWorkComponentStub() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;

	Workable = TScriptInterface<IBBWorkable>(nullptr);
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
	AbilityComponent = nullptr;
	Task = nullptr;
	Job = EBBJob::None;

	JobEfficiency = 1.0f;
	Working = false;
}

void UBBWorkComponentStub::BeginPlay()
{
	Super::BeginPlay();
}

void UBBWorkComponentStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBWorkComponentStub::Initialize(TScriptInterface<IBBWorkable> && NewWorkable, UIBBAIAbilityComponent * NewAbilityComponent, EBBJob NewJob)
{
	Workable = NewWorkable;
	AbilityComponent = NewAbilityComponent;
	Job = NewJob;
}

TScriptInterface<IBBWorkable> UBBWorkComponentStub::GetWorkable() const
{
	return Workable;
}

void UBBWorkComponentStub::SetWorkable(TScriptInterface<IBBWorkable> && NewWorkable)
{
	Workable = NewWorkable;
}

void UBBWorkComponentStub::Finalize()
{
	Workable = TScriptInterface<IBBWorkable>(nullptr);
	AbilityComponent = nullptr;
	Task = nullptr;
	Job = EBBJob::None;
}

const EBBJob UBBWorkComponentStub::GetJob() const
{
	return Job;
}

void UBBWorkComponentStub::SetJob(EBBJob NewJob)
{
	Job = NewJob;
}

float UBBWorkComponentStub::GetJobEfficiency(EBBJob ForJob) const
{
	return JobEfficiency;
}

void UBBWorkComponentStub::SetJobEfficiency(float NewJobEfficiency)
{
	JobEfficiency = NewJobEfficiency;
}


void UBBWorkComponentStub::AssignTask(UIBBAbilityTask * NewTask)
{
	Task = NewTask;
}

UIBBAbilityTask * UBBWorkComponentStub::UnassignTask()
{
	UIBBAbilityTask * OldTask = Task;
	Task = nullptr;

	return OldTask;
}

UIBBAbilityTask * UBBWorkComponentStub::GetTask() const
{
	return Task;
}

bool UBBWorkComponentStub::StartTask()
{
	return true;
}

bool UBBWorkComponentStub::StopTask()
{
	//OnTaskCanceled().Broadcast(this, Task);

	return true;
}

bool UBBWorkComponentStub::IsWorking() const
{
	return Working;
}

void UBBWorkComponentStub::SetIsWorking(bool NewWorking)
{
	Working = NewWorking;
}

UIBBAbilityTask * UBBWorkComponentStub::CompleteTask()
{
	//OnTaskCompleted().Broadcast(this, Task);

	return UnassignTask();
}

const TScriptInterface<IBBWidgetTarget> UBBWorkComponentStub::GetWidgetTarget() const
{
	return WidgetTarget;
}

void UBBWorkComponentStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}