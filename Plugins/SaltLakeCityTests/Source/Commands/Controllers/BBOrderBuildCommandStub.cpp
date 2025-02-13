// SaltLakeCity 4.27

#include "BBOrderBuildCommandStub.h"

UBBOrderBuildCommandStub::UBBOrderBuildCommandStub() :
	Super()
{
	Controller = nullptr;
	Outer = nullptr;
	BuildDataClass = TSoftClassPtr<UIBBBuildData>();
	TargetingClass = TSoftClassPtr<AIBBTargetingActor>();
	BuildableClasses = TArray<FBBBuildablePtr>();
	Price = -1.0f;
	Time = -1.0f;

	Executions = 0;
}

AIBBPlayerController * UBBOrderBuildCommandStub::GetController()
{
	return Controller;
}

void UBBOrderBuildCommandStub::SetController(AIBBPlayerController * NewController)
{
	Controller = NewController;
}

UObject * UBBOrderBuildCommandStub::GetOuter()
{
	return Outer;
}

void UBBOrderBuildCommandStub::SetOuter(UObject * NewOuter)
{
	Outer = NewOuter;
}

TSoftClassPtr<UIBBBuildData> UBBOrderBuildCommandStub::GetBuildDataClass()
{
	return BuildDataClass;
}

void UBBOrderBuildCommandStub::SetBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass)
{
	BuildDataClass = NewBuildDataClass;
}

const TSoftClassPtr<AIBBTargetingActor> UBBOrderBuildCommandStub::GetTargetingClass() const
{
	return TargetingClass;
}

void UBBOrderBuildCommandStub::SetTargetingClass(const TSoftClassPtr<AIBBTargetingActor> NewTargetingClass)
{
	TargetingClass = NewTargetingClass;
}

const TArray<FBBBuildablePtr> UBBOrderBuildCommandStub::GetBuildableClasses() const
{
	return BuildableClasses;
}

void UBBOrderBuildCommandStub::SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses)
{
	BuildableClasses = NewBuildableClasses;
}

float UBBOrderBuildCommandStub::GetPrice()
{
	return Price;
}

void UBBOrderBuildCommandStub::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float UBBOrderBuildCommandStub::GetTime()
{
	return Time;
}

void UBBOrderBuildCommandStub::SetTime(float NewTime)
{
	Time = NewTime;
}

void UBBOrderBuildCommandStub::Execute()
{
	Executions++;
}

int UBBOrderBuildCommandStub::GetNumExecutions() const
{
	return Executions;
}
