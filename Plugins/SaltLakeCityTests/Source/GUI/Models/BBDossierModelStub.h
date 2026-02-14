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

		virtual UIBBDossierEntry * GetDossierEntry(EBBAttribute Attribute) const;
		
		void SetDossierEntry(EBBAttribute Attribute, UIBBDossierEntry * NewDossierEntry);
		
		virtual UIBBDossierEntry * GetDossierEntry(EBBNeed Need) const;

		void SetDossierEntry(EBBNeed Need, UIBBDossierEntry * NewNeedEntry);

		virtual UIBBDossierEntry * GetDossierEntry(EBBSkill Skill) const;

		void SetDossierEntry(EBBSkill Skill, UIBBDossierEntry * NewSkillEntry);

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
