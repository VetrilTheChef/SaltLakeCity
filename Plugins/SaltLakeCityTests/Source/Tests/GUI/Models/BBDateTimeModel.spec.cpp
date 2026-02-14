// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/Components/BBGameClockStub.h"
#include "GameStates/Components/Interfaces/IBBGameClock.h"
#include "GUI/Models/BBDateTimeModel.h"
#include "GUI/Widgets/BBDateTimeWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBDateTimeModelSpec,
	"SaltLakeCity.GUI.Models.DateTime",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBDateTimeWidgetStub * View = nullptr;

	UPROPERTY()
	UBBGameClockStub * Clock = nullptr;

	UPROPERTY()
	TArray<FText> Dates;

	UPROPERTY()
	TArray<FText> Times;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBDateTimeModel * Model = nullptr;

END_DEFINE_SPEC(UBBDateTimeModelSpec)

void UBBDateTimeModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDateTimeModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	Dates.Empty();
	Dates.Emplace(FText::FromString("04-03-45"));
	Dates.Emplace(FText::FromString("15-01-71"));
	Dates.Emplace(FText::FromString("30-12-20"));
	Dates.Emplace(FText::FromString("00000000"));
	Dates.Emplace(FText::FromString("A(%Y-)(!"));

	Times.Empty();
	Times.Emplace(FText::FromString("15:47"));
	Times.Emplace(FText::FromString("23:59"));
	Times.Emplace(FText::FromString("10:04"));
	Times.Emplace(FText::FromString("-0123"));
	Times.Emplace(FText::FromString("//AC%"));

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		View = CreateWidget<UBBDateTimeWidgetStub>(TestWorld, UBBDateTimeWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		Clock = NewObject<UBBGameClockStub>(TestWorld, UBBGameClockStub::StaticClass());

		UTEST_TRUE("Clock is valid", IsValid(Clock))

		return true;
	});

	AfterEach([this]()
	{
		Clock = nullptr;

		View = nullptr;

		Model = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("["+ModelClass->GetName()+"]", [this, ModelClass]()
		{
			It("Given a date update from the clock, expect the model to update the view", [this, ModelClass]()
			{
				Model = NewObject<UBBDateTimeModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				Model->Initialize(View, Clock);

				for (FText & Date : Dates)
				{
					View->SetDate(FText::FromString(""));

					TEST_TRUE(View->GetDate().EqualTo(FText::FromString("")))

					Clock->UpdateDate(Date);

					TEST_TRUE(View->GetDate().EqualTo(Date))
				}

				Model->Finalize();

				return true;
			});

			It("Given a date update from the finalized clock, expect the model not to update the view", [this, ModelClass]()
			{
				Model = NewObject<UBBDateTimeModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				Model->Initialize(View, Clock);
				Model->Finalize();

				for (FText & Date : Dates)
				{
					View->SetDate(FText::FromString(""));

					TEST_TRUE(View->GetDate().EqualTo(FText::FromString("")))

					Clock->UpdateDate(Date);

					TEST_TRUE(View->GetDate().EqualTo(FText::FromString("")))
				}

				return true;
			});

			It("Given a time update from the clock, expect the model to update the view", [this, ModelClass]()
			{
				Model = NewObject<UBBDateTimeModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				Model->Initialize(View, Clock);

				for (FText & Time : Times)
				{
					View->SetTime(FText::FromString(""));

					TEST_TRUE(View->GetTime().EqualTo(FText::FromString("")))

					Clock->UpdateTime(Time);

					TEST_TRUE(View->GetTime().EqualTo(Time))
				}

				Model->Finalize();

				return true;
			});

			It("Given a time update from the finalized clock, expect the model not to update the view", [this, ModelClass]()
			{
				Model = NewObject<UBBDateTimeModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				Model->Initialize(View, Clock);
				Model->Finalize();

				for (FText & Time : Times)
				{
					View->SetTime(FText::FromString(""));

					TEST_TRUE(View->GetTime().EqualTo(FText::FromString("")))

					Clock->UpdateTime(Time);

					TEST_TRUE(View->GetTime().EqualTo(FText::FromString("")))
				}

				return true;
			});
		});
	}
}