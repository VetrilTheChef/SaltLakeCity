// SaltLakeCity 4.26

#include "BBBuildEntryControllerStub.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "Commands/Controllers/Interfaces/IBBOrderBuildCommand.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "GUI/Data/BBBuildEntry.h"
#include "GUI/Models/Interfaces/IBBBuildEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"

UBBBuildEntryControllerStub::UBBBuildEntryControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBBuildEntryControllerStub::Initialize(UIBBBuildEntryWidget * BuildEntryView, UIBBBuildEntryModel * BuildEntryModel, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(BuildEntryModel);
	InitializeView(BuildEntryView, BuildEntryModel, CommandFactory);
}

void UBBBuildEntryControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}


void UBBBuildEntryControllerStub::InitializeModel(UIBBBuildEntryModel * BuildEntryModel)
{
	FinalizeModel();

	Model = BuildEntryModel;
}

void UBBBuildEntryControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBBuildEntryControllerStub::InitializeView(UIBBBuildEntryWidget * BuildEntryView, UIBBBuildEntryModel * BuildEntryModel, const UIBBCommandFactory * CommandFactory)
{
	FinalizeView();

	View = BuildEntryView;

	if (IsValid(View))
	{
		if (IsValid(BuildEntryModel))
		{
			View->SetEntryName(BuildEntryModel->GetEntryName());
			View->SetIcon(BuildEntryModel->GetEntryIcon().LoadSynchronous());
			View->SetPrice(BuildEntryModel->GetEntryPrice());
			View->SetTime(BuildEntryModel->GetEntryTime());

			if (IsValid(CommandFactory))
			{
				UIBBOrderBuildCommand * Command = nullptr;
				
				if (CommandFactory->NewOrderBuildCommand(Command, View, BuildEntryModel->GetEntryBuildDataClass(), BuildEntryModel->GetEntryTargetingClass(), BuildEntryModel->GetEntryBuildableClasses(), BuildEntryModel->GetEntryPrice(), BuildEntryModel->GetEntryTime()))
				{
					View->SetCommand(Command);
				}
			}
		}
	}
}

void UBBBuildEntryControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}