// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Attributes/Includes/BBAttributeEnum.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "GUI/Models/Interfaces/IBBTargetedModel.h"
#include "IBBDossierModel.generated.h"

/**
 * 
 */

class AIBBCharacter;
class UAbilitySystemComponent;
class UIBBDossierEntry;
class UIBBDossierWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierModel : public UIBBTargetedModel
{
	GENERATED_BODY()

	public:
		UIBBDossierModel() : Super() { };

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override PURE_VIRTUAL(UIBBDossierModel::GetTarget, return nullptr; );

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBDossierModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBDossierModel::GetWidgetSpecification, return nullptr; );

		virtual UDataTable * GetAttributesDataTable() const PURE_VIRTUAL(UIBBDossierModel::GetAttributesDataTable, return nullptr; );

		virtual UDataTable * GetNeedsDataTable() const PURE_VIRTUAL(UIBBDossierModel::GetNeedsDataTable, return nullptr; );

		virtual UDataTable * GetSkillsDataTable() const PURE_VIRTUAL(UIBBDossierModel::GetSkillsDataTable, return nullptr; );

		virtual void Initialize(UIBBDossierWidget * NewView, AIBBCharacter * NewCharacter) PURE_VIRTUAL(UIBBDossierModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBDossierModel::Unbind, );

		virtual const AIBBCharacter * GetCharacter() const PURE_VIRTUAL(UIBBDossierModel::GetCharacter, return nullptr; );

		const UAbilitySystemComponent * GetAbilitySystemComponent() const PURE_VIRTUAL(UIBBDossierModel::GetAbilitySystemComponent, return nullptr; );

		virtual FText GetDisplayName() const PURE_VIRTUAL(UIBBDossierModel::GetDisplayName, return FText::FromString(""); );

		virtual UIBBDossierEntry * GetDossierEntry(EBBAttribute Attribute) const PURE_VIRTUAL(UIBBDossierModel::GetDossierEntry, return nullptr; );

		virtual UIBBDossierEntry * GetDossierEntry(EBBNeed Need) const PURE_VIRTUAL(UIBBDossierModel::GetDossierEntry, return nullptr; );

		virtual UIBBDossierEntry * GetDossierEntry(EBBSkill Skill) const PURE_VIRTUAL(UIBBDossierModel::GetDossierEntry, return nullptr; );
		
		DECLARE_EVENT_OneParam(UIBBDossierModel, FBBDisplayNameUpdate, FText);

		FBBDisplayNameUpdate & OnDisplayNameUpdate() { return UpdateDisplayName; };

	protected:
		FBBDisplayNameUpdate UpdateDisplayName;
};
