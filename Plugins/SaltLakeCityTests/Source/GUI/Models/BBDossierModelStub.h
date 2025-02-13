// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
#include "BBDossierModelStub.generated.h"

/**
 * 
 */

class AIBBCharacter;
class UIBBDossierEntry;
class UIBBDossierWidget;
class UIBBWidget;

UCLASS(NotBlueprintable)

class UBBDossierModelStub : public UIBBDossierModel
{
	GENERATED_BODY()

	public:
		UBBDossierModelStub();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget);

		virtual UIBBWidget * GetWidget() const override;

		virtual void Initialize(UIBBDossierWidget * NewView, AIBBCharacter * NewCharacter) override;

		virtual void Finalize() override;

		virtual const AIBBCharacter * GetCharacter() const override;

		virtual FText GetDisplayName() const override;

		void SetDisplayName(FText NewDisplayName);

		UIBBDossierEntry * GetEntry(EBBAttribute Attribute) const;
		
		void SetEntry(EBBAttribute Attribute, UIBBDossierEntry * NewDossierEntry);
		
		UIBBDossierEntry * GetEntry(EBBNeed Need) const;

		void SetEntry(EBBNeed Need, UIBBDossierEntry * NewNeedEntry);

		UIBBDossierEntry * GetEntry(EBBSkill Skill) const;

		void SetEntry(EBBSkill Skill, UIBBDossierEntry * NewSkillEntry);

	protected:
		UPROPERTY()
		UIBBDossierWidget * View;

		UPROPERTY()
		AIBBCharacter * Character;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> Target;

		FText DisplayName;

		UPROPERTY()
		TMap<EBBAttribute, UIBBDossierEntry *> AttributeEntries;

		UPROPERTY()
		TMap<EBBNeed, UIBBDossierEntry *> NeedEntries;

		UPROPERTY()
		TMap<EBBSkill, UIBBDossierEntry *> SkillEntries;
};
