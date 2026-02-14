// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/Controllers/BBOrderBuildCommandStub.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "GUI/Controllers/BBBuildEntryControllerStub.h"
#include "GUI/Widgets/BBBuildEntryWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBBuildEntryWidgetSpec,
	"SaltLakeCity.GUI.Widgets.BuildEntry",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBBuildEntryControllerStub * Controller = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBOrderBuildCommandStub * OrderBuildCommand = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBBuildEntryWidget * View = nullptr;

END_DEFINE_SPEC(UBBBuildEntryWidgetSpec)

void UBBBuildEntryWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildEntryWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = NewObject<UBBBuildEntryControllerStub>(TestWorld, UBBBuildEntryControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("CommandFactory is valid", IsValid(CommandFactory))

		OrderBuildCommand = NewObject<UBBOrderBuildCommandStub>(CommandFactory, UBBOrderBuildCommandStub::StaticClass());

		UTEST_TRUE("OrderBuildCommand is valid", IsValid(OrderBuildCommand))

		CommandFactory->AddOrderBuildCommand(OrderBuildCommand);

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		Controller = nullptr;
		View = nullptr;

		OrderBuildCommand = nullptr;
		CommandFactory = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new name, expect the view to update the name", [this, ViewClass]()
			{
				View = CreateWidget<UBBBuildEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				Controller->Initialize(View, nullptr, CommandFactory);

				UIBBButton * EntryButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("EntryButton")));

				UTEST_TRUE("Entry Button is valid", IsValid(EntryButton))

				TArray<FText> Names;
				Names.Empty();

				Names.Emplace(FText::FromString("SOME ENTRY"));
				Names.Emplace(FText::FromString("ANOTHER ENTRY"));
				Names.Emplace(FText::FromString("NUMBERS 1528142"));
				Names.Emplace(FText::FromString("%28t5GB9172f!"));
				Names.Emplace(FText::FromString("_-_-_-___--"));

				for (FText & Name : Names)
				{
					View->SetEntryName(Name);

					TEST_TRUE(EntryButton->ToolTipText.EqualTo(Name))
				}

				Names.Empty();

				Controller->Finalize();

				return true;
			});

			It("Given a new icon, expect the view to update the icon", [this, ViewClass]()
			{
				View = CreateWidget<UBBBuildEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				Controller->Initialize(View, nullptr, CommandFactory);

				UBorder * EntryIcon = Cast<UBorder>(View->WidgetTree->FindWidget(TEXT("EntryIcon")));

				UTEST_TRUE("Entry Icon is valid", IsValid(EntryIcon))

				TArray<UTexture2D *> Icons;
				Icons.Empty();

				for (int i = 0; i < 5; i++)
				{
					UTexture2D * Icon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
					Icon->AddToRoot();

					Icons.Emplace(Icon);
				}

				for (UTexture2D * & Icon : Icons)
				{
					View->SetIcon(Icon);

					TEST_TRUE(Cast<UTexture2D>(EntryIcon->Background.GetResourceObject()) == Icon)
				}

				for (UTexture2D * & Icon : Icons)
				{
					if (IsValid(Icon))
					{
						Icon->RemoveFromRoot();
						Icon->MarkAsGarbage();
					}

					Icon = nullptr;
				}

				Icons.Empty();

				Controller->Finalize();

				return true;
			});

			It("Given a new price, expect the view to update the price", [this, ViewClass]()
			{
				View = CreateWidget<UBBBuildEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				Controller->Initialize(View, nullptr, CommandFactory);

				UTextBlock * EntryPrice = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("EntryPrice")));

				UTEST_TRUE("Entry Price is valid", IsValid(EntryPrice))

				TArray<float> Prices;
				Prices.Empty();

				Prices.Emplace(24.0f);
				Prices.Emplace(10.0f);
				Prices.Emplace(-454.0f);
				Prices.Emplace(12.0f);
				Prices.Emplace(1621.0f);

				for (float & Price : Prices)
				{
					View->SetPrice(Price);

					TEST_TRUE(EntryPrice->GetText().EqualTo(FText::FromString(FString::SanitizeFloat(Price) + " $")))
				}

				Prices.Empty();

				Controller->Finalize();

				return true;
			});

			It("Given a new time, expect the view to update the time", [this, ViewClass]()
			{
				View = CreateWidget<UBBBuildEntryWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				Controller->Initialize(View, nullptr, CommandFactory);

				UTextBlock * EntryTime = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("EntryTime")));

				UTEST_TRUE("Entry Time is valid", IsValid(EntryTime))

				TArray<float> Times;
				Times.Empty();

				Times.Emplace(3000.0f);
				Times.Emplace(-105.0f);
				Times.Emplace(523.523f);
				Times.Emplace(1.5f);
				Times.Emplace(-25.0f);

				for (float & Time : Times)
				{
					View->SetTime(Time);

					TEST_TRUE(EntryTime->GetText().EqualTo(FText::FromString(FString::SanitizeFloat(Time) + " h")))
				}

				Times.Empty();

				Controller->Finalize();

				return true;
			});
		});
	}
}