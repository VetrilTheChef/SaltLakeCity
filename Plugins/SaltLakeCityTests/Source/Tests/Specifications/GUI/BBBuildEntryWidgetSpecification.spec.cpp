// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBBuildDataStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Data/BBBuildEntry.h"
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
#include "GUI/Widgets/BBBuildEntryWidgetStub.h"
#include "Specifications/GUI/BBBuildEntryWidgetSpecification.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBBuildEntryWidgetSpecificationSpec,
	"SaltLakeCity.Specifications.GUI.BuildEntryWidgetSpecification",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> WidgetSpecificationClasses;

	// SUT
	UPROPERTY()
	UBBBuildEntryWidgetSpecification * WidgetSpecification = nullptr;

END_DEFINE_SPEC(UBBBuildEntryWidgetSpecificationSpec)

void UBBBuildEntryWidgetSpecificationSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildEntryWidgetSpecification>(FString(TEXT("/Game/Specifications/GUI")), WidgetSpecificationClasses);

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
			It("Given a new GUI model that is not a build entry model, expect the specification to evaluate it negatively.", [this, WidgetSpecificationClass]()
			{
				WidgetSpecification = NewObject<UBBBuildEntryWidgetSpecification>(TestWorld, WidgetSpecificationClass);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				WidgetSpecification->SetBuildEntry(NewObject<UBBBuildEntry>(WidgetSpecification, UBBBuildEntry::StaticClass()));

				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBBuildModelStub>(WidgetSpecification, UBBBuildModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBContextModelStub>(WidgetSpecification, UBBContextModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBDateTimeModelStub>(WidgetSpecification, UBBDateTimeModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBDossierModelStub>(WidgetSpecification, UBBDossierModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBJobModelStub>(WidgetSpecification, UBBJobModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBModesModelStub>(WidgetSpecification, UBBModesModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBProgressModelStub>(WidgetSpecification, UBBProgressModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBSelectionModelStub>(WidgetSpecification, UBBSelectionModelStub::StaticClass())))
				TEST_FALSE(WidgetSpecification->Evaluate(NewObject<UBBTitleModelStub>(WidgetSpecification, UBBTitleModelStub::StaticClass())))

				return true;
			});

			It("Given a new GUI model that is a build entry model, expect the specification to evaluate it correctly.", [this, WidgetSpecificationClass]()
			{
				struct FBBBEWSpecTestCase
				{
					public:
						FBBBEWSpecTestCase() :
							Name(FText::FromString("")),
							Icon(nullptr),
							Price(0.0),
							Time(0.0),
							Buildables(TArray<FBBBuildablePtr>()),
							BuildDataClass(TSoftClassPtr<UIBBBuildData>()),
							Result(false)
						{};

						FBBBEWSpecTestCase(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, float NewPrice, float NewTime, TArray<FBBBuildablePtr> NewBuildables, TSoftClassPtr<UIBBBuildData> NewBuildDataClass, bool NewResult) :
							Name(NewName),
							Icon(NewIcon),
							Price(NewPrice),
							Time(NewTime),
							Buildables(NewBuildables),
							BuildDataClass(NewBuildDataClass),
							Result(NewResult)
						{};

						FText Name = FText::FromString("");

						TSoftObjectPtr<UTexture2D> Icon = TSoftObjectPtr<UTexture2D>();

						float Price = 0.0f;

						float Time = 0.0f;

						TArray<FBBBuildablePtr> Buildables;

						TSoftClassPtr<UIBBBuildData> BuildDataClass = TSoftClassPtr<UIBBBuildData>();

						bool Result = false;
				};

				UBBBuildEntryWidgetStub * TestView = CreateWidget<UBBBuildEntryWidgetStub>(TestWorld, UBBBuildEntryWidgetStub::StaticClass());

				UTEST_TRUE("Test View is valid", IsValid(TestView))

				TestView->NativeOnInitialized();

				UTexture2D * CorrectTexture = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());

				UTexture2D * WrongTexture = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());

				TArray<FBBBEWSpecTestCase> TestCases;

				TestCases.Emplace(FBBBEWSpecTestCase(FText::FromString("Some name"), TSoftObjectPtr<UTexture2D>(nullptr), -51.26f, 37.96f, TArray<FBBBuildablePtr>(), TSoftClassPtr<UIBBBuildData>(UBBBuildDataStub::StaticClass()), false));
				TestCases.Emplace(FBBBEWSpecTestCase(FText::FromString("Wrong"), TSoftObjectPtr<UTexture2D>(WrongTexture), 834.16f, -762.34f, TArray<FBBBuildablePtr>(), TSoftClassPtr<UIBBBuildData>(), false));
				TestCases.Emplace(FBBBEWSpecTestCase(FText::FromString("&%(=''___5124"), TSoftObjectPtr<UTexture2D>(CorrectTexture), -915.21f, 27.511f, TArray<FBBBuildablePtr>(), TSoftClassPtr<UIBBBuildData>(), false));
				TestCases.Emplace(FBBBEWSpecTestCase(FText::FromString("The Correct Name"), TSoftObjectPtr<UTexture2D>(CorrectTexture), 626.17f, 27.511f, TArray<FBBBuildablePtr>(), TSoftClassPtr<UIBBBuildData>(UBBBuildDataStub::StaticClass()), true));
				TestCases.Emplace(FBBBEWSpecTestCase(FText::FromString("The Correct Name"), TSoftObjectPtr<UTexture2D>(WrongTexture), 626.17f, 0.0f, TArray<FBBBuildablePtr>(), TSoftClassPtr<UIBBBuildData>(UBBBuildDataStub::StaticClass()), false));

				WidgetSpecification = NewObject<UBBBuildEntryWidgetSpecification>(TestWorld, WidgetSpecificationClass);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				UBBBuildEntryModelStub * TestModel = NewObject<UBBBuildEntryModelStub>(WidgetSpecification, UBBBuildEntryModelStub::StaticClass());
					
				UTEST_TRUE("Test Model is valid", IsValid(TestModel))

				UBBBuildEntry * SpecificationEntry = NewObject<UBBBuildEntry>(WidgetSpecification, UBBBuildEntry::StaticClass());

				UTEST_TRUE("Specification Entry is valid", IsValid(SpecificationEntry))

				TestModel->Initialize(TestView, nullptr);

				TestModel->SetEntryName(FText::FromString("The Correct Name"));
				TestModel->SetEntryIcon(TSoftObjectPtr<UTexture2D>(CorrectTexture));
				TestModel->SetEntryPrice(626.17f);
				TestModel->SetEntryTime(27.511f);
				TestModel->SetEntryBuildableClasses(TArray<FBBBuildablePtr>());
				TestModel->SetEntryBuildDataClass(TSoftClassPtr<UIBBBuildData>(UBBBuildDataStub::StaticClass()));

				WidgetSpecification->SetBuildEntry(SpecificationEntry);

				for (FBBBEWSpecTestCase & TestCase : TestCases)
				{
					SpecificationEntry->SetEntryName(TestCase.Name);
					SpecificationEntry->SetEntryIcon(TestCase.Icon);
					SpecificationEntry->SetEntryPrice(TestCase.Price);
					SpecificationEntry->SetEntryTime(TestCase.Time);
					SpecificationEntry->SetEntryBuildables(TestCase.Buildables);
					SpecificationEntry->SetEntryBuildDataClass(TestCase.BuildDataClass);

					TEST_TRUE(WidgetSpecification->Evaluate(TestModel) == TestCase.Result);
				}

				return true;
			});
		});
	}
}