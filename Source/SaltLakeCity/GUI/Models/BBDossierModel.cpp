// SaltLakeCity 4.27

#include "BBDossierModel.h"
#include "AbilitySystemComponent.h"
#include "Attributes/Interfaces/IBBAttributeSet.h"
#include "Attributes/Interfaces/IBBNeedSet.h"
#include "Attributes/Interfaces/IBBSkillSet.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "GUI/Data/BBAttributeRow.h"
#include "GUI/Data/BBNeedRow.h"
#include "GUI/Data/BBSkillRow.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"


UBBDossierModel::UBBDossierModel() :
	Super()
{
	View = nullptr;
	Character = nullptr;

	AttributeEntries.Empty();
	NeedEntries.Empty();
	SkillEntries.Empty();

	NeedDataToEnum.Empty();
	SkillDataToEnum.Empty();
	AttributeDataToEnum.Empty();
}

void UBBDossierModel::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBDossierModel::BeginDestroy()
{
	NeedDataToEnum.Empty();
	SkillDataToEnum.Empty();
	AttributeDataToEnum.Empty();

	AttributeEntries.Empty();
	NeedEntries.Empty();
	SkillEntries.Empty();

	Super::BeginDestroy();
}

TScriptInterface<IBBWidgetTarget> UBBDossierModel::GetWidgetTarget() const
{
	return TScriptInterface<IBBWidgetTarget>(Character);
}

UIBBWidget * UBBDossierModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBDossierModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBTargetedWidgetSpecification * DossierWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewDossierWidgetSpecification(DossierWidgetSpecification, this, GetWidgetTarget());

	verifyf(IsValid(DossierWidgetSpecification), TEXT("Dossier Widget Specification is invalid."));

	OnTargetUpdate().AddUObject(DossierWidgetSpecification, & UIBBTargetedWidgetSpecification::SetWidgetTarget);

	return DossierWidgetSpecification;
}

UDataTable * UBBDossierModel::GetAttributesDataTable() const
{
	return AttributesDataTable.LoadSynchronous();
}

UDataTable * UBBDossierModel::GetNeedsDataTable() const
{
	return NeedsDataTable.LoadSynchronous();
}

UDataTable * UBBDossierModel::GetSkillsDataTable() const
{
	return SkillsDataTable.LoadSynchronous();
}

void UBBDossierModel::Initialize(UIBBDossierWidget * NewView, AIBBCharacter * NewCharacter)
{
	InitializeView(NewView);
	InitializeCharacter(NewCharacter);
}

void UBBDossierModel::Finalize()
{
	FinalizeCharacter();
	FinalizeView();
}

const AIBBCharacter * UBBDossierModel::GetCharacter() const
{
	return Character;
}

FText UBBDossierModel::GetDisplayName() const
{
	return IsValid(Character) ? Character->GetDisplayName(EBBDisplayName::Full) : FText::FromString("");
}

float UBBDossierModel::GetValue(EBBAttribute Attribute) const
{
	UIBBDossierEntry * AttributeEntry = AttributeEntries.FindChecked(Attribute);

	verifyf(IsValid(AttributeEntry), TEXT("Attribute Entry is invalid."));

	return AttributeEntry->GetValue();
}

float UBBDossierModel::GetValue(EBBNeed Need) const
{
	UIBBDossierEntry * NeedEntry = NeedEntries.FindChecked(Need);

	verifyf(IsValid(NeedEntry), TEXT("Need Entry is invalid."));

	return NeedEntry->GetValue();
}

float UBBDossierModel::GetValue(EBBSkill Skill) const
{
	UIBBDossierEntry * SkillEntry = SkillEntries.FindChecked(Skill);

	verifyf(IsValid(SkillEntry), TEXT("Skill Entry is invalid."));

	return SkillEntry->GetValue();
}

float UBBDossierModel::GetMaxValue(EBBAttribute Attribute) const
{
	UIBBDossierEntry * AttributeEntry = AttributeEntries.FindChecked(Attribute);

	verifyf(IsValid(AttributeEntry), TEXT("Attribute Entry is invalid."));

	return AttributeEntry->GetMaxValue();
}

float UBBDossierModel::GetMaxValue(EBBNeed Need) const
{
	UIBBDossierEntry * NeedEntry = NeedEntries.FindChecked(Need);

	verifyf(IsValid(NeedEntry), TEXT("Need Entry is invalid."));

	return NeedEntry->GetMaxValue();
}

float UBBDossierModel::GetMaxValue(EBBSkill Skill) const
{
	UIBBDossierEntry * SkillEntry = SkillEntries.FindChecked(Skill);

	verifyf(IsValid(SkillEntry), TEXT("Skill Entry is invalid."));

	return SkillEntry->GetMaxValue();
}

UIBBDossierEntry * UBBDossierModel::GetDossierEntry(EBBAttribute Attribute) const
{
	return AttributeEntries.FindChecked(Attribute);
}

UIBBDossierEntry * UBBDossierModel::GetDossierEntry(EBBNeed Need) const
{
	return NeedEntries.FindChecked(Need);
}

UIBBDossierEntry * UBBDossierModel::GetDossierEntry(EBBSkill Skill) const
{
	return SkillEntries.FindChecked(Skill);
}



void UBBDossierModel::InitializeView(UIBBDossierWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Dossier View is invalid."));

	View = NewView;
}

void UBBDossierModel::InitializeCharacter(AIBBCharacter * NewCharacter)
{
	FinalizeCharacter();

	verifyf(IsValid(NewCharacter), TEXT("New Character is invalid."));

	Character = NewCharacter;

	Character->OnWidgetTargetUpdate().AddUObject(this, & UBBDossierModel::UpdateWidgetTarget);

	UIBBAIAbilityComponent * AbilityComponent = Cast<UIBBAIAbilityComponent>(Character->GetAbilitySystemComponent());

	verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."));

	InitializeEntries(* AbilityComponent);

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(Character));
}

void UBBDossierModel::InitializeEntries(UAbilitySystemComponent & AbilityComponent)
{
	UIBBAttributeSet * AttributeSet = const_cast<UIBBAttributeSet *>(AbilityComponent.GetSet<UIBBAttributeSet>());
	UIBBNeedSet * NeedSet = const_cast<UIBBNeedSet *>(AbilityComponent.GetSet<UIBBNeedSet>());
	UIBBSkillSet * SkillSet = const_cast<UIBBSkillSet *>(AbilityComponent.GetSet<UIBBSkillSet>());

	InitializeEntries<UIBBAttributeSet, FBBAttributeRow, AttributeMap>(AttributeSet, GetAttributesDataTable(), AttributeEntries);
	InitializeEntries<UIBBNeedSet, FBBNeedRow, NeedMap>(NeedSet, GetNeedsDataTable(), NeedEntries);
	InitializeEntries<UIBBSkillSet, FBBSkillRow, SkillMap>(SkillSet, GetSkillsDataTable(), SkillEntries);
}

void UBBDossierModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBDossierModel::FinalizeCharacter()
{
	if (IsValid(Character))
	{
		FinalizeEntries(Character->GetAbilitySystemComponent());

		Character->OnWidgetTargetUpdate().RemoveAll(this);
	}

	Character = nullptr;

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(nullptr));
}

void UBBDossierModel::FinalizeEntries(UAbilitySystemComponent * AbilityComponent)
{
	AttributeEntries.Empty();
	NeedEntries.Empty();
	SkillEntries.Empty();
}

void UBBDossierModel::UpdateWidgetTarget()
{
	verifyf(IsValid(Character), TEXT("Character is invalid."));

	OnDisplayNameUpdate().Broadcast(Character->GetDisplayName(EBBDisplayName::Full));
}