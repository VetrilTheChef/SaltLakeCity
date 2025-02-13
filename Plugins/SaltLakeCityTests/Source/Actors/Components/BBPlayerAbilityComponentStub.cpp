// SaltLakeCity 4.25

#include "BBPlayerAbilityComponentStub.h"

UBBPlayerAbilityComponentStub::UBBPlayerAbilityComponentStub() :
	Super()
{
	RequestedAbilityData = nullptr;

	TargetConfirmCalls = 0;
	TargetCancelCalls = 0;
}

void UBBPlayerAbilityComponentStub::BeginPlay()
{
	Super::BeginPlay();
}

void UBBPlayerAbilityComponentStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

TArray<TSubclassOf<UIBBPlayerAbility>> UBBPlayerAbilityComponentStub::GetAbilityClasses()
{
	return TArray<TSubclassOf<UIBBPlayerAbility>>();
}

void UBBPlayerAbilityComponentStub::AddAbility(TSubclassOf<UIBBPlayerAbility> NewPlayerAbilityClass)
{
}

void UBBPlayerAbilityComponentStub::ClearAbilities()
{
}

bool UBBPlayerAbilityComponentStub::RequestAbility(UIBBAbilityData * AbilityData)
{	
	RequestedAbilityData = AbilityData;

	return true;
}

void UBBPlayerAbilityComponentStub::TargetConfirm()
{
	TargetConfirmCalls++;

	Super::TargetConfirm();
}

int UBBPlayerAbilityComponentStub::GetNumTargetConfirmations()
{
	return TargetConfirmCalls;
}

void UBBPlayerAbilityComponentStub::TargetCancel()
{
	TargetCancelCalls++;

	Super::TargetCancel();
}

int UBBPlayerAbilityComponentStub::GetNumTargetCancellations()
{
	return TargetCancelCalls;
}

UIBBAbilityData * UBBPlayerAbilityComponentStub::GetRequestedAbilityData()
{
	return RequestedAbilityData;
}
