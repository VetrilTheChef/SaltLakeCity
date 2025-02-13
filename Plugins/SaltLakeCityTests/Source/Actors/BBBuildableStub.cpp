// SaltLakeCity 4.27

#include "BBBuildableStub.h"

UBBBuildableStub::UBBBuildableStub() :
	Super()
{
	MaterialOverride = nullptr;
	BuildableActor = nullptr;
	Price = -1.0f;
	BuildTime = -1.0f;
	IsBuilding = false;
}

float UBBBuildableStub::GetPrice() const
{
	return Price;
}

void UBBBuildableStub::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float UBBBuildableStub::GetBuildTime() const
{
	return BuildTime;
}

void UBBBuildableStub::SetBuildTime(float NewBuildTime)
{
	BuildTime = NewBuildTime;
}

void UBBBuildableStub::AddMaterialOverride(UMaterialInterface * NewMaterialOverride)
{
	MaterialOverride = NewMaterialOverride;
}

void UBBBuildableStub::RemoveMaterialOverride()
{
	MaterialOverride = nullptr;
}

void UBBBuildableStub::StartBuilding()
{
	IsBuilding = true;
}

void UBBBuildableStub::StopBuilding()
{
	IsBuilding = false;
}

AActor * UBBBuildableStub::ToActor()
{
	return BuildableActor;
}

void UBBBuildableStub::SetActor(AActor * NewBuildableActor)
{
	BuildableActor = NewBuildableActor;
}
