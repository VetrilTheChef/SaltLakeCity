// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBWidgetTargetStub.h"
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
#include "GUI/Widgets/BBDossierWidgetStub.h"
#include "Specifications/GUI/BBDossierWidgetSpecification.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBDossierWidgetSpecificationSpec, "SaltLakeCity.Specifications.GUI.DossierWidgetSpecification", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> WidgetSpecificationClasses;

	// SUT
	UPROPERTY()
	UBBDossierWidgetSpecification * WidgetSpecification = nullptr;

END_DEFINE_SPEC(UBBDossierWidgetSpecificationSpec)

void UBBDossierWidgetSpecificationSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDossierWidgetSpecification>(FString(TEXT("/Game/Specifications/GUI")), WidgetSpecificationClasses);

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
			It("Given a new GUI model that is not a dossier model, expect the specification to evaluate it negatively.", [this, WidgetSpecificationClass]()
			{
				WidgetSpecification = NewObject<UBBDossierWidgetSpecification>(TestWorld, WidgetSpecificationClass);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBBuildEntryModelStub>(WidgetSpecification, UBBBuildEntryModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBBuildModelStub>(WidgetSpecification, UBBBuildModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBContextModelStub>(WidgetSpecification, UBBContextModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBDateTimeModelStub>(WidgetSpecification, UBBDateTimeModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBJobModelStub>(WidgetSpecification, UBBJobModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBModesModelStub>(WidgetSpecification, UBBModesModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBProgressModelStub>(WidgetSpecification, UBBProgressModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBSelectionModelStub>(WidgetSpecification, UBBSelectionModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBTitleModelStub>(WidgetSpecification, UBBTitleModelStub::StaticClass())))

				return true;
			});

			It("Given a new GUI model that is a dossier model, expect the specification to evaluate it correctly.", [this, WidgetSpecificationClass]()
			{
				WidgetSpecification = NewObject<UBBDossierWidgetSpecification>(TestWorld, WidgetSpecificationClass);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				UBBDossierModelStub * TestModel = NewObject<UBBDossierModelStub>(WidgetSpecification, UBBDossierModelStub::StaticClass());
					
				UTEST_TRUE("Test Model is valid", IsValid(TestModel))

				UBBDossierWidgetStub * TestView = CreateWidget<UBBDossierWidgetStub>(TestWorld, UBBDossierWidgetStub::StaticClass());

				UTEST_TRUE("Test View is valid", IsValid(TestView))

				TestView->NativeOnInitialized();

				for (int Tests = 0; Tests < 5; Tests++)
				{
					UBBWidgetTargetStub * TestTarget = NewObject<UBBWidgetTargetStub>(TestWorld, UBBWidgetTargetStub::StaticClass());

					TestModel->Initialize(TestView, nullptr);

					TestModel->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(TestTarget));

					WidgetSpecification->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(TestTarget));

					TEST_TRUE(WidgetSpecification->Evaluate(TestModel))

					TestModel->Finalize();
				}

				return true;
			});
		});
	}
}