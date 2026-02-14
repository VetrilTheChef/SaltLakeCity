// SaltLakeCity 5.7

#include "BBBuildEntryWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"

UBBBuildEntryWidget::UBBBuildEntryWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

EBBWidget UBBBuildEntryWidget::GetType() const
{
	return EBBWidget::BuildEntry;
}

void UBBBuildEntryWidget::AddToScreen(int32 ZOrder)
{
	AddToViewport(ZOrder);
}

void UBBBuildEntryWidget::SetEntryName(FText NewName)
{
	verifyf(IsValid(EntryButton), TEXT("Entry Button is invalid."));

	EntryButton->SetToolTipText(NewName);
}

void UBBBuildEntryWidget::SetIcon(UTexture2D* NewIcon)
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

void UBBBuildEntryWidget::SetCommand(UIBBCommand* NewCommand)
{
	verifyf(IsValid(EntryButton), TEXT("Entry Button is invalid."));
	
	EntryButton->SetCommand(NewCommand);
}



void UBBBuildEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);

	UIBBGameInstance* GameInstance = GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	UIBBWidgetManager* WidgetManager = GameInstance->GetWidgetManager();

	verifyf(IsValid(WidgetManager), TEXT("Widget Manager is invalid."));

	const UIBBWidgetFactory* WidgetFactory = WidgetManager->GetWidgetFactory();

	verifyf(IsValid(WidgetFactory), TEXT("Widget Factory is invalid."));

	UIBBBuildEntryWidget* Widget = this;

	WidgetFactory->NewBuildEntryWidget(Widget, Cast<UIBBBuildEntry>(ListItemObject));
}