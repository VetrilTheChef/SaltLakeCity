// SaltLakeCity 5.7

#include "BBModelPool.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Components/Iterators/Interfaces/IBBModelIterator.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "GUI/Models/Interfaces/IBBBuildEntryModel.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "GUI/Models/Interfaces/IBBJobModel.h"
#include "GUI/Models/Interfaces/IBBModesModel.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "GUI/Models/Interfaces/IBBTitleModel.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"

UBBModelPool::UBBModelPool() :
	Super()
{
	ModelsMap.Empty();
}

void UBBModelPool::PostInitProperties()
{
	Super::PostInitProperties();

	ModelsMap.Empty();
	ModelsMap.Emplace(EBBWidget::Build, NewObject<UBBGUIModelSingle>(this, UBBGUIModelSingle::StaticClass()));
	ModelsMap.Emplace(EBBWidget::BuildEntry, NewObject<UBBGUIModelArray>(this, UBBGUIModelArray::StaticClass()));
	ModelsMap.Emplace(EBBWidget::Context, NewObject<UBBGUIModelSingle>(this, UBBGUIModelSingle::StaticClass()));
	ModelsMap.Emplace(EBBWidget::DateTime, NewObject<UBBGUIModelSingle>(this, UBBGUIModelSingle::StaticClass()));
	ModelsMap.Emplace(EBBWidget::Dossier, NewObject<UBBGUIModelArray>(this, UBBGUIModelArray::StaticClass()));
	ModelsMap.Emplace(EBBWidget::DossierEntry, NewObject<UBBGUIModelArray>(this, UBBGUIModelArray::StaticClass()));
	ModelsMap.Emplace(EBBWidget::Job, NewObject<UBBGUIModelArray>(this, UBBGUIModelArray::StaticClass()));
	ModelsMap.Emplace(EBBWidget::Modes, NewObject<UBBGUIModelSingle>(this, UBBGUIModelSingle::StaticClass()));
	ModelsMap.Emplace(EBBWidget::Progress, NewObject<UBBGUIModelArray>(this, UBBGUIModelArray::StaticClass()));
	ModelsMap.Emplace(EBBWidget::Selection, NewObject<UBBGUIModelSingle>(this, UBBGUIModelSingle::StaticClass()));
	ModelsMap.Emplace(EBBWidget::SkillEntry, NewObject<UBBGUIModelArray>(this, UBBGUIModelArray::StaticClass()));
	ModelsMap.Emplace(EBBWidget::Title, NewObject<UBBGUIModelArray>(this, UBBGUIModelArray::StaticClass()));
}

void UBBModelPool::BeginDestroy()
{
	ModelsMap.Empty();

	Super::BeginDestroy();
}

void UBBModelPool::Initialize(const UIBBGameInstance * NewGameInstance)
{
	verifyf(IsValid(NewGameInstance), TEXT("New Game Instance is invalid."));

	FTimerManager & TimerManager = NewGameInstance->GetTimerManager();

	for (TPair<EBBWidget, UIBBGUIModelContainer *> & ModelsCategory : ModelsMap)
	{
		UIBBGUIModelContainer * ModelsContainer = ModelsCategory.Value;

		verifyf(IsValid(ModelsContainer), TEXT("Models Container is invalid."));

		ModelsContainer->Initialize(TimerManager);
	}
}

void UBBModelPool::Finalize()
{
	for (TPair<EBBWidget, UIBBGUIModelContainer *> & ModelsCategory : ModelsMap)
	{
		UIBBGUIModelContainer * ModelsContainer = ModelsCategory.Value;

		verifyf(IsValid(ModelsContainer), TEXT("Models Container is invalid."));

		ModelsContainer->Finalize();
	}
}

void UBBModelPool::AddBuildModel(UIBBBuildModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Build);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetBuildModel(UIBBBuildModel * & Model) const 
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Build);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBBuildModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddBuildEntryModel(UIBBBuildEntryModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::BuildEntry);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetBuildEntryModel(UIBBBuildEntryModel * & Model)
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::BuildEntry);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBBuildEntryModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddContextModel(UIBBContextModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Context);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetContextModel(UIBBContextModel * & Model) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Context);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBContextModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddDateTimeModel(UIBBDateTimeModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::DateTime);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetDateTimeModel(UIBBDateTimeModel * & Model) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::DateTime);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBDateTimeModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddDossierModel(UIBBDossierModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Dossier);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetDossierModel(UIBBDossierModel * & Model, AIBBCharacter * Character) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Dossier);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBDossierModel>(Container->Get(Index));

		if (IsValid(Model) &&
			(Model->GetCharacter() == Character))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddDossierEntryModel(UIBBDossierEntryModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::DossierEntry);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetDossierEntryModel(UIBBDossierEntryModel * & Model)
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::DossierEntry);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBDossierEntryModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddJobModel(UIBBJobModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Job);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetJobModel(UIBBJobModel * & Model) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Job);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBJobModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddModesModel(UIBBModesModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Modes);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetModesModel(UIBBModesModel * & Model) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Modes);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBModesModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddProgressModel(UIBBProgressModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Progress);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetProgressModel(UIBBProgressModel * & Model) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Progress);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBProgressModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddSelectionModel(UIBBSelectionModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Selection);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetSelectionModel(UIBBSelectionModel * & Model) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Selection);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBSelectionModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

void UBBModelPool::AddTitleModel(UIBBTitleModel * NewModel)
{
	UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Title);

	verifyf(Container, TEXT("Model Container is null."));

	Container->Add(NewModel);
}

bool UBBModelPool::GetTitleModel(UIBBTitleModel * & Model) const
{
	const UIBBGUIModelContainer * Container = ModelsMap.FindRef(EBBWidget::Title);

	verifyf(Container, TEXT("Model Container is null."));

	for (int Index = 0; Index < Container->GetNumModels(); Index++)
	{
		Model = Cast<UIBBTitleModel>(Container->Get(Index));

		if (IsValid(Model))
		{
			return true;
		}
	}

	Model = nullptr;

	return false;
}

const UIBBModelIterator * UBBModelPool::GetIterator(EBBWidget WidgetType)
{
	verifyf(!ModelIteratorClass.IsNull(), TEXT("Model Iterator Class is null."));

	UIBBModelIterator * Iterator = NewObject<UIBBModelIterator>(this, ModelIteratorClass.LoadSynchronous());

	verifyf(IsValid(Iterator), TEXT("Iterator is invalid."));

	//Iterator->SetModelContainer(* ModelsMap.FindRef(WidgetType));

	return Iterator;
}

UIBBGUIModel * UBBModelPool::GetModel(UIBBWidgetSpecification & Specification)
{
	for (TPair<EBBWidget, UIBBGUIModelContainer *> & ModelsCategory : ModelsMap)
	{
		UIBBGUIModelContainer * Models = ModelsCategory.Value;

		if (IsValid(Models))
		{
			for (int Index = 0; Index < Models->GetNumModels(); Index++)
			{
				UIBBGUIModel * Model = Models->Get(Index);

				if (Specification.Evaluate(Model))
				{
					return Model;
				}
			}
		}
	}

	return nullptr;
}