// SaltLakeCity 4.26

#include "BBTargetingActorStub.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Engine/World.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "Materials/BBMaterialInterfaceStub.h"

ABBTargetingActorStub::ABBTargetingActorStub() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(false);
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Actors.Empty();

	PreviewMaterial = nullptr;

	Buildable = true;
}

void ABBTargetingActorStub::PostInitProperties()
{
	Super::PostInitProperties();

	PreviewMaterial = NewObject<UBBMaterialInterfaceStub>(this, UBBMaterialInterfaceStub::StaticClass());
}

void ABBTargetingActorStub::StartTargeting(UGameplayAbility * Ability)
{
	Super::StartTargeting(Ability);
}

void ABBTargetingActorStub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABBTargetingActorStub::SetBuildable(bool NewBuildable)
{
	Buildable = NewBuildable;
}

void ABBTargetingActorStub::ConfirmTargetingAndContinue()
{
	ConfirmTargeting();
}

void ABBTargetingActorStub::ConfirmTargeting()
{
	if (Buildable)
	{
		DetachAllActors();

		const FGameplayAbilityActorInfo * ActorInfo = (OwningAbility ? OwningAbility->GetCurrentActorInfo() : nullptr);
		UAbilitySystemComponent * AbilitySystemComponent = (ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr);

		verifyf(IsValid(AbilitySystemComponent), TEXT("Ability System Component is invalid."));

		AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::GenericConfirm, OwningAbility->GetCurrentAbilitySpecHandle(), OwningAbility->GetCurrentActivationInfo().GetActivationPredictionKey()).Remove(GenericConfirmHandle);

		FHitResult HitResult = FHitResult();
		HitResult.Location = GetActorLocation();

		FGameplayAbilityTargetingLocationInfo Data = FGameplayAbilityTargetingLocationInfo();

		TargetDataReadyDelegate.Broadcast(Data.MakeTargetDataHandleFromHitResult(TWeakObjectPtr<UGameplayAbility>(OwningAbility), HitResult));
	}
}

void ABBTargetingActorStub::CancelTargeting()
{
	DetachAllActors();

	const FGameplayAbilityActorInfo * ActorInfo = (OwningAbility ? OwningAbility->GetCurrentActorInfo() : nullptr);
	UAbilitySystemComponent * AbilitySystemComponent = (ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr);

	verifyf(IsValid(AbilitySystemComponent), TEXT("Ability System Component is invalid."));
	
	AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::GenericCancel, OwningAbility->GetCurrentAbilitySpecHandle(), OwningAbility->GetCurrentActivationInfo().GetActivationPredictionKey()).Remove(GenericCancelHandle);

	FHitResult HitResult = FHitResult();
	HitResult.Location = GetActorLocation();

	FGameplayAbilityTargetingLocationInfo Data = FGameplayAbilityTargetingLocationInfo();

	CanceledDelegate.Broadcast(Data.MakeTargetDataHandleFromHitResult(TWeakObjectPtr<UGameplayAbility>(OwningAbility), HitResult));
}

UMaterialInterface * ABBTargetingActorStub::GetPreviewMaterial() const
{
	return PreviewMaterial;
}

void ABBTargetingActorStub::AttachActor(AActor * NewActor)
{
	Actors.Emplace(NewActor);
}

int ABBTargetingActorStub::GetAttachedActorsNum()
{
	return Actors.Num();
}

void ABBTargetingActorStub::DetachAllActors()
{
	Actors.Empty();
}