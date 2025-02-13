// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBBuildController.h"
#include "GUI/Data/BBBuildEntryStub.h"
#include "GUI/Models/BBBuildModelStub.h"
#include "GUI/Widgets/BBBuildWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBBuildControllerSpec, "SaltLakeCity.GUI.Controllers.Build", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBBuildModelStub * Model = nullptr;

	UPROPERTY()
	UBBBuildWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<EBBBuildCategory> Categories;

	UPROPERTY()
	TArray<FText> Names;

	UPROPERTY()
	TArray<TSoftObjectPtr<UTexture2D>> Icons;

	UPROPERTY()
	TArray<float> Prices;

	UPROPERTY()
	TArray<float> Times;

	UPROPERTY()
	TArray<TArray<FBBBuildablePtr>> AllBuildables;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBBuildController * Controller = nullptr;

	void TestCategoryEntries(EBBBuildCategory Category, UBBBuildWidgetStub * BuildWidgetStub, UBBBuildModelStub * BuildModelStub);

	void TestCategoryNoEntries(EBBBuildCategory Category, UBBBuildWidgetStub * BuildWidgetStub);

END_DEFINE_SPEC(UBBBuildControllerSpec)

void UBBBuildControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	Categories.Empty();
	Categories.Emplace(EBBBuildCategory::None);
	Categories.Emplace(EBBBuildCategory::Customization);
	Categories.Emplace(EBBBuildCategory::Foundation);
	Categories.Emplace(EBBBuildCategory::Indoors);
	Categories.Emplace(EBBBuildCategory::Outdoors);

	Names.Empty();
	Names.Emplace(FText::FromString("FOUNDATION 1"));
	Names.Emplace(FText::FromString("OTHER CATEGORY"));
	Names.Emplace(FText::FromString("STRUCUTAL"));
	Names.Emplace(FText::FromString("Outdoorsy"));
	Names.Emplace(FText::FromString("OBJECTOBJECTOBJECT"));

	Icons.Empty();
	Icons.Emplace(TSoftObjectPtr<UTexture2D>(FSoftObjectPath(FString(""))));
	Icons.Emplace(TSoftObjectPtr<UTexture2D>(FSoftObjectPath(FString(""))));
	Icons.Emplace(TSoftObjectPtr<UTexture2D>(FSoftObjectPath(FString(""))));
	Icons.Emplace(TSoftObjectPtr<UTexture2D>(FSoftObjectPath(FString(""))));
	Icons.Emplace(TSoftObjectPtr<UTexture2D>(FSoftObjectPath(FString(""))));

	Prices.Empty();
	Prices.Emplace(24.0f);
	Prices.Emplace(10.0f);
	Prices.Emplace(-454.0f);
	Prices.Emplace(12.0f);
	Prices.Emplace(1621.0f);

	Times.Empty();
	Times.Emplace(3000.0f);
	Times.Emplace(-105.0f);
	Times.Emplace(523.523f);
	Times.Emplace(1.5f);
	Times.Emplace(-25.0f);

	AllBuildables.Empty();
	TArray<FBBBuildablePtr> Buildables;

	Buildables.Empty();
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	AllBuildables.Emplace(Buildables);

	Buildables.Empty();
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	AllBuildables.Emplace(Buildables);

	Buildables.Empty();
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	AllBuildables.Emplace(Buildables);

	Buildables.Empty();
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	AllBuildables.Emplace(Buildables);

	Buildables.Empty();
	Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
	AllBuildables.Emplace(Buildables);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Model = NewObject<UBBBuildModelStub>(TestWorld, UBBBuildModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		for (int Index = 0; Index < 5; Index++)
		{
			Model->AddEntry(Categories[Index], Names[Index], Icons[Index], Prices[Index], Times[Index], TArray<FBBBuildablePtr>());
		}

		View = CreateWidget<UBBBuildWidgetStub>(TestWorld, UBBBuildWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

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

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("["+ ControllerClass->GetName() +"]", [this, ControllerClass]()
		{
			It("Given a new view, expect the controller to set the view's entries", [this, ControllerClass]()
			{
				Controller = NewObject<UBBBuildController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model);

				#define EBBBUILDCATEGORY_OPERATION(Value) TestCategoryEntries(Value, View, Model);

					FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

				#undef EBBBUILDCATEGORY_OPERATION

				Controller->Finalize();

				return true;
			});

			It("Given a view to be finalized, expect the controller to clear the view's entries", [this, ControllerClass]()
			{
				Controller = NewObject<UBBBuildController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model);
				Controller->Finalize();

				#define EBBBUILDCATEGORY_OPERATION(Value) TestCategoryNoEntries(Value, View);

					FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

				#undef EBBBUILDCATEGORY_OPERATION

				return true;
			});
		});
	}
}

void UBBBuildControllerSpec::TestCategoryEntries(EBBBuildCategory Category, UBBBuildWidgetStub * BuildViewStub, UBBBuildModelStub * BuildModelStub)
{
	TEST_TRUE(BuildViewStub->GetNumEntries(Category) == BuildModelStub->GetNumEntries(Category));

	for (int Index = 0; Index < BuildViewStub->GetNumEntries(Category); Index++)
	{
		UIBBBuildEntry * ViewEntry = View->GetEntry(Category, Index);
		UIBBBuildEntry * ModelEntry = Model->GetEntry(Category, Index);

		TEST_TRUE(IsValid(ViewEntry))
		TEST_TRUE(IsValid(ModelEntry))

		if (IsValid(ViewEntry) && IsValid(ModelEntry))
		{
			TEST_TRUE(ViewEntry->GetEntryName().EqualTo(ModelEntry->GetEntryName()))
			TEST_TRUE(ViewEntry->GetEntryIcon() == ModelEntry->GetEntryIcon())
			TEST_TRUE(ViewEntry->GetEntryPrice() == ModelEntry->GetEntryPrice())
			TEST_TRUE(ViewEntry->GetEntryTime() == ModelEntry->GetEntryTime())
		}
	}
}

void UBBBuildControllerSpec::TestCategoryNoEntries(EBBBuildCategory Category, UBBBuildWidgetStub * BuildViewStub)
{
	TEST_TRUE(View->GetNumEntries(Category) == 0)
}