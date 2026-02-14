// SaltLakeCity 5.7

#include "BBDossierEntryWidget.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Interfaces/IBBWidgetManager.h"

UBBDossierEntryWidget::UBBDossierEntryWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

EBBWidget UBBDossierEntryWidget::GetType() const
{
	return EBBWidget::DossierEntry;
}

void UBBDossierEntryWidget::AddToScreen(int32 ZOrder)
{
	AddToViewport(ZOrder);
}

void UBBDossierEntryWidget::SetEntryName(FText NewName)
{
	verifyf(IsValid(EntryName), TEXT("Entry Name is invalid."));

	EntryName->SetText(NewName);
}

void UBBDossierEntryWidget::SetIcon(UTexture2D* NewIcon)
{
	verifyf(IsValid(EntryIcon), TEXT("Entry Icon is invalid."));
	
	EntryIcon->SetBrushFromTexture(NewIcon);
}

void UBBDossierEntryWidget::SetValue(FText NewValue)
{
	verifyf(IsValid(EntryValue), TEXT("Entry Value is invalid."));

	EntryValue->SetText(NewValue);
}

void UBBDossierEntryWidget::SetProgress(float NewProgress)
{
	verifyf(IsValid(EntryProgressBar), TEXT("Entry Progress Bar is invalid."));

	EntryProgressBar->SetPercent(NewProgress);
}



void UBBDossierEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);

	UIBBGameInstance* GameInstance = GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	UIBBWidgetManager* WidgetManager = GameInstance->GetWidgetManager();

	verifyf(IsValid(WidgetManager), TEXT("Widget Manager is invalid."));

	const UIBBWidgetFactory* WidgetFactory = WidgetManager->GetWidgetFactory();

	verifyf(IsValid(WidgetFactory), TEXT("Widget Factory is invalid."));

	UIBBDossierEntryWidget* Widget = this;

	WidgetFactory->NewDossierEntryWidget(Widget, Cast<UIBBDossierEntry>(ListItemObject));
}