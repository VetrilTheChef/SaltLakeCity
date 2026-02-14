// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/GUI/BBOpenWidgetCommandStub.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "GUI/Controllers/BBContextControllerStub.h"
#include "GUI/Widgets/BBContextRowWidget.h"
#include "GUI/Widgets/BBContextWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBContextRowWidgetSpec,
	"SaltLakeCity.GUI.Widgets.ContextRow",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	TArray<FText> Names;

	UPROPERTY()
	TArray<UTexture2D *> Icons;

	UPROPERTY()
	TArray<FText> Tooltips;

	UPROPERTY()
	UBBOpenWidgetCommandStub * OpenCommand = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBContextRowWidget * View = nullptr;

END_DEFINE_SPEC(UBBContextRowWidgetSpec)

void UBBContextRowWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBContextRowWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	Names.Empty();
	Names.Emplace(FText::FromString("ROW NAME"));
	Names.Emplace(FText::FromString("SOME ACTION"));
	Names.Emplace(FText::FromString("$&21___1h"));
	Names.Emplace(FText::FromString("        "));
	Names.Emplace(FText::FromString("LAST OPTION"));

	Tooltips.Empty();
	Tooltips.Emplace(FText::FromString("This is a tooltip."));
	Tooltips.Emplace(FText::FromString("Row Description."));
	Tooltips.Emplace(FText::FromString("_______136531"));
	Tooltips.Emplace(FText::FromString("          "));
	Tooltips.Emplace(FText::FromString("ANOTHER TOOLTIP."));

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		OpenCommand = NewObject<UBBOpenWidgetCommandStub>(TestWorld, UBBOpenWidgetCommandStub::StaticClass());

		UTEST_TRUE("Open Command is valid", IsValid(OpenCommand))

		Icons.Empty();

		for (int i = 0; i < 5; i++)
		{
			UTexture2D * Icon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
			Icon->AddToRoot();

			Icons.Emplace(Icon);
		}

		return true;
	});

	AfterEach([this]()
	{
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

		OpenCommand = nullptr;

		View = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new command, expect the view to execute it when clicked", [this, ViewClass]()
			{
				UBBContextWidgetStub * ParentView = CreateWidget<UBBContextWidgetStub>(TestWorld, UBBContextWidgetStub::StaticClass());

				UTEST_TRUE("Parent View is valid", IsValid(ParentView))
				
				View = CreateWidget<UBBContextRowWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				View->SetCommand(OpenCommand);

				UIBBButton * RowButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("RowButton")));

				UTEST_TRUE("Row Button is valid", IsValid(RowButton))

				UIBBContextRowWidget * RowWidget = Cast<UIBBContextRowWidget>(View);

				UTEST_TRUE("Row Widget is valid", IsValid(RowWidget))

				ParentView->AddRow(RowWidget);

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					RowButton->OnClicked.Broadcast();

					TEST_TRUE(OpenCommand->GetNumExecutions() == Clicks)
				}

				return true;
			});

			It("Given a new clicked event, expect the parent controller to close the parent view", [this, ViewClass]()
			{
				View = CreateWidget<UBBContextRowWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UBBContextControllerStub * ParentController = NewObject<UBBContextControllerStub>(TestWorld, UBBContextControllerStub::StaticClass());

				UTEST_TRUE("Parent Controller is valid", IsValid(ParentController))

				ParentController->Initialize(nullptr, nullptr, nullptr, nullptr);

				ParentController->AddRow(View);

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					View->OnClicked().Broadcast();

					TEST_TRUE(ParentController->GetNumRowClickExecutions() == Clicks)
				}

				ParentController->ClearRows();

				ParentController->Finalize();

				return true;
			});

			It("Given a new name, expect the view to update its name", [this, ViewClass]()
			{
				View = CreateWidget<UBBContextRowWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UTextBlock * RowText = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("RowText")));

				UTEST_TRUE("Row Text is valid", IsValid(RowText))

				for (int Index = 0; Index < Names.Num(); Index++)
				{
					View->SetRowName(Names[Index]);

					TEST_TRUE(RowText->GetText().EqualTo(Names[Index]))
				}

				return true;
			});

			It("Given a new icon, expect the view to update its icon", [this, ViewClass]()
			{
				View = CreateWidget<UBBContextRowWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UImage * RowIcon = Cast<UImage>(View->WidgetTree->FindWidget(TEXT("RowIcon")));

				UTEST_TRUE("Row Icon is valid", IsValid(RowIcon))

				for (int Index = 0; Index < Icons.Num(); Index++)
				{
					View->SetRowIcon(Icons[Index]);

					TEST_TRUE(Cast<UTexture2D>(RowIcon->Brush.GetResourceObject()) == Icons[Index])
				}

				return true;
			});

			It("Given a new tooltip, expect the view to update its tooltip", [this, ViewClass]()
			{
				View = CreateWidget<UBBContextRowWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				UIBBButton * RowButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("RowButton")));

				UTEST_TRUE("Row Button is valid", IsValid(RowButton))

				for (int Index = 0; Index < Tooltips.Num(); Index++)
				{
					View->SetRowTooltip(Tooltips[Index]);

					TEST_TRUE(RowButton->ToolTipText.EqualTo(Tooltips[Index]))
				}

				return true;
			});
		});
	}
}