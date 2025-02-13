// SaltLakeCity 4.27

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

void UBBDossierWidgetStub::CreateCharacterPreview(const AIBBCharacter * TemplateCharacter)
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

int UBBDossierWidgetStub::GetNumAttributeEntries()
{
	return AttributeEntries.Num();
}

UIBBDossierEntry * UBBDossierWidgetStub::GetAttributeEntry(int Index)
{
	return AttributeEntries[Index];
}

void UBBDossierWidgetStub::AddAttributeEntry(UIBBDossierEntry * NewEntry)
{
	AttributeEntries.Emplace(NewEntry);
}

int UBBDossierWidgetStub::GetNumNeedEntries()
{
	return NeedEntries.Num();
}

UIBBDossierEntry * UBBDossierWidgetStub::GetNeedEntry(int Index)
{
	return NeedEntries[Index];
}

void UBBDossierWidgetStub::AddNeedEntry(UIBBDossierEntry * NewEntry)
{
	NeedEntries.Emplace(NewEntry);
}

int UBBDossierWidgetStub::GetNumSkillEntries()
{
	return SkillEntries.Num();
}

UIBBDossierEntry * UBBDossierWidgetStub::GetSkillEntry(int Index)
{
	return SkillEntries[Index];
}

void UBBDossierWidgetStub::AddSkillEntry(UIBBDossierEntry * NewEntry)
{
	SkillEntries.Emplace(NewEntry);
}

UIBBTitleWidget * & UBBDossierWidgetStub::GetTitle()
{
	return Title;
}