// SaltLakeCity 4.26

#pragma once

#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Tests/BBTestUtil.h"

// Performs a test of Pawn Lerp functionality

class FBBPawnLerpTestLatentCommand : public IAutomationLatentCommand
{
	public:
		FBBPawnLerpTestLatentCommand(FAutomationTestBase & NewOwnerTest, UWorld * NewWorld, AIBBPawn * NewPawn, FVector NewLocation, float NewTime) :
			OwnerTest(NewOwnerTest),
			World(NewWorld),
			Pawn(NewPawn),
			Location(NewLocation),
			Time(NewTime)
		{
			Pawn->Lerp(Location, Time);

			Time = World->GetRealTimeSeconds() + Time + 3.0f;
		}

		virtual ~FBBPawnLerpTestLatentCommand()
		{}

		virtual bool Update() override
		{
			if (World->GetRealTimeSeconds() >= Time)
			{
				OwnerTest.TEST_TRUE(Pawn->GetActorLocation() == Location)

				World->DestroyActor(Pawn);

				return true;
			}

			return false;
		}

	private:
		FAutomationTestBase & OwnerTest;

		UWorld * World;

		AIBBPawn * Pawn;

		FVector Location;

		float Time;
};

// Performs a test of Pawn Move functionality

class FBBPawnMoveTestLatentCommand : public IAutomationLatentCommand
{
	public:
		FBBPawnMoveTestLatentCommand(FAutomationTestBase & NewOwnerTest, UWorld * NewWorld, AIBBPawn * NewPawn, FVector NewDirection, float NewScale) :
			OwnerTest(NewOwnerTest),
			World(NewWorld),
			Pawn(NewPawn),
			Direction(NewDirection),
			Scale(NewScale)
		{
			Location = Pawn->GetActorLocation();

			Pawn->Move(Direction, Scale);

			Time = World->GetRealTimeSeconds() + 3.0f;
		}

		virtual ~FBBPawnMoveTestLatentCommand()
		{}

		virtual bool Update() override
		{
			if (World->GetRealTimeSeconds() >= Time)
			{
				OwnerTest.TEST_TRUE(Pawn->GetActorLocation() != Location)
				OwnerTest.TEST_TRUE(Pawn->GetActorLocation().Z == Location.Z)

				World->DestroyActor(Pawn);

				return true;
			}

			return false;
		}

	private:
		FAutomationTestBase & OwnerTest;

		UWorld * World;

		AIBBPawn * Pawn;

		FVector Direction;

		float Scale;

		FVector Location;

		float Time;
};