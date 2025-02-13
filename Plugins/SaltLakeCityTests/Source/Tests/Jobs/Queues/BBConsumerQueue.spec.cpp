// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Jobs/Queues/BBConsumerQueue.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBConsumerQueueSpec, "SaltLakeCity.Jobs.Queues.ConsumerQueue", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<FBBManagedConsumer> ManagedConsumers;

	UPROPERTY()
	TArray<UClass *> QueueClasses;

	// SUT
	UPROPERTY()
	UBBConsumerQueue * Queue = nullptr;

END_DEFINE_SPEC(UBBConsumerQueueSpec)

void UBBConsumerQueueSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBConsumerQueue>(FString(TEXT("/Game/Jobs/Queues")), QueueClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))
		
		ManagedConsumers.Empty();
		ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
		ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
		ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
		ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
		ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));

		return true;
	});

	AfterEach([this]()
	{
		Queue = nullptr;

		ManagedConsumers.Empty();

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & QueueClass : QueueClasses)
	{
		Describe("[" + QueueClass->GetName() + "]", [this, QueueClass]()
		{
			It("Given an added consumer, expect the queue to return the correct consumers number", [this, QueueClass]()
			{
				Queue = NewObject<UBBConsumerQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				int ConsumersNum = 0;

				TEST_TRUE(Queue->GetConsumersNum() == ConsumersNum)

				for (FBBManagedConsumer & ManagedConsumer : ManagedConsumers)
				{
					Queue->Add(ManagedConsumer);
					ConsumersNum++;

					TEST_TRUE(Queue->GetConsumersNum() == ConsumersNum)
				}

				return true;
			});

			It("Given a removed consumer, expect the queue to return the correct consumers number", [this, QueueClass]()
			{
				Queue = NewObject<UBBConsumerQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				int ConsumersNum = ManagedConsumers.Num();

				for (FBBManagedConsumer & ManagedConsumer : ManagedConsumers)
				{
					Queue->Add(ManagedConsumer);
				}

				TEST_TRUE(Queue->GetConsumersNum() == ConsumersNum)

				for (ConsumersNum = ConsumersNum - 1; ConsumersNum >= 0; ConsumersNum--)
				{
					Queue->Remove(ManagedConsumers[ConsumersNum]);

					TEST_TRUE(Queue->GetConsumersNum() == ConsumersNum)
				}

				return true;
			});

			It("Given a consumer presence request, expect the queue to return true if it has consumer", [this, QueueClass]()
			{
				Queue = NewObject<UBBConsumerQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				TEST_TRUE(Queue->HasConsumer() == false)

				Queue->Add(ManagedConsumers[0]);

				TEST_TRUE(Queue->HasConsumer() == true)

				Queue->Remove(ManagedConsumers[0]);

				TEST_TRUE(Queue->HasConsumer() == false)
					
				Queue->Add(ManagedConsumers[0]);

				TEST_TRUE(Queue->HasConsumer() == true)

				Queue->Add(ManagedConsumers[1]);

				TEST_TRUE(Queue->HasConsumer() == true)

				Queue->Remove(ManagedConsumers[0]);

				TEST_TRUE(Queue->HasConsumer() == true)

				Queue->Add(ManagedConsumers[2]);

				TEST_TRUE(Queue->HasConsumer() == true)

				Queue->Remove(ManagedConsumers[1]);

				TEST_TRUE(Queue->HasConsumer() == true)

				Queue->Remove(ManagedConsumers[2]);

				TEST_TRUE(Queue->HasConsumer() == false)

				return true;
			});

			It("Given a queue iterator request, expect the queue to return it", [this, QueueClass]()
			{
				Queue = NewObject<UBBConsumerQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				for (FBBManagedConsumer & ManagedConsumer : ManagedConsumers)
				{
					Queue->Add(ManagedConsumer);
				}

				UTEST_TRUE("Queue has the correct number of consumers", Queue->GetConsumersNum() == ManagedConsumers.Num())

				UIBBConsumerQueueIterator * Iterator = Queue->GetIterator();

				UTEST_TRUE("Queue Iterator is valid", IsValid(Iterator))

				TArray<UIBBWorkComponent *> RemainingConsumers;

				for (FBBManagedConsumer & ManagedConsumer : ManagedConsumers)
				{
					RemainingConsumers.Emplace(ManagedConsumer.Consumer);
				}

				for (int Index = 0; Index < Queue->GetConsumersNum(); Index++)
				{
					FBBManagedConsumer ManagedConsumer;

					UTEST_TRUE("Queue Iterator has next", Iterator->HasNext())

					Iterator->Next(ManagedConsumer);

					UIBBWorkComponent * Consumer = ManagedConsumer.Consumer;

					UTEST_TRUE("Consumer is valid", IsValid(Consumer))

					UTEST_TRUE("Consumer is one of the remaining consumers", RemainingConsumers.Contains(Consumer))

					RemainingConsumers.Remove(Consumer);
				}

				UTEST_TRUE("Queue Iterator has returned all consumers", RemainingConsumers.Num() == 0)

				return true;
			});
		});
	}
}