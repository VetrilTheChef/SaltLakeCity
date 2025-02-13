// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
#include "Commands/Jobs/BBSetJobCommandStub.h"
#include "Commands/Metacommands/BBCompositeCommandStub.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "GUI/Controllers/BBJobControllerStub.h"
#include "GUI/Widgets/BBJobWidget.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBJobWidgetSpec, "SaltLakeCity.GUI.Widgets.Job", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	TArray<FText> Names;

	UPROPERTY()
	TArray<EBBJob> Jobs;

	UPROPERTY()
	TArray<FText> JobNames;

	UPROPERTY()
	TArray<FText> JobTooltips;

	UPROPERTY()
	UBBCompositeCommandStub * AcceptCommand = nullptr;

	UPROPERTY()
	UBBCloseWidgetCommandStub * CancelCommand = nullptr;

	UPROPERTY()
	UBBJobControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBJobWidget * View = nullptr;

END_DEFINE_SPEC(UBBJobWidgetSpec)

void UBBJobWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBJobWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	Names.Empty();
	Names.Emplace(FText::FromString("NAME EXAMPLE"));
	Names.Emplace(FText::FromString("a random name"));
	Names.Emplace(FText::FromString("198t!&h2$GHA"));
	Names.Emplace(FText::FromString("          "));
	Names.Emplace(FText::FromString("_BiZ4Rr0_n4m3!_"));

	Jobs.Empty();
	Jobs.Emplace(EBBJob::Builder);
	Jobs.Emplace(EBBJob::None);
	Jobs.Emplace(EBBJob::Idle);

	JobNames.Empty();
	JobNames.Emplace(FText::FromString("A JOB"));
	JobNames.Emplace(FText::FromString("invalid"));
	JobNames.Emplace(FText::FromString("%_2f5!&51a"));

	JobTooltips.Empty();
	JobTooltips.Emplace(FText::FromString("A description"));
	JobTooltips.Emplace(FText::FromString("   ___   ___"));
	JobTooltips.Emplace(FText::FromString("51v QTYG8E!"));

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		Controller = NewObject<UBBJobControllerStub>(TestWorld, UBBJobControllerStub::StaticClass());

		AcceptCommand = NewObject<UBBCompositeCommandStub>(Controller, UBBCompositeCommandStub::StaticClass());

		UTEST_TRUE("Accept Command is valid", IsValid(AcceptCommand))

		CancelCommand = NewObject<UBBCloseWidgetCommandStub>(Controller, UBBCloseWidgetCommandStub::StaticClass());

		UTEST_TRUE("Cancel Command is valid", IsValid(CancelCommand))

		Controller->SetViewCommands(AcceptCommand, CancelCommand);

		return true;
	});

	AfterEach([this]()
	{

		AcceptCommand = nullptr;
		CancelCommand = nullptr;

		Controller = nullptr;
		View = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new display name, expect the view to update its display name", [this, ViewClass]()
			{
				View = CreateWidget<UBBJobWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr, nullptr);

				UTextBlock * NameText = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("NameText")));

				UTEST_TRUE("Name Text is valid", IsValid(NameText))

				for (FText & Name : Names)
				{
					View->SetDisplayName(Name);

					TEST_TRUE(NameText->GetText().EqualTo(Name))
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new job, expect the view to add it to the jobs list", [this, ViewClass]()
			{
				View = CreateWidget<UBBJobWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr, nullptr);

				UComboBoxString * JobComboBox = Cast<UComboBoxString>(View->WidgetTree->FindWidget(TEXT("JobComboBox")));

				UTEST_TRUE("Job Combo Box is valid", IsValid(JobComboBox))

				for (int Index = 0; Index < 3; Index++)
				{
					View->AddJob(Jobs[Index], JobNames[Index], JobTooltips[Index]);

					TEST_TRUE(JobComboBox->GetOptionAtIndex(Index) == JobNames[Index].ToString())
				}

				Controller->Finalize();

				return true;
			});

			It("Given a job to be set, expect the view to select it in the jobs list", [this, ViewClass]()
			{
				View = CreateWidget<UBBJobWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr, nullptr);

				UComboBoxString * JobComboBox = Cast<UComboBoxString>(View->WidgetTree->FindWidget(TEXT("JobComboBox")));

				UTEST_TRUE("Job Combo Box is valid", IsValid(JobComboBox))

				for (int Index = 0; Index < 3; Index++)
				{
					View->AddJob(Jobs[Index], JobNames[Index], JobTooltips[Index]);
				}

				for (int Index = 0; Index < 3; Index++)
				{
					View->SetJob(Jobs[Index]);

					TEST_TRUE(JobComboBox->GetSelectedOption() == JobNames[Index].ToString())
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new accept command, expect the view to execute it when the accept button is clicked", [this, ViewClass]()
			{
				View = CreateWidget<UBBJobWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr, nullptr);

				UIBBButton * AcceptButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("AcceptButton")));

				UTEST_TRUE("Accept Button is valid", IsValid(AcceptButton))

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					AcceptButton->OnClicked.Broadcast();

					TEST_TRUE(AcceptCommand->GetNumExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new cancel command, expect the view to execute it when the cancel button is clicked", [this, ViewClass]()
			{
				View = CreateWidget<UBBJobWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr, nullptr);

				UIBBButton * CancelButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("CancelButton")));

				UTEST_TRUE("Cancel Button is valid", IsValid(CancelButton))

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					CancelButton->OnClicked.Broadcast();

					TEST_TRUE(CancelCommand->GetNumExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}