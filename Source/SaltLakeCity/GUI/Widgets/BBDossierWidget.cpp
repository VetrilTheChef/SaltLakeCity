// SaltLakeCity 5.7

#include "BBDossierWidget.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "Actors/Previews/Interfaces/IBBCharacterPreview.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "GUI/Components/BBRadioBox.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "Levels/Interfaces/IBBLevelScriptActor.h"
#include "Styling/SlateBrush.h"


UBBDossierWidget::UBBDossierWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	CharacterPreview = nullptr;
	Character = nullptr;

	NumberFormat.SetUseGrouping(true);
	NumberFormat.SetMinimumFractionalDigits(0);
	NumberFormat.SetMaximumFractionalDigits(0);
	NumberFormat.SetMinimumIntegralDigits(0);

	Tabs.Empty();
	Bodies.Empty();

	EntryLists.Empty();
	EntryLists.Emplace(StaticEnum<EBBAttribute>(), AttributeEntries);
	EntryLists.Emplace(StaticEnum<EBBNeed>(), NeedEntries);
	EntryLists.Emplace(StaticEnum<EBBSkill>(), SkillEntries);
}

void UBBDossierWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeTabs();
	InitializeBodies();
}

void UBBDossierWidget::NativeDestruct()
{
	AttributeEntries->ClearListItems();
	NeedEntries->ClearListItems();
	SkillEntries->ClearListItems();
	TraitsList->ClearListItems();
	EquipmentList->ClearListItems();

	DestroyCharacterPreview();
	FinalizeTabs();
	FinalizeBodies();

	Super::NativeDestruct();
}

EBBWidget UBBDossierWidget::GetType() const
{
	return EBBWidget::Dossier;
}

void UBBDossierWidget::AddToScreen(int32 ZOrder)
{
	AddToViewport(ZOrder);
}

void UBBDossierWidget::CreateCharacterPreview(const AIBBCharacter* TemplateCharacter)
{
	verifyf(IsValid(TemplateCharacter), TEXT("Template Character is invalid."));

	UWorld* World = TemplateCharacter->GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	AIBBLevelScriptActor* LevelScriptActor = Cast<AIBBLevelScriptActor>(World->GetLevelScriptActor());

	verifyf(IsValid(LevelScriptActor), TEXT("Preview Streaming Level is invalid."));

	ULevel* PreviewLevel = LevelScriptActor->GetPreviewLevel();

	verifyf(IsValid(PreviewLevel), TEXT("Preview Level is invalid."));

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.OverrideLevel = PreviewLevel;

	Character = World->SpawnActor<AIBBCharacterPreview>(CharacterPreviewClass.LoadSynchronous(), SpawnParams);

	verifyf(IsValid(Character), TEXT("Character is invalid."));

	Character->CreatePreview(TemplateCharacter);

	Character->ShowActors(PreviewLevel->Actors);

	verifyf(IsValid(CharacterPreview), TEXT("Character Preview is invalid."));

	//const FSlateBrush& Brush = CharacterPreview->GetBrush();

	CharacterPreview->Brush.ImageType = ESlateBrushImageType::FullColor;
	CharacterPreview->Brush.SetResourceObject(Character->GetPreview());
}

void UBBDossierWidget::DestroyCharacterPreview()
{
	CharacterPreview->Brush.SetResourceObject(nullptr);
	CharacterPreview->Brush.ImageType = ESlateBrushImageType::NoImage;

	if (IsValid(Character))
	{
		UWorld* World = Character->GetWorld();

		verifyf(IsValid(World), TEXT("World is invalid."));

		World->DestroyActor(Character);
	}

	Character = nullptr;
}

void UBBDossierWidget::SetDisplayName(FText NewDisplayName)
{
	verifyf(IsValid(DisplayNameText), TEXT("Display Name Text is invalid."));

	DisplayNameText->SetText(NewDisplayName);
}

void UBBDossierWidget::AddAttributeEntry(UIBBDossierEntry* NewEntry)
{
	verifyf(IsValid(AttributeEntries), TEXT("Attribute Entries is invalid."));
	
	AttributeEntries->AddItem(NewEntry);
}

void UBBDossierWidget::AddNeedEntry(UIBBDossierEntry* NewEntry)
{
	verifyf(IsValid(NeedEntries), TEXT("Need Entries is invalid."));

	NeedEntries->AddItem(NewEntry);
}

void UBBDossierWidget::AddSkillEntry(UIBBDossierEntry* NewEntry)
{
	verifyf(IsValid(SkillEntries), TEXT("Skill Entries is invalid."));

	SkillEntries->AddItem(NewEntry);
}

UIBBTitleWidget*& UBBDossierWidget::GetTitle()
{
	return Title;
}



void UBBDossierWidget::InitializeTabs()
{
	Tabs.Empty();

	Tabs.Emplace(Tab0);
	Tabs.Emplace(Tab1);
	Tabs.Emplace(Tab2);
	Tabs.Emplace(Tab3);

	for (int TabIndex = 0; TabIndex < Tabs.Num(); TabIndex++)
	{
		UIBBRadioBox* Tab = Tabs[TabIndex];

		verifyf(IsValid(Tab), TEXT("Tab is invalid."));

		Tab->Initialize(TabIndex);
		Tab->OnRadioStateChanged().AddUObject(this, &UBBDossierWidget::ChangeRadioState);
	}

	Tabs[0]->SetIsChecked(true);
	ChangeRadioState(0);
}

void UBBDossierWidget::FinalizeTabs()
{
	for (UIBBRadioBox*& Tab : Tabs)
	{
		if (IsValid(Tab))
		{
			Tab->OnRadioStateChanged().RemoveAll(this);
			Tab->Finalize();
		}

		Tab = nullptr;
	}

	Tabs.Empty();
}

void UBBDossierWidget::InitializeBodies()
{
	Bodies.Empty();

	Bodies.Emplace(Body0);
	Bodies.Emplace(Body1);
	Bodies.Emplace(Body2);
	Bodies.Emplace(Body3);

	verifyf(IsValid(BodySwitcher), TEXT("Bodies Switcher is invalid."));

	BodySwitcher->SetActiveWidgetIndex(0);
}

void UBBDossierWidget::FinalizeBodies()
{
	Bodies.Empty();
}

void UBBDossierWidget::SetAttributeText(UTextBlock* AttributeTextBlock, float AttributeValue)
{
	verifyf(IsValid(AttributeTextBlock), TEXT("Attribute Text Block is invalid."));

	FText AttributeText = FText::Format(
		NSLOCTEXT("BBDossierAttributeText", "DossierAttributeFormatString", "{0}"),
		FText::AsNumber(AttributeValue, &NumberFormat)
	);

	AttributeTextBlock->SetText(AttributeText);
}

void UBBDossierWidget::ToggleCharacterPreview(bool bVisible)
{
	verifyf(IsValid(Character), TEXT("Character is invalid."));

	Character->SetActorTickEnabled(bVisible);
}

void UBBDossierWidget::ChangeRadioState(int Index)
{
	for (int TabIndex = 0; TabIndex < Tabs.Num(); TabIndex++)
	{
		bool Checked = (TabIndex == Index);

		UIBBRadioBox* RadioBox = Tabs[TabIndex];

		verifyf(IsValid(RadioBox), TEXT("Radio Box is invalid."));

		RadioBox->SetIsEnabled(!Checked);

		// Do not set the checked state if the radio box is the one which
		// broadcasted the event, otherwise the code will loop
		if (!Checked)
		{
			RadioBox->SetIsChecked(false);
		}
	}

	verifyf(IsValid(BodySwitcher), TEXT("Bodies Switcher is invalid."));

	BodySwitcher->SetActiveWidgetIndex(Index);
}