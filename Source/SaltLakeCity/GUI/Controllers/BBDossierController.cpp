// SaltLakeCity 5.7

#include "BBDossierController.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "Specifications/Factories/Interfaces/IBBSpecificationFactory.h"

UBBDossierController::UBBDossierController() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBDossierController::Initialize(UIBBDossierWidget * DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory, const UIBBSpecificationFactory * SpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(DossierModel);
	InitializeView(DossierView, DossierModel, WidgetFactory, SpecificationFactory, CommandFactory);
}

void UBBDossierController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBDossierController::InitializeModel(UIBBDossierModel * DossierModel)
{
	FinalizeModel();

	verifyf(IsValid(DossierModel), TEXT("Dossier Model is invalid."));
	
	Model = DossierModel;

	Model->OnDisplayNameUpdate().AddUObject(this, & UBBDossierController::UpdateDisplayName);
}

void UBBDossierController::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnDisplayNameUpdate().RemoveAll(this);
	}

	Model = nullptr;
}

void UBBDossierController::InitializeView(UIBBDossierWidget * DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory, const UIBBSpecificationFactory * SpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	FinalizeView();

	verifyf(IsValid(DossierView), TEXT("Dossier View is invalid."));

	View = DossierView;

	CreateTitle(* View, DossierModel, WidgetFactory);

	verifyf(IsValid(SpecificationFactory), TEXT("Specification Factory is invalid."));
	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	CreateCommands(* DossierView, * SpecificationFactory, * CommandFactory);

	CreateCharacterPreview(* DossierView, DossierModel->GetCharacter());

	SetDisplayName(* DossierView, * DossierModel);

	AddAttributeEntries(* DossierView, * DossierModel);
	AddNeedEntries(* DossierView, * DossierModel);
	AddSkillEntries(* DossierView, * DossierModel);
}

void UBBDossierController::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkAsGarbage();
	}

	View = nullptr;
}

void UBBDossierController::CreateTitle(UIBBDossierWidget & DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory)
{
	verifyf(IsValid(WidgetFactory), TEXT("Widget Factory is invalid."));

	WidgetFactory->NewTitleWidget(DossierView.GetTitle(), DossierModel);
}

void UBBDossierController::CreateCommands(UIBBDossierWidget & DossierView, const UIBBSpecificationFactory & SpecificationFactory, const UIBBCommandFactory & CommandFactory)
{
}

void UBBDossierController::CreateCharacterPreview(UIBBDossierWidget & DossierView, const AIBBCharacter * TemplateCharacter)
{
	DossierView.CreateCharacterPreview(TemplateCharacter);
}

void UBBDossierController::SetDisplayName(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel)
{
	DossierView.SetDisplayName(DossierModel.GetDisplayName());
}

void UBBDossierController::AddAttributeEntries(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const
{
	#define EBBATTRIBUTE_OPERATION(Value) AddAttributeEntry(Value, DossierView, DossierModel);

		FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

	#undef EBBATTRIBUTE_OPERATION
}

void UBBDossierController::AddNeedEntries(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const
{
	#define EBBNEED_OPERATION(Value) AddNeedEntry(Value, DossierView, DossierModel);

		FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

	#undef EBBNEED_OPERATION
}

void UBBDossierController::AddSkillEntries(UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const
{
	#define EBBSKILL_OPERATION(Value) AddSkillEntry(Value, DossierView, DossierModel);

		FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

	#undef EBBSKILL_OPERATION
}

void UBBDossierController::AddAttributeEntry(EBBAttribute Attribute, UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const
{
	DossierView.AddAttributeEntry(DossierModel.GetDossierEntry(Attribute));
}

void UBBDossierController::AddNeedEntry(EBBNeed Need, UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const
{
	DossierView.AddNeedEntry(DossierModel.GetDossierEntry(Need));
}

void UBBDossierController::AddSkillEntry(EBBSkill Skill, UIBBDossierWidget & DossierView, const UIBBDossierModel & DossierModel) const
{
	DossierView.AddSkillEntry(DossierModel.GetDossierEntry(Skill));
}

void UBBDossierController::UpdateDisplayName(FText NewDisplayName)
{
	verifyf(IsValid(View), TEXT("Dossier View is invalid."));

	View->SetDisplayName(NewDisplayName);
}