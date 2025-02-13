// SaltLakeCity 4.26

#include "BBBuildWidget.h"
#include "Abilities/Player/Interfaces/IBBOrderBuildAbility.h"
#include "Components/TileView.h"
#include "Components/WidgetSwitcher.h"
#include "GUI/Components/BBRadioBox.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"

UBBBuildWidget::UBBBuildWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Tabs.Empty();
	Tiles.Empty();
}

void UBBBuildWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeTabs();
	InitializeTiles();
}

void UBBBuildWidget::NativeDestruct()
{
	FinalizeTabs();
	FinalizeTiles();

	Super::NativeDestruct();
}

EBBWidget UBBBuildWidget::GetType() const
{
	return EBBWidget::Build;
}

void UBBBuildWidget::AddEntry(EBBBuildCategory Category, UIBBBuildEntry * & NewEntry)
{
	if (Tiles.Contains(Category))
	{
		UTileView * CategoryTile = Tiles.FindRef(Category);

		verifyf(IsValid(CategoryTile), TEXT("Category Tile is invalid."))

		CategoryTile->AddItem(NewEntry);
	}
}

void UBBBuildWidget::ClearEntries(EBBBuildCategory Category)
{
	if (Tiles.Contains(Category))
	{
		UTileView * CategoryTile = Tiles.FindRef(Category);

		verifyf(IsValid(CategoryTile), TEXT("Category Tile is invalid."))

		CategoryTile->ClearListItems();
	}
}



void UBBBuildWidget::InitializeTabs()
{
	Tabs.Empty();

	Tabs.Emplace(EBBBuildCategory::Foundation, Tab0);
	Tabs.Emplace(EBBBuildCategory::Outdoors, Tab1);
	Tabs.Emplace(EBBBuildCategory::Indoors, Tab2);
	Tabs.Emplace(EBBBuildCategory::Customization, Tab3);

	for (TPair<EBBBuildCategory, UIBBRadioBox *> & Tab : Tabs)
	{
		UIBBRadioBox * RadioBox = Tab.Value;

		verifyf(IsValid(RadioBox), TEXT("Radio Box is invalid."));

		RadioBox->Initialize((int)(Tab.Key));
		RadioBox->OnRadioStateChanged().AddUObject(this, &UBBBuildWidget::ChangeRadioState);
	}
}

void UBBBuildWidget::InitializeTiles()
{
	Tiles.Empty();

	Tiles.Emplace(EBBBuildCategory::Foundation, Tile0);
	Tiles.Emplace(EBBBuildCategory::Outdoors, Tile1);
	Tiles.Emplace(EBBBuildCategory::Indoors, Tile2);
	Tiles.Emplace(EBBBuildCategory::Customization, Tile3);
}

void UBBBuildWidget::FinalizeTabs()
{
	for (TPair<EBBBuildCategory, UIBBRadioBox *> & Tab : Tabs)
	{
		UIBBRadioBox * RadioBox = Tab.Value;

		if (IsValid(RadioBox))
		{
			RadioBox->OnRadioStateChanged().RemoveAll(this);
			RadioBox->Finalize();
		}

		Tab.Value = nullptr;
	}

	Tabs.Empty();
}

void UBBBuildWidget::FinalizeTiles()
{
	Tiles.Empty();
}

void UBBBuildWidget::ChangeRadioState(int Index)
{
	for (int TabIndex = 0; TabIndex < Tabs.Num(); TabIndex++)
	{
		bool Checked = (TabIndex == Index);

		UIBBRadioBox * RadioBox = Tabs[(EBBBuildCategory)TabIndex];

		verifyf(IsValid(RadioBox), TEXT("Radio Box is invalid."));

		RadioBox->SetIsEnabled(!Checked);

		// Do not set the checked state if the radio box is the one which
		// broadcasted the event, otherwise the code will loop
		if (!Checked)
		{
			RadioBox->SetIsChecked(false);
		}
	}
}