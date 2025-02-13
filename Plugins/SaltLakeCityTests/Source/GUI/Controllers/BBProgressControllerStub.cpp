// SaltLakeCity 4.26

#include "BBProgressControllerStub.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"

UBBProgressControllerStub::UBBProgressControllerStub() :
	Super()
{
	View = nullptr;
	Model = nullptr;
}

void UBBProgressControllerStub::Initialize(UIBBProgressWidget * ProgressView, UIBBProgressModel * ProgressModel)
{
	InitializeView(ProgressView);
	InitializeModel(ProgressModel);
}

void UBBProgressControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}

float UBBProgressControllerStub::GetProgress()
{
	return -1.0f;
}

void UBBProgressControllerStub::SetProgress(float NewProgress)
{
}



void UBBProgressControllerStub::InitializeView(UIBBProgressWidget * ProgressView)
{
	View = ProgressView;
}

void UBBProgressControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBProgressControllerStub::InitializeModel(UIBBProgressModel * ProgressModel)
{
	Model = ProgressModel;
}

void UBBProgressControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}