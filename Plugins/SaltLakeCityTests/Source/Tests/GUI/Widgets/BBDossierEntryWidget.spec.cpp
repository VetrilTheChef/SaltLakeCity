// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/ListView.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GUI/Data/BBDossierEntryStub.h"
#include "GUI/Widgets/BBDossierEntryWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBDossierEntryWidgetSpec,
	"SaltLakeCity.GUI.Widgets.DossierEntry",
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
	UBBDossierEntryWidget * View = nullptr;

END_DEFINE_SPEC(UBBDossierEntryWidgetSpec)

void UBBDossierEntryWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDossierEntryWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

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
			It("Given a new entry name, expect the view to update its entry name", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UTextBlock * EntryName = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("EntryName")));

				UTEST_TRUE("Entry Name is valid", IsValid(EntryName))

				TArray<FText> Names;
				Names.Emplace(FText::FromString("Some Entry"));
				Names.Emplace(FText::FromString("12614__1325"));
				Names.Emplace(FText::FromString("Another Entry151"));
				Names.Emplace(FText::FromString("623h081g54r8"));
				Names.Emplace(FText::FromString(" - -%$!$--_ -_!"));

				for (FText & Name : Names)
				{
					View->SetEntryName(Name);

					TEST_TRUE(EntryName->GetText().EqualTo(Name))
				}

				return true;
			});

			It("Given a new entry icon, expect the view to update its entry icon", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UBorder * EntryIcon = Cast<UBorder>(View->WidgetTree->FindWidget(TEXT("EntryIcon")));

				UTEST_TRUE("Entry Icon is valid", IsValid(EntryIcon))

				UTexture2D * EntryIconTexture = Cast<UTexture2D>(EntryIcon->Background.GetResourceObject());

				UTEST_TRUE("Entry Icon Texture is valid", IsValid(EntryIconTexture))

				TArray<UTexture2D *> IconTextures;
				IconTextures.Emplace(UTexture2D::CreateTransient(256, 256));
				IconTextures.Emplace(UTexture2D::CreateTransient(256, 256));
				IconTextures.Emplace(UTexture2D::CreateTransient(256, 256));
				IconTextures.Emplace(UTexture2D::CreateTransient(256, 256));
				IconTextures.Emplace(UTexture2D::CreateTransient(256, 256));

				for (UTexture2D * & IconTexture : IconTextures)
				{
					View->SetIcon(IconTexture);

					EntryIconTexture = Cast<UTexture2D>(EntryIcon->Background.GetResourceObject());

					TEST_TRUE(EntryIconTexture == IconTexture)
				}

				return true;
			});

			It("Given a new entry value, expect the view to update its entry value", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UTextBlock * EntryValue = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("EntryValue")));

				UTEST_TRUE("Entry Value is valid", IsValid(EntryValue))

				TArray<FText> Values;
				Values.Emplace(FText::AsNumber(0.0f));
				Values.Emplace(FText::AsNumber(10.0f));
				Values.Emplace(FText::AsNumber(-62.61f));
				Values.Emplace(FText::AsNumber(78.35f));
				Values.Emplace(FText::AsNumber(6.81f));

				for (FText & Value : Values)
				{
					View->SetValue(Value);

					TEST_TRUE(EntryValue->GetText().EqualTo(Value))
				}

				return true;
			});

			It("Given a new entry progress, expect the view to update its entry progress", [this, ViewClass]()
			{
				View = CreateWidget<UBBDossierEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UProgressBar * EntryProgress = Cast<UProgressBar>(View->WidgetTree->FindWidget(TEXT("EntryProgressBar")));

				UTEST_TRUE("Entry Progress is valid", IsValid(EntryProgress))

				TArray<float> Progresses;
				Progresses.Emplace(0.0f);
				Progresses.Emplace(1.0f);
				Progresses.Emplace(0.26f);
				Progresses.Emplace(0.85f);
				Progresses.Emplace(0.57f);

				for (float & Progress : Progresses)
				{
					View->SetProgress(Progress);

					TEST_TRUE(EntryProgress->GetPercent() == Progress)
				}

				return true;
			});
		});
	}
}