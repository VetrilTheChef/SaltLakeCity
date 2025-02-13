// SaltLakeCity 4.25

#include "BBBuildEntryWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "IOC/BBIOC.h"

UBBBuildEntryWidget::UBBBuildEntryWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
}

EBBWidget UBBBuildEntryWidget::GetType() const
{
	return EBBWidget::BuildEntry;
}

void UBBBuildEntryWidget::SetEntryName(FText NewName)
{
	verifyf(IsValid(EntryButton), TEXT("Entry Button is invalid."));

	EntryButton->SetToolTipText(NewName);
}

void UBBBuildEntryWidget::SetIcon(UTexture2D * NewIcon)
{
	verifyf(IsValid(EntryIcon), TEXT("Entry Icon is invalid."));
	
	EntryIcon->SetBrushFromTexture(NewIcon);
}

void UBBBuildEntryWidget::SetPrice(float NewPrice)
{
	verifyf(IsValid(EntryPrice), TEXT("Entry Price is invalid."));

	EntryPrice->SetText(FText::FromString(FString::SanitizeFloat(NewPrice) + " $"));
}

void UBBBuildEntryWidget::SetTime(float NewTime)
{
	verifyf(IsValid(EntryTime), TEXT("Entry Time is invalid."));
	
	EntryTime->SetText(FText::FromString(FString::SanitizeFloat(NewTime) + " h"));
}

void UBBBuildEntryWidget::SetCommand(UIBBCommand * NewCommand)
{
	verifyf(IsValid(EntryButton), TEXT("Entry Button is invalid."));
	
	EntryButton->SetCommand(NewCommand);
}



void UBBBuildEntryWidget::NativeOnListItemObjectSet(UObject * ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);

	UIBBGameInstance * GameInstance = GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	AIBBHUD * HUD = GameInstance->GetHUD();

	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	const UIBBWidgetFactory * WidgetFactory = HUD->GetWidgetFactory();

	verifyf(IsValid(WidgetFactory), TEXT("Widget Factory is invalid."));

	UIBBBuildEntryWidget * Widget = this;

	WidgetFactory->NewBuildEntryWidget(Widget, Cast<UIBBBuildEntry>(ListItemObject));
}