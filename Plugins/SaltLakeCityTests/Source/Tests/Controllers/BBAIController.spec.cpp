// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBAbilityDataStub.h"
#include "Abilities/Tasks/BBBuildTaskStub.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Controllers/BBAIController.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBAIControllerSpec, "SaltLakeCity.Controllers.AIController", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBlackboardData * BlackboardAsset = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	ABBAIController * Controller = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBAIControllerSpec)

void UBBAIControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBAIController>(FString(TEXT("/Game/Controllers")), ControllerClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
		TestWorld->DestroyActor(Controller);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It("Given a new blackboard task, expect the controller to add it to the blackboard", [this, ControllerClass]()
			{
				FName TaskName = FName(TEXT("TaskVariable"));

				Controller = TestWorld->SpawnActor<ABBAIController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				UBlackboardComponent * Blackboard = nullptr;

				UBlackboardData * BlackboardAsset = NewObject<UBlackboardData>(Controller, UBlackboardData::StaticClass());

				UTEST_TRUE("Blackboard Asset is valid", IsValid(BlackboardAsset))

				FBlackboardEntry Entry = FBlackboardEntry();

				Entry.EntryName = TaskName;
				Entry.EntryDescription = TEXT("Testing Task Entry");
				Entry.KeyType = NewObject<UBlackboardKeyType_Object>(BlackboardAsset, UBlackboardKeyType_Object::StaticClass());

				BlackboardAsset->Keys.Emplace(Entry);

				Controller->UseBlackboard(BlackboardAsset, Blackboard);

				UTEST_TRUE("Blackboard is valid", IsValid(Blackboard))

				for (int Tasks = 0; Tasks < 5; Tasks++)
				{
					UBBBuildTaskStub * BuildTask = NewObject<UBBBuildTaskStub>(Controller, UBBBuildTaskStub::StaticClass());

					Controller->SetBlackboardTask(TaskName, BuildTask);

					TEST_TRUE(Blackboard->GetValueAsObject(TaskName) == BuildTask)
				}

				return true;
			});

			It("Given a new blackboard float value, expect the controller to add it to the blackboard", [this, ControllerClass]()
			{
				FName FloatName = FName(TEXT("FloatVariable"));

				Controller = TestWorld->SpawnActor<ABBAIController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				UBlackboardComponent * Blackboard = nullptr;

				UBlackboardData * BlackboardAsset = NewObject<UBlackboardData>(Controller, UBlackboardData::StaticClass());

				UTEST_TRUE("Blackboard Asset is valid", IsValid(BlackboardAsset))

				FBlackboardEntry Entry = FBlackboardEntry();

				Entry.EntryName = FloatName;
				Entry.EntryDescription = TEXT("Testing Float Entry");
				Entry.KeyType = NewObject<UBlackboardKeyType_Float>(BlackboardAsset, UBlackboardKeyType_Float::StaticClass());

				BlackboardAsset->Keys.Emplace(Entry);

				Controller->UseBlackboard(BlackboardAsset, Blackboard);

				UTEST_TRUE("Blackboard is valid", IsValid(Blackboard))

				TArray<float> FloatValues;
				FloatValues.Emplace(15.2f);
				FloatValues.Emplace(-25.125);
				FloatValues.Emplace(641.23f);
				FloatValues.Emplace(-0.02f);
				FloatValues.Emplace(984.71f);

				for (float & FloatValue : FloatValues)
				{
					Controller->SetBlackboardFloat(FloatName, FloatValue);

					TEST_TRUE(Blackboard->GetValueAsFloat(FloatName) == FloatValue);
				}

				return true;
			});

			It("Given a new blackboard object value, expect the controller to add it to the blackboard", [this, ControllerClass]()
			{
				FName ObjectName = FName(TEXT("ObjectVariable"));

				Controller = TestWorld->SpawnActor<ABBAIController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				UBlackboardComponent * Blackboard = nullptr;

				UBlackboardData * BlackboardAsset = NewObject<UBlackboardData>(Controller, UBlackboardData::StaticClass());

				UTEST_TRUE("Blackboard Asset is valid", IsValid(BlackboardAsset))

				FBlackboardEntry Entry = FBlackboardEntry();

				Entry.EntryName = ObjectName;
				Entry.EntryDescription = TEXT("Testing Object Entry");
				Entry.KeyType = NewObject<UBlackboardKeyType_Object>(BlackboardAsset, UBlackboardKeyType_Object::StaticClass());

				BlackboardAsset->Keys.Emplace(Entry);

				Controller->UseBlackboard(BlackboardAsset, Blackboard);

				UTEST_TRUE("Blackboard is valid", IsValid(Blackboard))

				TArray<UObject *> Objects;
				Objects.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				Objects.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				Objects.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				Objects.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				Objects.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));

				for (UObject * & Object : Objects)
				{
					Controller->SetBlackboardObject(ObjectName, Object);

					TEST_TRUE(Blackboard->GetValueAsObject(ObjectName) == Object);
				}

				return true;
			});

			It("Given a new blackboard value to clear, expect the controller to remove it from the blackboard", [this, ControllerClass]()
			{
				FName TaskName = FName(TEXT("TaskVariable"));
				FName FloatName = FName(TEXT("FloatVariable"));
				FName ObjectName = FName(TEXT("ObjectVariable"));

				Controller = TestWorld->SpawnActor<ABBAIController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				UBlackboardComponent * Blackboard = nullptr;

				UBlackboardData * BlackboardAsset = NewObject<UBlackboardData>(Controller, UBlackboardData::StaticClass());

				UTEST_TRUE("Blackboard Asset is valid", IsValid(BlackboardAsset))

				FBlackboardEntry TaskEntry = FBlackboardEntry();

				TaskEntry.EntryName = TaskName;
				TaskEntry.EntryDescription = TEXT("Testing Task Entry");
				TaskEntry.KeyType = NewObject<UBlackboardKeyType_Object>(BlackboardAsset, UBlackboardKeyType_Object::StaticClass());

				FBlackboardEntry FloatEntry = FBlackboardEntry();

				FloatEntry.EntryName = FloatName;
				FloatEntry.EntryDescription = TEXT("Testing Float Entry");
				FloatEntry.KeyType = NewObject<UBlackboardKeyType_Float>(BlackboardAsset, UBlackboardKeyType_Float::StaticClass());

				FBlackboardEntry ObjectEntry = FBlackboardEntry();

				ObjectEntry.EntryName = ObjectName;
				ObjectEntry.EntryDescription = TEXT("Testing Object Entry");
				ObjectEntry.KeyType = NewObject<UBlackboardKeyType_Object>(BlackboardAsset, UBlackboardKeyType_Object::StaticClass());

				BlackboardAsset->Keys.Emplace(TaskEntry);
				BlackboardAsset->Keys.Emplace(FloatEntry);
				BlackboardAsset->Keys.Emplace(ObjectEntry);

				Controller->UseBlackboard(BlackboardAsset, Blackboard);

				UTEST_TRUE("Blackboard is valid", IsValid(Blackboard))

				UBBBuildTaskStub * TaskValue = NewObject<UBBBuildTaskStub>(Controller, UBBBuildTaskStub::StaticClass());
				float FloatValue = 523.0f;
				UBBAbilityDataStub * ObjectValue = NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass());

				for (int Tests = 0; Tests < 5; Tests++)
				{
					Controller->SetBlackboardTask(TaskName, TaskValue);

					TEST_TRUE(Blackboard->GetValueAsObject(TaskName) != UBlackboardKeyType_Object::InvalidValue);

					Controller->ClearBlackboardValue(TaskName);

					TEST_TRUE(Blackboard->GetValueAsObject(TaskName) == UBlackboardKeyType_Object::InvalidValue);

					// ---

					Controller->SetBlackboardFloat(FloatName, FloatValue);

					TEST_TRUE(Blackboard->GetValueAsFloat(FloatName) != UBlackboardKeyType_Float::InvalidValue);

					Controller->ClearBlackboardValue(FloatName);

					TEST_TRUE(Blackboard->GetValueAsFloat(FloatName) == UBlackboardKeyType_Float::InvalidValue);

					// ---

					Controller->SetBlackboardObject(ObjectName, ObjectValue);

					TEST_TRUE(Blackboard->GetValueAsObject(ObjectName) != UBlackboardKeyType_Object::InvalidValue);

					Controller->ClearBlackboardValue(ObjectName);

					TEST_TRUE(Blackboard->GetValueAsObject(ObjectName) == UBlackboardKeyType_Object::InvalidValue);
				}

				return true;
			});
		});
	}
}