// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBAttributeEnum.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "GUI/Controllers/Interfaces/IBBDossierController.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "BBDossierController.generated.h"

/**
 * 
 */

class AIBBCharacter;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDossierController : public UIBBDossierController
{
	GENERATED_BODY()

	public:
		UBBDossierController();
		
		virtual void Initialize(UIBBDossierWidget * DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory, const UIBBSpecificationFactory * SpecificationFactory, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;
	
	protected:
		UPROPERTY()
		UIBBDossierModel * Model;

		UPROPERTY()
		UIBBDossierWidget * View;

		void InitializeModel(UIBBDossierModel * DossierModel);

		void FinalizeModel();

		void InitializeView(UIBBDossierWidget * DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory, const UIBBSpecificationFactory * SpecificationFactory, const UIBBCommandFactory * CommandFactory);

		void FinalizeView();

		void CreateTitle(UIBBDossierWidget & DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory);

		void CreateCommands(UIBBDossierWidget & DossierView, const UIBBSpecificationFactory & SpecificationFactory, const UIBBCommandFactory & CommandFactory);

		void CreateCharacterPreview(UIBBDossierWidget & DossierView, const AIBBCharacter * TemplateCharacter);

		void SetDisplayName(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel);

		void AddAttributeEntries(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const;

		void AddNeedEntries(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const;

		void AddSkillEntries(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const;

		void AddAttributeEntry(EBBAttribute Attribute, UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const;

		void AddNeedEntry(EBBNeed Need, UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const;

		void AddSkillEntry(EBBSkill Skill, UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const;

		UFUNCTION()
		void UpdateDisplayName(FText NewDisplayName);
};
