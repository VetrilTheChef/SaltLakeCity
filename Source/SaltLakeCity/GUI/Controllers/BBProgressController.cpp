// SaltLakeCity 4.26

#include "BBProgressController.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"

UBBProgressController::UBBProgressController() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBProgressController::Initialize(UIBBProgressWidget * ProgressView, UIBBProgressModel * ProgressModel)
{
	InitializeModel(ProgressModel);
	InitializeView(ProgressView);
}

void UBBProgressController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBProgressController::InitializeModel(UIBBProgressModel * ProgressModel)
{
	verifyf(IsValid(ProgressModel), TEXT("Progress Model is invalid."));

	FinalizeModel();

	Model = ProgressModel;
}

void UBBProgressController::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBProgressController::InitializeView(UIBBProgressWidget * ProgressView)
{
	FinalizeView();

	View = ProgressView;

	verifyf(IsValid(View), TEXT("Progress View is invalid."));
}

void UBBProgressController::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkPendingKill();
	}

	View = nullptr;
}