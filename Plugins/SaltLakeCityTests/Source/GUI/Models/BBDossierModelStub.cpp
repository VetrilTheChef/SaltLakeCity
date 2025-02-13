// SaltLakeCity 4.27

#include "BBDossierModelStub.h"
#include "AbilitySystemComponent.h"
#include "Attributes/Interfaces/IBBAttributeSet.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "Actors/Components/Interfaces/IBBCharacterAbilityComponent.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"

UBBDossierModelStub::UBBDossierModelStub() :
	Super()
{
	View = nullptr;

	Character = nullptr;

	DisplayName = FText::FromString("");

	Target = nullptr;
}

void UBBDossierModelStub::PostInitProperties()
{
	Super::PostInitProperties();

	AttributeEntries.Empty();
	NeedEntries.Empty();
	SkillEntries.Empty();
}

void UBBDossierModelStub::BeginDestroy()
{
	AttributeEntries.Empty();
	NeedEntries.Empty();
	SkillEntries.Empty();

	Super::BeginDestroy();
}

TScriptInterface<IBBWidgetTarget> UBBDossierModelStub::GetWidgetTarget() const
{
	return Target;
}

void UBBDossierModelStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	Target = NewWidgetTarget;
	Character = (Cast<AIBBCharacter>(Target.GetObject()));
}

UIBBWidget * UBBDossierModelStub::GetWidget() const
{
	return View;
}

void UBBDossierModelStub::Initialize(UIBBDossierWidget * NewView, AIBBCharacter * NewCharacter)
{
	View = NewView;

	Character = NewCharacter;
	SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(Character));
}

void UBBDossierModelStub::Finalize()
{
	Character = nullptr;
	View = nullptr;
}

const AIBBCharacter * UBBDossierModelStub::GetCharacter() const
{
	return Character;
}

FText UBBDossierModelStub::GetDisplayName() const
{
	return DisplayName;
}

void UBBDossierModelStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}

UIBBDossierEntry * UBBDossierModelStub::GetEntry(EBBAttribute Attribute) const
{
	return AttributeEntries.Contains(Attribute) ? AttributeEntries.FindRef(Attribute) : nullptr;
}

void UBBDossierModelStub::SetEntry(EBBAttribute Attribute, UIBBDossierEntry * NewDossierEntry)
{
	AttributeEntries.Remove(Attribute);
	AttributeEntries.FindOrAdd(Attribute, NewDossierEntry);
}

UIBBDossierEntry * UBBDossierModelStub::GetEntry(EBBNeed Need) const
{
	return NeedEntries.Contains(Need) ? NeedEntries.FindRef(Need) : nullptr;
}

void UBBDossierModelStub::SetEntry(EBBNeed Need, UIBBDossierEntry * NewNeedEntry)
{
	NeedEntries.Remove(Need);
	NeedEntries.Add(Need, NewNeedEntry);
}

UIBBDossierEntry * UBBDossierModelStub::GetEntry(EBBSkill Skill) const
{
	return SkillEntries.Contains(Skill) ? SkillEntries.FindRef(Skill) : nullptr;
}

void UBBDossierModelStub::SetEntry(EBBSkill Skill, UIBBDossierEntry * NewSkillEntry)
{
	SkillEntries.Remove(Skill);
	SkillEntries.Add(Skill, NewSkillEntry);
}
