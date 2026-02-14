// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBDossierEntryController.h"
#include "GUI/Models/BBDossierEntryModelStub.h"
#include "GUI/Widgets/BBDossierEntryWidgetStub.h"
#include "Specifications/Factories/BBSpecificationFactoryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBDossierEntryControllerSpec,
	"SaltLakeCity.GUI.Controllers.DossierEntry",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBDossierEntryModelStub * Model = nullptr;

	UPROPERTY()
	UBBDossierEntryWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBDossierEntryController * Controller = nullptr;

END_DEFINE_SPEC(UBBDossierEntryControllerSpec)

void UBBDossierEntryControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDossierEntryController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		Model = NewObject<UBBDossierEntryModelStub>(TestWorld, UBBDossierEntryModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		View = CreateWidget<UBBDossierEntryWidgetStub>(TestWorld, UBBDossierEntryWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;

		Controller = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It("Given a new view, expect the controller to initialize the view", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierEntryController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Model->SetEntryName(FText::FromString("Some Kind Of Attribute"));
				Model->SetIcon(TSoftObjectPtr<UTexture2D>(nullptr));
				Model->SetValue(4.22f);
				Model->SetMaxValue(13.61f);

				Controller->Initialize(View, Model);

				TEST_TRUE(View->GetEntryName().EqualTo(Model->GetEntryName()))
				TEST_TRUE(View->GetIcon() == Model->GetIcon().LoadSynchronous())
				TEST_TRUE(View->GetValue().EqualTo(FText::AsNumber(FMath::FloorToInt(Model->GetValue()))))
				TEST_TRUE(View->GetProgress() == (Model->GetValue() / Model->GetMaxValue()))

				Controller->Finalize();

				return true;
			});

			It("Given a new value update, expect the controller to update the view's value", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierEntryController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model);

				TArray<float> Updates;
				Updates.Emplace(23.56f);
				Updates.Emplace(0.0f);
				Updates.Emplace(-82.62f);
				Updates.Emplace(-1246.27f);
				Updates.Emplace(735.62f);

				for (float & Update : Updates)
				{
					Model->SetValue(Update);

					TEST_TRUE(View->GetValue().EqualTo(FText::AsNumber(FMath::FloorToInt(Update))))
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new max value update, expect the controller to update the view's max value", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierEntryController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model);

				float Value = 100.0f;

				TArray<float> Updates;
				Updates.Emplace(-634.56f);
				Updates.Emplace(-16.33f);
				Updates.Emplace(3262.11f);
				Updates.Emplace(0.0f);
				Updates.Emplace(235.59f);

				Model->SetValue(Value);

				for (float & Update : Updates)
				{
					Model->SetMaxValue(Update);

					TEST_TRUE(View->GetProgress() == (Value / Update))
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}