// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Models/BBBuildEntryModelStub.h"
#include "GUI/Models/BBBuildModelStub.h"
#include "GUI/Models/BBContextModelStub.h"
#include "GUI/Models/BBDateTimeModelStub.h"
#include "GUI/Models/BBDossierModelStub.h"
#include "GUI/Models/BBJobModelStub.h"
#include "GUI/Models/BBModesModelStub.h"
#include "GUI/Models/BBProgressModelStub.h"
#include "GUI/Models/BBSelectionModelStub.h"
#include "GUI/Models/BBTitleModelStub.h"
#include "GUI/Widgets/BBProgressWidgetStub.h"
#include "Specifications/GUI/BBProgressWidgetSpecification.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBProgressWidgetSpecificationSpec, "SaltLakeCity.Specifications.GUI.ProgressWidgetSpecification", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> WidgetSpecificationClasses;

	// SUT
	UPROPERTY()
	UBBProgressWidgetSpecification * WidgetSpecification = nullptr;

END_DEFINE_SPEC(UBBProgressWidgetSpecificationSpec)

void UBBProgressWidgetSpecificationSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBProgressWidgetSpecification>(FString(TEXT("/Game/Specifications/GUI")), WidgetSpecificationClasses);

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
		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & WidgetSpecificationClass : WidgetSpecificationClasses)
	{
		Describe("[" + WidgetSpecificationClass->GetName() + "]", [this, WidgetSpecificationClass]()
		{
			It("Given a new GUI model that is not a progress model, expect the specification to evaluate it negatively.", [this, WidgetSpecificationClass]()
			{
				WidgetSpecification = NewObject<UBBProgressWidgetSpecification>(TestWorld, WidgetSpecificationClass);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBBuildEntryModelStub>(WidgetSpecification, UBBBuildEntryModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBBuildModelStub>(WidgetSpecification, UBBBuildModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBContextModelStub>(WidgetSpecification, UBBContextModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBDateTimeModelStub>(WidgetSpecification, UBBDateTimeModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBDossierModelStub>(WidgetSpecification, UBBDossierModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBJobModelStub>(WidgetSpecification, UBBJobModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBModesModelStub>(WidgetSpecification, UBBModesModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBSelectionModelStub>(WidgetSpecification, UBBSelectionModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBTitleModelStub>(WidgetSpecification, UBBTitleModelStub::StaticClass())))

				return true;
			});

			It("Given a new GUI model that is a progress model, expect the specification to evaluate it correctly.", [this, WidgetSpecificationClass]()
			{
				WidgetSpecification = NewObject<UBBProgressWidgetSpecification>(TestWorld, WidgetSpecificationClass);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				UBBProgressModelStub * TestModel = NewObject<UBBProgressModelStub>(WidgetSpecification, UBBProgressModelStub::StaticClass());
					
				UTEST_TRUE("Test Model is valid", IsValid(TestModel))

				UBBProgressWidgetStub * TestView = CreateWidget<UBBProgressWidgetStub>(TestWorld, UBBProgressWidgetStub::StaticClass());

				UTEST_TRUE("Test View is valid", IsValid(TestView))

				TestView->NativeOnInitialized();

				TestModel->Initialize(TestView, nullptr);

				TEST_TRUE(WidgetSpecification->Evaluate(TestModel))

				return true;
			});
		});
	}
}