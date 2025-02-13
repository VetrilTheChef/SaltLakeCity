// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TileView.h"
#include "Components/WidgetSwitcher.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBBuildControllerStub.h"
#include "GUI/Data/BBBuildEntryStub.h"
#include "GUI/Widgets/BBBuildWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBBuildWidgetSpec, "SaltLakeCity.GUI.Widgets.Build", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

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
	TArray<UIBBBuildEntry *> BuildEntries;

	UPROPERTY()
	UBBBuildControllerStub * Controller;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBBuildWidget * View;

END_DEFINE_SPEC(UBBBuildWidgetSpec)

void UBBBuildWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	Categories.Empty();
	Categories.Emplace(EBBBuildCategory::Foundation);
	Categories.Emplace(EBBBuildCategory::Customization);
	Categories.Emplace(EBBBuildCategory::Foundation);
	Categories.Emplace(EBBBuildCategory::Outdoors);
	Categories.Emplace(EBBBuildCategory::Indoors);

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
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = NewObject<UBBBuildControllerStub>(TestWorld, UBBBuildControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		BuildEntries.Empty();

		for (int Index = 0; Index < 5; Index++)
		{
			UBBBuildEntryStub * BuildEntry = NewObject<UBBBuildEntryStub>(Controller, UBBBuildEntryStub::StaticClass());

			UTEST_TRUE("Build Entry is valid", IsValid(BuildEntry))

			BuildEntry->AddToRoot();
			BuildEntry->SetEntryName(Names[Index]);
			BuildEntry->SetEntryIcon(Icons[Index]);
			BuildEntry->SetEntryPrice(Prices[Index]);
			BuildEntry->SetEntryTime(Times[Index]);

			BuildEntries.Emplace(BuildEntry);
		}

		return true;
	});

	AfterEach([this]()
	{
		for (UIBBBuildEntry * & BuildEntry : BuildEntries)
		{
			if (IsValid(BuildEntry))
			{
				BuildEntry->RemoveFromRoot();
				BuildEntry->MarkPendingKill();
			}
			
			BuildEntry = nullptr;
		}

		BuildEntries.Empty();

		Controller = nullptr;
		View = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new entry, expect the view to add it to the entries list", [this, ViewClass]()
			{
				View = CreateWidget<UBBBuildWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				Controller->Initialize(View, nullptr);

				UWidgetSwitcher * CategorySwitcher = Cast<UWidgetSwitcher>(View->WidgetTree->FindWidget(TEXT("CategorySwitcher")));

				UTEST_TRUE("CategorySwitcher is valid", IsValid(CategorySwitcher))

				for (int Index = 0; Index < 5; Index++)
				{
					UTileView * CategoryTile = Cast<UTileView>(CategorySwitcher->GetWidgetAtIndex((int)Categories[Index] - 1));

					UTEST_TRUE("Category Tile is valid", IsValid(CategoryTile))

					View->AddEntry(Categories[Index], BuildEntries[Index]);

					int ItemIndex = CategoryTile->GetIndexForItem(BuildEntries[Index]);

					TEST_TRUE(ItemIndex != INDEX_NONE)

					if (ItemIndex != INDEX_NONE)
					{
						UBBBuildEntryStub * RetrievedEntry = Cast<UBBBuildEntryStub>(CategoryTile->GetItemAt(ItemIndex));

						TEST_TRUE(IsValid(RetrievedEntry))

						if (IsValid(RetrievedEntry))
						{
							TEST_TRUE(RetrievedEntry->GetEntryName().EqualTo(BuildEntries[Index]->GetEntryName()))
							TEST_TRUE(RetrievedEntry->GetEntryIcon() == BuildEntries[Index]->GetEntryIcon())
							TEST_TRUE(RetrievedEntry->GetEntryPrice() == BuildEntries[Index]->GetEntryPrice())
							TEST_TRUE(RetrievedEntry->GetEntryTime() == BuildEntries[Index]->GetEntryTime())
						}
					}
				}

				Controller->Finalize();

				return true;
			});

			It("Given entries to be cleared, expect the view to empty the entries list", [this, ViewClass]()
			{
				View = CreateWidget<UBBBuildWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				Controller->Initialize(View, nullptr);

				for (int Index = 0; Index < 5; Index++)
				{
					View->AddEntry(Categories[Index], BuildEntries[Index]);
				}

				for (int Index = 0; Index < 5; Index++)
				{
					View->ClearEntries(Categories[Index]);
				}

				UWidgetSwitcher * CategorySwitcher = Cast<UWidgetSwitcher>(View->WidgetTree->FindWidget(TEXT("CategorySwitcher")));

				UTEST_TRUE("Category Switcher is valid", IsValid(CategorySwitcher))

				for (int Index = 0; Index < 5; Index++)
				{
					UTileView * CategoryTile = Cast<UTileView>(CategorySwitcher->GetWidgetAtIndex((int)Categories[Index] - 1));

					UTEST_TRUE("Category Tile is valid", IsValid(CategoryTile))

					TEST_TRUE(CategoryTile->GetListItems().Num() == 0)
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}