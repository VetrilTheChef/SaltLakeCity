// SaltLakeCity 4.26

#include "BBPlayerController.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"
#include "Actors/Components/BBPlayerAbilityComponent.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "Actors/Pawns/Interfaces/IBBPawn.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameInstances/BBGameInstance.h"
#include "GameStates/BBGameState.h"

ABBPlayerController::ABBPlayerController() :
	Super()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	ClickEventKeys.Add(EKeys::RightMouseButton);

	ModeInputComponents.Empty();
	PlayerAbilityComponent = nullptr;
	ControllerPawn = nullptr;

	MovementEnabled = false;

	UInputComponent * BuildModeInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("BuildModeInputComponent"));

	verifyf(IsValid(BuildModeInputComponent), TEXT("Build Mode Input Component is invalid."));

	BuildModeInputComponent->bBlockInput = false;

	ModeInputComponents.Emplace(EBBGameMode::Build, BuildModeInputComponent);
}

void ABBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControllerPawn = GetPawn<AIBBPawn>();
	
	MovementEnabled = true;

	GridTrace = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel3);
	BuildableTrace = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel5);

	CreateAbilityComponent();
}

void ABBPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyAbilityComponent();

	MovementEnabled = false;

	Super::EndPlay(EndPlayReason);
}

void ABBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputModeGameAndUI InputModeData = FInputModeGameAndUI();
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	SetInputMode(InputModeData);

	InputComponent->BindAxis("MoveForward", this, &ABBPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABBPlayerController::MoveRight);
	InputComponent->BindAxis("Pan", this, &ABBPlayerController::Pan);
	InputComponent->BindAxis("Zoom", this, &ABBPlayerController::Zoom);
	InputComponent->BindAction("RMB", IE_Pressed, this, &ABBPlayerController::DisableMovement);
	InputComponent->BindAction("RMB", IE_Released, this, &ABBPlayerController::EnableMovement);
	InputComponent->BindAction("PgUp", IE_Pressed, this, &ABBPlayerController::MoveUp);
	InputComponent->BindAction("PgDn", IE_Pressed, this, &ABBPlayerController::MoveDown);

	UInputComponent * BuildModeInputComponent = ModeInputComponents.FindChecked(EBBGameMode::Build);
		
	BuildModeInputComponent->BindAction("LMB", IE_Pressed, this, &ABBPlayerController::ConfirmTarget);
	BuildModeInputComponent->BindAction("RMB", IE_Pressed, this, &ABBPlayerController::CancelTarget);
}

UAbilitySystemComponent * ABBPlayerController::GetAbilitySystemComponent() const
{
	return PlayerAbilityComponent;
}

void ABBPlayerController::LerpToHeight(const float TargetHeight)
{
	verifyf(IsValid(ControllerPawn), TEXT("Controller Pawn is invalid."));

	DisableMovement();

	FVector TargetLocation = ControllerPawn->GetActorLocation();
	TargetLocation.Z = TargetHeight;

	ControllerPawn->Lerp(TargetLocation, 1.0f);

	EnableMovement();
}

void ABBPlayerController::RequestAbility(UIBBAbilityData * NewAbilityData)
{
	verifyf(IsValid(PlayerAbilityComponent), TEXT("Player Ability Component is invalid."));

	PlayerAbilityComponent->RequestAbility(NewAbilityData);
}

bool ABBPlayerController::GetCursorGridPosition(FVector & OutPosition) const
{
	FHitResult Hit;

	// Check Buildable Trace
	GetHitResultUnderCursorByChannel(BuildableTrace, true, Hit);

	if (!Hit.bBlockingHit)
	{
		// Check Grid Trace
		GetHitResultUnderCursorByChannel(GridTrace, true, Hit);
	}

	OutPosition = Hit.ImpactPoint;

	return (Hit.bBlockingHit);
}

void ABBPlayerController::ConfirmTarget()
{
	verifyf(IsValid(PlayerAbilityComponent), TEXT("Player Ability Component is invalid."));

	PlayerAbilityComponent->TargetConfirm();
}

void ABBPlayerController::CancelTarget()
{
	verifyf(IsValid(PlayerAbilityComponent), TEXT("Player Ability Component is invalid."));

	PlayerAbilityComponent->TargetCancel();
}

void ABBPlayerController::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	UInputComponent * ModeInputComponent = ModeInputComponents.Contains(NewActiveMode) ? ModeInputComponents.FindChecked(NewActiveMode) : nullptr;

	ClearInputComponents();

	if (IsValid(ModeInputComponent))
	{
		PushInputComponent(ModeInputComponent);
	}
}



void ABBPlayerController::CreateAbilityComponent()
{
	UIBBGameInstance * GameInstance = GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	const UIBBComponentFactory * ComponentFactory = GameInstance->GetComponentFactory();

	verifyf(IsValid(ComponentFactory), TEXT("Component Factory is invalid."));

	if (ComponentFactory->NewPlayerAbilityComponent(PlayerAbilityComponent, this))
	{
		UWorld * World = GetWorld();

		verifyf(IsValid(World), TEXT("World is invalid."));

		AIBBGameState * GameState = World->GetGameState<AIBBGameState>();

		verifyf(IsValid(GameState), TEXT("Game State is invalid."));

		GameState->AddProducer(PlayerAbilityComponent);
	}
}

void ABBPlayerController::DestroyAbilityComponent()
{
	if (IsValid(PlayerAbilityComponent))
	{
		UWorld * World = GetWorld();

		verifyf(IsValid(World), TEXT("World is invalid."));

		AIBBGameState * GameState = World->GetGameState<AIBBGameState>();

		verifyf(IsValid(GameState), TEXT("Game State is invalid."));

		GameState->RemoveProducer(PlayerAbilityComponent);

		PlayerAbilityComponent->DestroyComponent();
	}

	PlayerAbilityComponent = nullptr;
}

void ABBPlayerController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	ControllerPawn = Cast<AIBBPawn>(InPawn);

	if (IsValid(PlayerAbilityComponent))
	{
		PlayerAbilityComponent->RefreshAbilityActorInfo();
	}
}

void ABBPlayerController::ClearInputComponents()
{
	TArray<TWeakObjectPtr<UInputComponent>> InputStack = CurrentInputStack;

	for (TWeakObjectPtr<UInputComponent> StackedInputComponent : InputStack)
	{
		PopInputComponent(StackedInputComponent.Get());
	}
}

void ABBPlayerController::DisableMovement()
{
	MovementEnabled = false;
}

void ABBPlayerController::EnableMovement()
{
	MovementEnabled = true;
}

void ABBPlayerController::MoveForward(float AxisValue)
{
	if (MovementEnabled)
	{
		verifyf(IsValid(ControllerPawn), TEXT("Controller Pawn is invalid."));

		ControllerPawn->Move(ControllerPawn->GetActorForwardVector(), FMath::Clamp<float>(AxisValue, -1.0, 1.0));
	}
}

void ABBPlayerController::MoveRight(float AxisValue)
{
	if (MovementEnabled)
	{
		verifyf(IsValid(ControllerPawn), TEXT("Controller Pawn is invalid."));

		ControllerPawn->Move(ControllerPawn->GetActorRightVector(), FMath::Clamp<float>(AxisValue, -1.0, 1.0));
	}
}

void ABBPlayerController::MoveUp()
{
	if (MovementEnabled)
	{
		verifyf(IsValid(ControllerPawn), TEXT("Controller Pawn is invalid."));

		int TargetFloorDelta = 1;
		float TargetFloorHeight = ControllerPawn->GetActorLocation().Z;

		OnFloorChangeRequested().Broadcast(TargetFloorDelta, TargetFloorHeight);

		LerpToHeight(TargetFloorHeight);
	}
}

void ABBPlayerController::MoveDown()
{
	if (MovementEnabled)
	{
		verifyf(IsValid(ControllerPawn), TEXT("Controller Pawn is invalid."));

		int TargetFloorDelta = -1;
		float TargetFloorHeight = ControllerPawn->GetActorLocation().Z;

		OnFloorChangeRequested().Broadcast(TargetFloorDelta, TargetFloorHeight);

		LerpToHeight(TargetFloorHeight);
	}
}

void ABBPlayerController::Zoom(float AxisValue)
{
	verifyf(IsValid(ControllerPawn), TEXT("Controller Pawn is invalid."));

	ControllerPawn->Zoom(AxisValue);
}

void ABBPlayerController::Pan(float AxisValue)
{
	if (!MovementEnabled)
	{
		verifyf(IsValid(ControllerPawn), TEXT("Controller Pawn is invalid."));

		ControllerPawn->Turn(FMath::Clamp<float>(AxisValue, -1.0, 1.0));
	}
}
