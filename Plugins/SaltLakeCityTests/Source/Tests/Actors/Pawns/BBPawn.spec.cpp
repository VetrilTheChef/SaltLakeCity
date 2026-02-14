// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pawns/BBPawn.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBLatentCommands.h"
#include "Tests/BBTestUtil.h"
#include "Tests/Actors/Pawns/BBPawnLatentCommands.h"

BEGIN_DEFINE_SPEC(
	UBBPawnSpec,
	"SaltLakeCity.Actors.Pawns.Pawn",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * Controller;

	UPROPERTY()
	TArray<ABBPawn *> Pawns;

	UPROPERTY()
	TArray<UClass *> PawnClasses;

	// SUT
	UPROPERTY()
	ABBPawn * Pawn = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBPawnSpec)

void UBBPawnSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBPawn>(FString(TEXT("/Game/Actors/Pawns")), PawnClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (UClass * & PawnClass : PawnClasses)
	{
		Describe("[" + PawnClass->GetName() + "]", [this, PawnClass]()
		{
			Describe("", [this, PawnClass]()
			{
				BeforeEach([this]()
				{
					TestWorld = UBBTestUtil::OpenTestWorld();

					UTEST_TRUE("Test World is valid", IsValid(TestWorld))

					GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

					UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

					return true;
				});

				AfterEach([this]()
				{
					TestWorld->DestroyActor(Pawn);

					GameInstance = nullptr;

					UBBTestUtil::CloseTestWorld(TestWorld);
				});

				It("Given a new camera distance, expect the pawn to adjust its camera", [this, PawnClass]()
				{
					Pawn = TestWorld->SpawnActor<ABBPawn>(PawnClass, SpawnParameters);

					UTEST_TRUE("Pawn is valid.", IsValid(Pawn))

					TArray<float> CameraDistances;
					CameraDistances.Empty();
					CameraDistances.Emplace(400.0f);
					CameraDistances.Emplace(725.81f);
					CameraDistances.Emplace(6250.0f);
					CameraDistances.Emplace(-641.7f);
					CameraDistances.Emplace(-0.62f);

					float MinDistance = Pawn->GetMinCameraDistance();
					float MaxDistance = Pawn->GetMaxCameraDistance();

					for (float & CameraDistance : CameraDistances)
					{
						Pawn->SetCameraDistance(CameraDistance);

						TEST_TRUE(Pawn->GetCameraDistance() == FMath::Clamp(CameraDistance, MinDistance, MaxDistance))
					}

					return true;
				});

				It("Given a new rotation, expect the pawn to adjust its directional vectors", [this, PawnClass]()
				{
					Pawn = TestWorld->SpawnActor<ABBPawn>(PawnClass, SpawnParameters);

					UTEST_TRUE("Pawn is valid.", IsValid(Pawn))

					TArray<FRotator> PawnRotations;
					PawnRotations.Empty();
					PawnRotations.Emplace(FRotator(10.85f, -25.10f, 75.0f));
					PawnRotations.Emplace(FRotator(-60.1f, 15.05f, 49.71f));
					PawnRotations.Emplace(FRotator(-116.06f, 515.03f, -52.7f));
					PawnRotations.Emplace(FRotator(712.1f, 0.0f, -211.2f));
					PawnRotations.Emplace(FRotator(47.6f, -84.163f, 0.0f));

					FVector Forward = Pawn->GetForwardVector();

					UTEST_TRUE("Pawn forward vector equals the expected value.", Forward.Equals(FRotator(-45.0f, 0.0f, 0.0f).Vector()));

					FVector Right = Pawn->GetRightVector();

					UTEST_TRUE("Pawn right vector equals the expected value.", Right.Equals(FRotator(0.0f, 90.0f, 0.0f).Vector()));

					FVector Up = Pawn->GetUpVector();

					UTEST_TRUE("Pawn up vector equals the expected value.", Up.Equals(FRotator(45.0f, 0.0f, 90.0f).Vector()));

					for (FRotator & PawnRotation : PawnRotations)
					{
						Forward = PawnRotation.RotateVector(Forward);
						Right = PawnRotation.RotateVector(Right);
						Up = PawnRotation.RotateVector(Up);

						Pawn->AddActorWorldRotation(PawnRotation.Quaternion());

						TEST_TRUE(Pawn->GetForwardVector().Equals(Forward));

						Forward = Pawn->GetForwardVector();

						TEST_TRUE(Pawn->GetRightVector().Equals(Right));

						Right = Pawn->GetRightVector();

						TEST_TRUE(Pawn->GetUpVector().Equals(Up));

						Up = Pawn->GetUpVector();
					}

					return true;
				});
			});

			Describe("", [this, PawnClass]()
			{
				LatentBeforeEach([this](const FDoneDelegate & Done)
				{
					TestWorld = UBBTestUtil::OpenTestWorld();

					UTEST_TRUE("Test World is valid.", IsValid(TestWorld))

					Pawns.Empty();

					Controller = NewObject<ABBPlayerControllerStub>(TestWorld, ABBPlayerControllerStub::StaticClass());

					UTEST_TRUE("Controller is valid.", IsValid(Controller))

					Done.Execute();

					return true;
				});

				LatentIt("Given a new movement, expect the pawn to move while staying at a constant height", [this, PawnClass](const FDoneDelegate & Done)
				{
					TArray<FVector> PawnDirections;

					PawnDirections.Emplace(FVector(168.33f, 726.04f, 263.65f));
					PawnDirections.Emplace(FVector(467.6f, 854.16f, -164.0f));
					PawnDirections.Emplace(FVector(327.27f, -426.24f, 219.92f));
					PawnDirections.Emplace(FVector(471.72f, -764.73f, -140.67f));
					PawnDirections.Emplace(FVector(-116.25f, 697.63f, 672.7f));
					PawnDirections.Emplace(FVector(-355.63f, 361.12f, -424.15f));
					PawnDirections.Emplace(FVector(-671.5f, -212.41f, 102.61f));
					PawnDirections.Emplace(FVector(-414.75f, -656.1f, -956.26f));

					TArray<float> PawnScales;

					PawnScales.Emplace(252.1f);
					PawnScales.Emplace(-167.11f);
					PawnScales.Emplace(743.18f);
					PawnScales.Emplace(-913.61f);
					PawnScales.Emplace(127.12f);
					PawnScales.Emplace(-452.74f);
					PawnScales.Emplace(863.78f);
					PawnScales.Emplace(-671.25f);

					for (int Index = 0; Index < 8; Index++)
					{
						ABBPawn * MovePawn = TestWorld->SpawnActor<ABBPawn>(PawnClass, SpawnParameters);

						UTEST_TRUE("Pawn is valid.", IsValid(MovePawn))

						MovePawn->Controller = Controller;

						ADD_LATENT_AUTOMATION_COMMAND(FBBPawnMoveTestLatentCommand(* this, TestWorld, MovePawn, PawnDirections[Index], PawnScales[Index]));
					}

					Done.Execute();

					return true;
				});

				LatentIt("Given a new lerp, expect the pawn to change its location over time", [this, PawnClass](const FDoneDelegate & Done)
				{
					TArray<FVector> PawnLocations;
					PawnLocations.Empty();
					PawnLocations.Emplace(FVector(372.26f, 742.72f, 631.24f));
					PawnLocations.Emplace(FVector(163.12f, 632.21f, -467.32f));
					PawnLocations.Emplace(FVector(734.67f, -126.12, 856.73f));
					PawnLocations.Emplace(FVector(932.56f, -437.39f, -956.25f));
					PawnLocations.Emplace(FVector(-618.49f, 823.46f, 473.45f));
					PawnLocations.Emplace(FVector(-853.62f, 458.36f, -631.54f));
					PawnLocations.Emplace(FVector(-236.54f, -874.25f, 164.27f));
					PawnLocations.Emplace(FVector(-723.36f, -363.26f, -834.52f));

					TArray<float> PawnTimes;
					PawnTimes.Empty();
					PawnTimes.Emplace(1.0f);
					PawnTimes.Emplace(0.5f);
					PawnTimes.Emplace(0.25f);
					PawnTimes.Emplace(1.2f);
					PawnTimes.Emplace(0.7f);
					PawnTimes.Emplace(2.0f);
					PawnTimes.Emplace(0.5f);
					PawnTimes.Emplace(1.4f);

					Pawns.Empty();

					for (int Index = 0; Index < 8; Index++)
					{
						ABBPawn * LerpPawn = TestWorld->SpawnActor<ABBPawn>(PawnClass, SpawnParameters);

						UTEST_TRUE("Pawn is valid.", IsValid(LerpPawn))

						LerpPawn->Controller = Controller;

						ADD_LATENT_AUTOMATION_COMMAND(FBBPawnLerpTestLatentCommand(* this, TestWorld, LerpPawn, PawnLocations[Index], PawnTimes[Index]));
					}

					Done.Execute();

					return true;
				});

				LatentAfterEach([this](const FDoneDelegate & Done)
				{
					ADD_LATENT_AUTOMATION_COMMAND(FBBCloseTestWorldLatentCommand(TestWorld));

					Done.Execute();
				});
			});
		});			
	}
}