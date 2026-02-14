// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/BBProgressComponentStub.h"
#include "GUI/Models/BBProgressModel.h"
#include "GUI/Widgets/BBProgressWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBProgressModelSpec,
	"SaltLakeCity.GUI.Models.Progress",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBProgressWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<float> Progresses;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBProgressModel * Model = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBProgressModelSpec)

void UBBProgressModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBProgressModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	Progresses.Empty();
	Progresses.Emplace(0.0f);
	Progresses.Emplace(100.0f);
	Progresses.Emplace(52.0f);
	Progresses.Emplace(-15.0f);
	Progresses.Emplace(263.0f);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		View = CreateWidget<UBBProgressWidgetStub>(TestWorld, UBBProgressWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		return true;
	});

	AfterEach([this]()
	{
		View = nullptr;

		Model = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("[" + ModelClass->GetName() + "]", [this, ModelClass]()
		{
			It("Given a progress update from the component, expect the model to update the view's progress", [this, ModelClass]()
			{
				Model = NewObject<UBBProgressModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				UBBProgressComponentStub * ProgressComponent = NewObject<UBBProgressComponentStub>(TestWorld, UBBProgressComponentStub::StaticClass(), FName(TEXT("ProgressModelTest")));

				UTEST_TRUE("Progress Component is valid", IsValid(ProgressComponent))

				Model->Initialize(View, ProgressComponent);

				for (int Index = 0; Index < Progresses.Num(); Index++)
				{
					View->SetProgress(-1.0f);

					TEST_TRUE(View->GetProgress() == -1.0f)

					ProgressComponent->SetProgress(Progresses[Index]);

					TEST_TRUE(View->GetProgress() == Progresses[Index])
				}

				Model->Finalize();

				ProgressComponent->MarkAsGarbage();
				ProgressComponent = nullptr;

				return true;
			});

			It("Given a progress update from the finalized component, expect the model not to update the controller's progress", [this, ModelClass]()
			{
				Model = NewObject<UBBProgressModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				UBBProgressComponentStub * ProgressComponent = NewObject<UBBProgressComponentStub>(TestWorld, UBBProgressComponentStub::StaticClass(), FName(TEXT("ProgressModelTest")));

				UTEST_TRUE("Progress Component is valid", IsValid(ProgressComponent))

				Model->Initialize(View, ProgressComponent);
				Model->Finalize();

				for (int Index = 0; Index < Progresses.Num(); Index++)
				{
					View->SetProgress(-1.0f);

					TEST_TRUE(View->GetProgress() == -1.0f)

					ProgressComponent->SetProgress(Progresses[Index]);

					TEST_TRUE(View->GetProgress() == -1.0f)
				}

				ProgressComponent->MarkAsGarbage();
				ProgressComponent = nullptr;

				return true;
			});
		});
	}
}