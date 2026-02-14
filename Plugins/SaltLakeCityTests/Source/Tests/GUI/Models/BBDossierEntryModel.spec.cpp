// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBDossierEntryControllerStub.h"
#include "GUI/Data/BBDossierEntryStub.h"
#include "GUI/Models/BBDossierEntryModel.h"
#include "GUI/Widgets/BBDossierEntryWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBDossierEntryModelSpec,
	"SaltLakeCity.GUI.Models.DossierEntry",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBDossierEntryWidgetStub * View = nullptr;

	UPROPERTY()
	UBBDossierEntryControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBDossierEntryModel * Model = nullptr;

END_DEFINE_SPEC(UBBDossierEntryModelSpec)

void UBBDossierEntryModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDossierEntryModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		View = CreateWidget<UBBDossierEntryWidgetStub>(TestWorld, UBBDossierEntryWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		Controller = NewObject<UBBDossierEntryControllerStub>(TestWorld, UBBDossierEntryControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;

		View = nullptr;
		Controller = nullptr;
		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("[" + ModelClass->GetName() + "]", [this, ModelClass]()
		{
			struct FBBUpdateTestCase
			{
				public:
					FBBUpdateTestCase(float NewIn, float NewMaxIn, float NewOut, float NewMaxOut) :
						In(NewIn),
						MaxIn(NewMaxIn),
						Out(NewOut),
						MaxOut(NewMaxOut)
					{};

					float In = 0.0f;

					float MaxIn = 0.0f;

					float Out = 0.0f;

					float MaxOut = 0.0f;
			};

			It("Given a dossier entry values update, expect the model to broadcast the new values", [this, ModelClass]()
			{
				TArray<FBBUpdateTestCase> TestCases;
				TestCases.Empty();
				TestCases.Emplace(FBBUpdateTestCase(5.15f, 10.0f, 5.15f, 10.0f));
				TestCases.Emplace(FBBUpdateTestCase(-3.25f, 5.0f, -3.25f, 5.0f));
				TestCases.Emplace(FBBUpdateTestCase(6.74f, 2.24f, 6.74f, 2.24f));
				TestCases.Emplace(FBBUpdateTestCase(10.0f, 12.17f, 10.0f, 12.17f));
				TestCases.Emplace(FBBUpdateTestCase(256.74f, 8.0f, 256.74f, 8.0f));
				TestCases.Emplace(FBBUpdateTestCase(3.68f, 7.0f, 3.68f, 7.0f));
				TestCases.Emplace(FBBUpdateTestCase(-712.67f, 350.05f, -712.67f, 350.05f));
				TestCases.Emplace(FBBUpdateTestCase(0.0f, 10.0f, 0.0f, 10.0f));
				TestCases.Emplace(FBBUpdateTestCase(443.56f, 0.0f, 443.56f, 0.0f));
				TestCases.Emplace(FBBUpdateTestCase(7.35f, 1.62f, 7.35f, 1.62f));

				UBBDossierEntryStub * Entry = NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass());

				UTEST_TRUE("Entry is valid", IsValid(Entry))

				Model = NewObject<UBBDossierEntryModel>(TestWorld, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				Model->Initialize(View, Entry);

				Controller->Initialize(View, Model);

				for (FBBUpdateTestCase & TestCase : TestCases)
				{
					Entry->SetValue(TestCase.In);
					Entry->SetMaxValue(TestCase.MaxIn);

					TEST_TRUE(Controller->GetValue() == TestCase.Out)
					TEST_TRUE(Controller->GetMaxValue() == TestCase.MaxOut)
				}

				Model->Finalize();

				Controller->Finalize();

				return true;
			});
		});
	}
}