// SaltLakeCity 4.26

#include "BBTargetingActor.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "Engine/World.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

ABBTargetingActor::ABBTargetingActor() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(false);
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Actors.Empty();

	Buildable = false;
}

void ABBTargetingActor::StartTargeting(UGameplayAbility * Ability)
{
	Super::StartTargeting(Ability);

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	PreviewMaterial = PreviewMaterialAsset.LoadSynchronous();
	PreviewMaterialParameters = World->GetParameterCollectionInstance(PreviewMaterialParametersAsset.LoadSynchronous());

	SubscribeToGameMode();
}

void ABBTargetingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	AIBBPlayerController * PlayerController = World->GetFirstPlayerController<AIBBPlayerController>();

	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));

	FVector CursorPosition;
	bool IsBuildable = false;

	if (PlayerController->GetCursorGridPosition(CursorPosition))
	{
		AIBBGameState * GameState = World->GetGameState<AIBBGameState>();

		verifyf(IsValid(GameState), TEXT("Game State is invalid."));

		FVector GridPosition;

		if (GameState->GetGridPosition(CursorPosition, GridPosition, IsBuildable))
		{
			SetActorLocation(GridPosition);
		}
	}

	UpdateMaterialOverride(IsBuildable);
}

void ABBTargetingActor::ConfirmTargetingAndContinue()
{
	ConfirmTargeting();
}

void ABBTargetingActor::ConfirmTargeting()
{
	if (Buildable)
	{
		UnsubscribeFromGameMode();

		DetachAllActors();

		const FGameplayAbilityActorInfo * ActorInfo = (OwningAbility ? OwningAbility->GetCurrentActorInfo() : nullptr);
		UAbilitySystemComponent * AbilitySystemComponent = (ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr);

		verifyf(IsValid(AbilitySystemComponent), TEXT("Ability System Component is invalid."));

		AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::GenericConfirm, OwningAbility->GetCurrentAbilitySpecHandle(), OwningAbility->GetCurrentActivationInfo().GetActivationPredictionKey()).Remove(GenericConfirmHandle);

		FHitResult HitResult = FHitResult();
		HitResult.Location = GetActorLocation();

		FGameplayAbilityTargetingLocationInfo Data = FGameplayAbilityTargetingLocationInfo();

		TargetDataReadyDelegate.Broadcast(Data.MakeTargetDataHandleFromHitResult(TWeakObjectPtr<UGameplayAbility>(OwningAbility), HitResult));

		if (bDestroyOnConfirmation) Destroy();
	}
}

void ABBTargetingActor::CancelTargeting()
{
	UnsubscribeFromGameMode();

	DetachAllActors();

	const FGameplayAbilityActorInfo * ActorInfo = (OwningAbility ? OwningAbility->GetCurrentActorInfo() : nullptr);
	UAbilitySystemComponent * AbilitySystemComponent = (ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr);

	verifyf(IsValid(AbilitySystemComponent), TEXT("Ability System Component is invalid."));
	
	AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::GenericCancel, OwningAbility->GetCurrentAbilitySpecHandle(), OwningAbility->GetCurrentActivationInfo().GetActivationPredictionKey()).Remove(GenericCancelHandle);

	FHitResult HitResult = FHitResult();
	HitResult.Location = GetActorLocation();

	FGameplayAbilityTargetingLocationInfo Data = FGameplayAbilityTargetingLocationInfo();

	CanceledDelegate.Broadcast(Data.MakeTargetDataHandleFromHitResult(TWeakObjectPtr<UGameplayAbility>(OwningAbility), HitResult));

	Destroy();
}

UMaterialInterface * ABBTargetingActor::GetPreviewMaterial() const
{
	return PreviewMaterial;
}

void ABBTargetingActor::AttachActor(AActor * NewActor)
{
	verifyf(IsValid(NewActor), TEXT("New Actor is invalid."));

	NewActor->AttachToActor(this, AttachRules);

	Actors.Emplace(NewActor);
}

int ABBTargetingActor::GetAttachedActorsNum()
{
	return Actors.Num();
}

void ABBTargetingActor::DetachAllActors()
{
	for (auto& Actor : Actors)
	{
		verifyf(IsValid(Actor), TEXT("Actor is invalid."));

		Actor->DetachFromActor(DetachRules);
	}

	Actors.Empty();
}

void ABBTargetingActor::SubscribeToGameMode()
{
	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	AIBBGameMode * GameMode = World->GetAuthGameMode<AIBBGameMode>();

	verifyf(IsValid(GameMode), TEXT("Game Mode is invalid."));

	GameMode->OnActiveModeUpdate().AddUObject(this, &ABBTargetingActor::UpdateActiveGameMode);
}

void ABBTargetingActor::UnsubscribeFromGameMode()
{
	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	AIBBGameMode * GameMode = World->GetAuthGameMode<AIBBGameMode>();

	verifyf(IsValid(GameMode), TEXT("Game Mode is invalid."));

	GameMode->OnActiveModeUpdate().RemoveAll(this);
}

void ABBTargetingActor::UpdateMaterialOverride(bool NewBuildable)
{
	if (NewBuildable != Buildable)
	{
		Buildable = NewBuildable;

		verifyf(IsValid(PreviewMaterial), TEXT("Preview Material is invalid."));
		verifyf(IsValid(PreviewMaterialParameters), TEXT("Preview Material Parameters is invalid."));

		FLinearColor NewColor = Buildable ? FLinearColor::FromSRGBColor(EnabledColor) : FLinearColor::FromSRGBColor(DisabledColor);

		PreviewMaterialParameters->SetVectorParameterValue(ColorParameterName, NewColor);
	}
}

void ABBTargetingActor::UpdateActiveGameMode(EBBGameMode NewActiveGameMode)
{
	if (NewActiveGameMode != EBBGameMode::Build)
	{
		CancelTargeting();
	}
}