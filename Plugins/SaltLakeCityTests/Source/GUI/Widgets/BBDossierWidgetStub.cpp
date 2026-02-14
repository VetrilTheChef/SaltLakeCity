// SaltLakeCity 5.7

#include "BBDossierWidgetStub.h"

UBBDossierWidgetStub::UBBDossierWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	DisplayName = FText::FromString("");

	AttributeEntries.Empty();
	NeedEntries.Empty();
	SkillEntries.Empty();
}

void UBBDossierWidgetStub::NativeDestruct()
{
	AttributeEntries.Empty();
	NeedEntries.Empty();
	SkillEntries.Empty();

	DisplayName = FText::FromString("");

	Super::NativeDestruct();
}

void UBBDossierWidgetStub::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

EBBWidget UBBDossierWidgetStub::GetType() const
{
	return EBBWidget::Dossier;
}

void UBBDossierWidgetStub::AddToScreen(int32 ZOrder)
{
}

void UBBDossierWidgetStub::CreateCharacterPreview(const AIBBCharacter* TemplateCharacter)
{
}

void UBBDossierWidgetStub::DestroyCharacterPreview()
{
}

FText UBBDossierWidgetStub::GetDisplayName()
{
	return DisplayName;
}

void UBBDossierWidgetStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}

TArray<UIBBDossierEntry*> UBBDossierWidgetStub::GetAttributeEntries() const
{
	return AttributeEntries;
}

void UBBDossierWidgetStub::AddAttributeEntry(UIBBDossierEntry* NewEntry)
{
	AttributeEntries.Emplace(NewEntry);
}

TArray<UIBBDossierEntry*> UBBDossierWidgetStub::GetNeedEntries() const
{
	return NeedEntries;
}

void UBBDossierWidgetStub::AddNeedEntry(UIBBDossierEntry* NewEntry)
{
	NeedEntries.Emplace(NewEntry);
}

TArray<UIBBDossierEntry*> UBBDossierWidgetStub::GetSkillEntries() const
{
	return SkillEntries;
}

void UBBDossierWidgetStub::AddSkillEntry(UIBBDossierEntry* NewEntry)
{
	SkillEntries.Emplace(NewEntry);
}

UIBBTitleWidget*& UBBDossierWidgetStub::GetTitle()
{
	return Title;
}