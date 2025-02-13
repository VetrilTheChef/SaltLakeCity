// SaltLakeCity 4.26

#include "BBModelPoolStub.h"

UBBModelPoolStub::UBBModelPoolStub() :
	Super()
{
	BuildModels.Empty();
	ContextModels.Empty();
	DateTimeModels.Empty();
	DossierModels.Empty();
	JobModels.Empty();
	ProgressModels.Empty();
	SelectionModels.Empty();
	TitleModels.Empty();

	ReturnModel = nullptr;
}

void UBBModelPoolStub::Initialize(UIBBGameInstance * NewGameInstance)
{
}

void UBBModelPoolStub::AddBuildModel(UIBBBuildModel * NewModel)
{
	BuildModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetBuildModel(UIBBBuildModel * & Model) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumBuildModels() const
{
	return BuildModels.Num();
}

UIBBBuildModel * UBBModelPoolStub::GetBuildModel(int Index) const
{
	return BuildModels.IsValidIndex(Index) ? BuildModels[Index] : nullptr;
}


void UBBModelPoolStub::AddContextModel(UIBBContextModel * NewModel)
{
	ContextModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetContextModel(UIBBContextModel * & Model) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumContextModels() const
{
	return ContextModels.Num();
}

UIBBContextModel * UBBModelPoolStub::GetContextModel(int Index) const
{
	return ContextModels.IsValidIndex(Index) ? ContextModels[Index] : nullptr;
}

void UBBModelPoolStub::AddDateTimeModel(UIBBDateTimeModel * NewModel)
{
	DateTimeModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetDateTimeModel(UIBBDateTimeModel * & Model) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumDateTimeModels() const
{
	return DateTimeModels.Num();
}

UIBBDateTimeModel * UBBModelPoolStub::GetDateTimeModel(int Index) const
{
	return DateTimeModels.IsValidIndex(Index) ? DateTimeModels[Index] : nullptr;
}

void UBBModelPoolStub::AddDossierModel(UIBBDossierModel * NewModel)
{
	DossierModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetDossierModel(UIBBDossierModel * & Model, AIBBCharacter * Character) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumDossierModels() const
{
	return DossierModels.Num();
}

UIBBDossierModel * UBBModelPoolStub::GetDossierModel(int Index) const
{
	return DossierModels.IsValidIndex(Index) ? DossierModels[Index] : nullptr;
}

void UBBModelPoolStub::AddJobModel(UIBBJobModel * NewModel)
{
	JobModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetJobModel(UIBBJobModel * & Model) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumJobModels() const
{
	return JobModels.Num();
}

UIBBJobModel * UBBModelPoolStub::GetJobModel(int Index) const
{
	return JobModels.IsValidIndex(Index) ? JobModels[Index] : nullptr;
}

void UBBModelPoolStub::AddProgressModel(UIBBProgressModel * NewModel)
{
	ProgressModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetProgressModel(UIBBProgressModel * & Model) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumProgressModels() const
{
	return ProgressModels.Num();
}

void UBBModelPoolStub::AddSelectionModel(UIBBSelectionModel * NewModel)
{
	SelectionModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetSelectionModel(UIBBSelectionModel * & Model) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumSelectionModels() const
{
	return SelectionModels.Num();
}

UIBBProgressModel * UBBModelPoolStub::GetProgressModel(int Index) const
{
	return ProgressModels.IsValidIndex(Index) ? ProgressModels[Index] : nullptr;
}

void UBBModelPoolStub::AddTitleModel(UIBBTitleModel * NewModel)
{
	TitleModels.Emplace(NewModel);
}

bool UBBModelPoolStub::GetTitleModel(UIBBTitleModel * & Model) const
{
	Model = nullptr;

	return false;
}

int UBBModelPoolStub::GetNumTitleModels() const
{
	return TitleModels.Num();
}

UIBBTitleModel * UBBModelPoolStub::GetTitleModel(int Index) const
{
	return TitleModels.IsValidIndex(Index) ? TitleModels[Index] : nullptr;
}

UIBBModelIterator * UBBModelPoolStub::GetIterator(EBBWidget WidgetType)
{
	return nullptr;
}

UIBBGUIModel * UBBModelPoolStub::GetModel(UIBBWidgetSpecification & Specification)
{
	return ReturnModel;
}

void UBBModelPoolStub::SetModel(UIBBGUIModel * NewReturnModel)
{
	ReturnModel = NewReturnModel;
}