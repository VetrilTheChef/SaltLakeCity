// SaltLakeCity 4.26

#include "BBPlayerControllerStub.h"
#include "Actors/Components/BBPlayerAbilityComponent.h"

ABBPlayerControllerStub::ABBPlayerControllerStub() :
	Super()
{
	PlayerAbilityComponent = nullptr;
	RequestedAbilityData = nullptr;
	PawnHeight = 0.0f;
	ActiveGameMode = EBBGameMode::None;
}

void ABBPlayerControllerStub::BeginPlay()
{
	Super::BeginPlay();
}

void ABBPlayerControllerStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBPlayerControllerStub::SetupInputComponent()
{
	Super::SetupInputComponent();
}

UAbilitySystemComponent * ABBPlayerControllerStub::GetAbilitySystemComponent() const
{
	return PlayerAbilityComponent;
}

void ABBPlayerControllerStub::SetAbilitySystemComponent(UIBBPlayerAbilityComponent * NewPlayerAbilityComponent)
{
	PlayerAbilityComponent = NewPlayerAbilityComponent;
}

float ABBPlayerControllerStub::GetLerpHeight()
{
	return PawnHeight;
}

void ABBPlayerControllerStub::LerpToHeight(const float TargetHeight)
{
	PawnHeight = TargetHeight;
}

UIBBAbilityData * ABBPlayerControllerStub::GetRequestedAbilityData()
{
	return RequestedAbilityData;
}

void ABBPlayerControllerStub::RequestAbility(UIBBAbilityData * NewAbilityData)
{
	RequestedAbilityData = NewAbilityData;
}

void ABBPlayerControllerStub::ConfirmTarget()
{
}

void ABBPlayerControllerStub::CancelTarget()
{
}

EBBGameMode ABBPlayerControllerStub::GetActiveMode()
{
	return ActiveGameMode;
}

void ABBPlayerControllerStub::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	ActiveGameMode = NewActiveMode;
}

void ABBPlayerControllerStub::BroadcastFloorChangeRequest(int TargetFloorDelta, float TargetFloorHeight)
{
	OnFloorChangeRequested().Broadcast(TargetFloorDelta, TargetFloorHeight);
}
