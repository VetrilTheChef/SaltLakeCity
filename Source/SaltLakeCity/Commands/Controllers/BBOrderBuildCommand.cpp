// SaltLakeCity 4.26

#include "BBOrderBuildCommand.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "Controllers/Interfaces/IBBPlayerController.h"

UBBOrderBuildCommand::UBBOrderBuildCommand() :
	Super()
{
	Controller = nullptr;
	Outer = nullptr;
	BuildDataClass = TSoftClassPtr<UIBBBuildData>();
	TargetingClass = TSoftClassPtr<AIBBTargetingActor>();
	BuildableClasses = TArray<FBBBuildablePtr>();
	Price = -1.0f;
	Time = -1.0f;
}

void UBBOrderBuildCommand::SetController(AIBBPlayerController * NewController)
{
	verifyf(IsValid(NewController), TEXT("New Controller is invalid."));

	Controller = NewController;
}

void UBBOrderBuildCommand::SetOuter(UObject * NewOuter)
{
	Outer = NewOuter;
}

void UBBOrderBuildCommand::SetBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass)
{
	BuildDataClass = NewBuildDataClass;
}

const TSoftClassPtr<AIBBTargetingActor> UBBOrderBuildCommand::GetTargetingClass() const
{
	return TargetingClass;
}

void UBBOrderBuildCommand::SetTargetingClass(const TSoftClassPtr<AIBBTargetingActor> NewTargetingClass)
{
	TargetingClass = NewTargetingClass;
}

const TArray<FBBBuildablePtr> UBBOrderBuildCommand::GetBuildableClasses() const
{
	return BuildableClasses;
}

void UBBOrderBuildCommand::SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses)
{
	BuildableClasses = NewBuildableClasses;
}

void UBBOrderBuildCommand::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

void UBBOrderBuildCommand::SetTime(float NewTime)
{
	Time = NewTime;
}

void UBBOrderBuildCommand::Execute()
{
	verifyf(IsValid(Outer), TEXT("Outer is invalid."));
	verifyf(!BuildDataClass.IsNull(), TEXT("Build Data class is null."));

	UIBBBuildData * BuildData = NewObject<UIBBBuildData>(Outer, BuildDataClass.LoadSynchronous());

	verifyf(IsValid(BuildData), TEXT("Build Data is invalid."));

	BuildData->SetPrice(Price);
	BuildData->SetTime(Time);
	BuildData->SetBuildableClasses(BuildableClasses);

	verifyf(IsValid(Controller), TEXT("Controller is invalid."));

	Controller->RequestAbility(BuildData);
}