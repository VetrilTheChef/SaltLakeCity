// SaltLakeCity 4.27

#include "BBDossierEntryWidget.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "IOC/BBIOC.h"

UBBDossierEntryWidget::UBBDossierEntryWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
}

EBBWidget UBBDossierEntryWidget::GetType() const
{
	return EBBWidget::DossierEntry;
}

void UBBDossierEntryWidget::SetEntryName(FText NewName)
{
	verifyf(IsValid(EntryName), TEXT("Entry Name is invalid."));

	EntryName->SetText(NewName);
}

void UBBDossierEntryWidget::SetIcon(UTexture2D * NewIcon)
{
	verifyf(IsValid(EntryIcon), TEXT("Entry Icon is invalid."));
	
	EntryIcon->SetBrushFromTexture(NewIcon);
}

void UBBDossierEntryWidget::SetValue(float NewValue)
{
	verifyf(IsValid(EntryValue), TEXT("Entry Value is invalid."));

	EntryValue->SetText(FText::FromString(FString::SanitizeFloat(NewValue)));

	UpdateProgressBar();
}

void UBBDossierEntryWidget::SetMaxValue(float NewMaxValue)
{
	verifyf(IsValid(EntryMaxValue), TEXT("Entry Max Value is invalid."));
	
	EntryMaxValue->SetText(FText::FromString(FString::SanitizeFloat(NewMaxValue)));

	UpdateProgressBar();
}



void UBBDossierEntryWidget::NativeOnListItemObjectSet(UObject * ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);

	UIBBGameInstance * GameInstance = GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	AIBBHUD * HUD = GameInstance->GetHUD();

	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	const UIBBWidgetFactory * WidgetFactory = HUD->GetWidgetFactory();

	verifyf(IsValid(WidgetFactory), TEXT("Widget Factory is invalid."));

	UIBBDossierEntryWidget * Widget = this;

	WidgetFactory->NewDossierEntryWidget(Widget, Cast<UIBBDossierEntry>(ListItemObject));
}

void UBBDossierEntryWidget::UpdateProgressBar()
{
	verifyf(IsValid(EntryValue), TEXT("Entry Value is invalid."));
	verifyf(IsValid(EntryMaxValue), TEXT("Entry Max Value is invalid."));
	verifyf(IsValid(EntryProgressBar), TEXT("Entry Progress Bar is invalid."));

	float Value = FCString::Atof(* (EntryValue->GetText()).ToString());
	float MaxValue = FCString::Atof(* (EntryMaxValue->GetText()).ToString());

	EntryProgressBar->SetPercent(Value / MaxValue);
}