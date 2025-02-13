// SaltLakeCity 4.27

#include "BBSkillEntryControllerStub.h"
#include "GUI/Models/Interfaces/IBBSkillEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBSkillEntryWidget.h"

UBBSkillEntryControllerStub::UBBSkillEntryControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBSkillEntryControllerStub::Initialize(UIBBSkillEntryWidget * SkillEntryView, UIBBSkillEntryModel * SkillEntryModel)
{
	InitializeModel(SkillEntryModel);
	InitializeView(SkillEntryView, SkillEntryModel);
}

void UBBSkillEntryControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}


void UBBSkillEntryControllerStub::InitializeModel(UIBBSkillEntryModel * SkillEntryModel)
{
	FinalizeModel();

	Model = SkillEntryModel;
}

void UBBSkillEntryControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBSkillEntryControllerStub::InitializeView(UIBBSkillEntryWidget * SkillEntryView, UIBBSkillEntryModel * SkillEntryModel)
{
	FinalizeView();

	View = SkillEntryView;

	if (IsValid(View))
	{
		if (IsValid(SkillEntryModel))
		{
			View->SetEntryName(SkillEntryModel->GetEntryName());
			View->SetIcon(SkillEntryModel->GetEntryIcon().LoadSynchronous());
			View->SetValue(SkillEntryModel->GetEntryValue());
			View->SetMaxValue(SkillEntryModel->GetEntryMaxValue());
		}
	}
}

void UBBSkillEntryControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}