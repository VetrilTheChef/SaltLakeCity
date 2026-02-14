// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "GUI/Data/BBDossierEntryStub.h"
#include "GUI/Widgets/BBDossierWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBDossierWidgetSpec,
	"SaltLakeCity.GUI.Widgets.Dossier",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBDossierWidget * View = nullptr;

END_DEFINE_SPEC(UBBDossierWidgetSpec)

void UBBDossierWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDossierWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		return true;
	});

	AfterEach([this]()
	{
		View = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new display name, expect the view to update its display name", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UTextBlock * DisplayNameText = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("DisplayNameText")));

				UTEST_TRUE("Display Name Text is valid", IsValid(DisplayNameText))

				TArray<FText> DisplayNames;
				DisplayNames.Emplace(FText::FromString("Display Name"));
				DisplayNames.Emplace(FText::FromString("%£?=UQ%)?Hie"));
				DisplayNames.Emplace(FText::FromString("2416789567"));
				DisplayNames.Emplace(FText::FromString("-_$!&!%%!/--"));
				DisplayNames.Emplace(FText::FromString("           !"));

				for (FText & DisplayName : DisplayNames)
				{
					View->SetDisplayName(DisplayName);

					TEST_TRUE(DisplayNameText->GetText().EqualTo(DisplayName))
				}

				return true;
			});

			It("Given a new attribute entry, expect the view to update its attribute entries", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UListView * AttributeEntries = Cast<UListView>(View->WidgetTree->FindWidget(TEXT("AttributeEntries")));

				UTEST_TRUE("Attribute Entries is valid", IsValid(AttributeEntries))

				TArray<UBBDossierEntryStub *> Entries;
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));

				TEST_TRUE(AttributeEntries->GetNumItems() == 0)

				for (int Index = 0; Index < Entries.Num(); Index++)
				{
					View->AddAttributeEntry(Entries[Index]);

					TEST_TRUE(AttributeEntries->GetNumItems() == Index + 1)
				}

				return true;
			});

			It("Given a new need entry, expect the view to update its need entries", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UListView * NeedEntries = Cast<UListView>(View->WidgetTree->FindWidget(TEXT("NeedEntries")));

				UTEST_TRUE("Need Entries is valid", IsValid(NeedEntries))

				TArray<UBBDossierEntryStub *> Entries;
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));

				TEST_TRUE(NeedEntries->GetNumItems() == 0)

				for (int Index = 0; Index < Entries.Num(); Index++)
				{
					View->AddNeedEntry(Entries[Index]);

					TEST_TRUE(NeedEntries->GetNumItems() == Index + 1)
				}

				return true;
			});

			It("Given a new skill entry, expect the view to update its skill entries", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UListView * SkillEntries = Cast<UListView>(View->WidgetTree->FindWidget(TEXT("SkillEntries")));

				UTEST_TRUE("Skill Entries is valid", IsValid(SkillEntries))

				TArray<UBBDossierEntryStub *> Entries;
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(NewObject<UBBDossierEntryStub>(TestWorld, UBBDossierEntryStub::StaticClass()));

				TEST_TRUE(SkillEntries->GetNumItems() == 0)

				for (int Index = 0; Index < Entries.Num(); Index++)
				{
					View->AddSkillEntry(Entries[Index]);

					TEST_TRUE(SkillEntries->GetNumItems() == Index + 1)
				}

				return true;
			});
		});
	}
}