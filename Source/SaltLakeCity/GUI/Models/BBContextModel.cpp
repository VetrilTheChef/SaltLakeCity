// SaltLakeCity 4.27

#include "BBContextModel.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "Engine/DataTable.h"
#include "GUI/Data/BBContextRow.h"
#include "GUI/Data/BBContextRowData.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBContextModel::UBBContextModel() :
	Super()
{
	View = nullptr;
	HUD = nullptr;
	Component = nullptr;
	ContextRows.Empty();
	RowWidgetSpecificators.Empty();
}

void UBBContextModel::PostInitProperties()
{
	Super::PostInitProperties();

	RowWidgetSpecificators.Emplace(EBBWidget::None, FBBRowWidgetSpecificator(& UBBContextModel::NewNoWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Build, FBBRowWidgetSpecificator(& UBBContextModel::NewBuildWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Context, FBBRowWidgetSpecificator(& UBBContextModel::NewContextWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::DateTime, FBBRowWidgetSpecificator(& UBBContextModel::NewDateTimeWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Dossier, FBBRowWidgetSpecificator(& UBBContextModel::NewDossierWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Job, FBBRowWidgetSpecificator(& UBBContextModel::NewJobWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Modes, FBBRowWidgetSpecificator(& UBBContextModel::NewModesWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Progress, FBBRowWidgetSpecificator(& UBBContextModel::NewProgressWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Selection, FBBRowWidgetSpecificator(& UBBContextModel::NewSelectionWidgetSpecification));
	RowWidgetSpecificators.Emplace(EBBWidget::Title, FBBRowWidgetSpecificator(& UBBContextModel::NewTitleWidgetSpecification));
}

TScriptInterface<IBBWidgetTarget> UBBContextModel::GetWidgetTarget() const
{
	return IsValid(Component)? Component->GetWidgetTarget() : TScriptInterface<IBBWidgetTarget>(nullptr);
}

UIBBWidget * UBBContextModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBContextModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBWidgetSpecification * ContextWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewContextWidgetSpecification(ContextWidgetSpecification, this);

	return ContextWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::GetRowWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, int RowIndex)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));
	
	FBBContextRowData RowData = ContextRows.IsValidIndex(RowIndex) ? ContextRows[RowIndex] : FBBContextRowData();

	return (this->* (RowWidgetSpecificators.FindChecked(RowData.WidgetToOpen).Specificator))(* WidgetSpecificationFactory, RowData);
}

UDataTable * UBBContextModel::GetDataTable()
{
	return TableAsset.LoadSynchronous();
}

void UBBContextModel::Initialize(UIBBContextWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table)
{
	InitializeRows(Table);
	InitializeView(NewView);
	InitializeHUD(NewHUD);
}

void UBBContextModel::Finalize()
{
	FinalizeHUD();
	FinalizeView();
	FinalizeRows();
}

int UBBContextModel::GetNumRows()
{
	return ContextRows.Num();
}

FBBContextRowData UBBContextModel::GetRowData(int Index)
{
	return ContextRows.IsValidIndex(Index) ? ContextRows[Index] : FBBContextRowData();
}

bool UBBContextModel::GetRowVisibility(EBBContext RowContextType) const
{
	return IsValid(Component) ? Component->IsOption(RowContextType) : false;
}



void UBBContextModel::InitializeRows(UDataTable * Table)
{
	verifyf(IsValid(Table), TEXT("Context Data Table is invalid."));

	for (auto& Iterator : Table->GetRowMap())
	{
		FBBContextRow * TableRow = (FBBContextRow *)Iterator.Value;

		if (TableRow)
		{
			FBBContextRowData ContextRow;
			ContextRow.Specification = TableRow->Specification.IsNull() ? nullptr : TableRow->Specification.LoadSynchronous();
			ContextRow.Name = TableRow->Name;
			ContextRow.Icon = TableRow->Icon.IsNull() ? nullptr : TableRow->Icon.LoadSynchronous();
			ContextRow.Tooltip = TableRow->Tooltip;
			ContextRow.ContextType = TableRow->ContextType;
			ContextRow.WidgetToOpen = TableRow->WidgetToOpen;

			ContextRows.Emplace(ContextRow);
		}
	}
}

void UBBContextModel::InitializeView(UIBBContextWidget * NewView)
{
	verifyf(IsValid(NewView), TEXT("New Context View is invalid."));

	View = NewView;
}

void UBBContextModel::InitializeHUD(AIBBHUD * NewHUD)
{
	verifyf(IsValid(NewHUD), TEXT("New HUD is invalid."));

	HUD = NewHUD;

	HUD->OnContextUpdate().AddUObject(this, & UBBContextModel::UpdateContext);
}

void UBBContextModel::InitializeComponent(UIBBContextComponent * NewContextComponent)
{
	FinalizeComponent();

	Component = NewContextComponent;

	OnTargetUpdate().Broadcast(Component->GetWidgetTarget());

	OnContextUpdate().Broadcast();
}

void UBBContextModel::FinalizeRows()
{
	ContextRows.Empty();
}

void UBBContextModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBContextModel::FinalizeHUD()
{
	if (IsValid(HUD))
	{
		HUD->OnContextUpdate().RemoveAll(this);
	}

	HUD = nullptr;
}

void UBBContextModel::FinalizeComponent()
{
	if (IsValid(Component))
	{
	}

	Component = nullptr;

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(nullptr));
}

UIBBWidgetSpecification * UBBContextModel::NewNoWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBWidgetSpecification * RowWidgetSpecification = nullptr;

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewBuildWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewBuildWidgetSpecification(RowWidgetSpecification, this);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewContextWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewContextWidgetSpecification(RowWidgetSpecification, this);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewDateTimeWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewDateTimeWidgetSpecification(RowWidgetSpecification, this);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewDossierWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBTargetedWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewDossierWidgetSpecification(RowWidgetSpecification, this, GetWidgetTarget());

	verifyf(IsValid(RowWidgetSpecification), TEXT("Row Widget Specification is invalid."));

	OnTargetUpdate().AddUObject(RowWidgetSpecification, & UIBBTargetedWidgetSpecification::SetWidgetTarget);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewJobWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBTargetedWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewJobWidgetSpecification(RowWidgetSpecification, this, GetWidgetTarget());

	verifyf(IsValid(RowWidgetSpecification), TEXT("Row Widget Specification is invalid."));

	OnTargetUpdate().AddUObject(RowWidgetSpecification, & UIBBTargetedWidgetSpecification::SetWidgetTarget);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewModesWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewModesWidgetSpecification(RowWidgetSpecification, this);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewProgressWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewProgressWidgetSpecification(RowWidgetSpecification, this);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewSelectionWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewSelectionWidgetSpecification(RowWidgetSpecification, this);

	return RowWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModel::NewTitleWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData)
{
	UIBBTargetedWidgetSpecification * RowWidgetSpecification = nullptr;

	WidgetSpecificationFactory.NewTitleWidgetSpecification(RowWidgetSpecification, this, GetWidgetTarget());

	verifyf(IsValid(RowWidgetSpecification), TEXT("Row Widget Specification is invalid."));

	OnTargetUpdate().AddUObject(RowWidgetSpecification, & UIBBTargetedWidgetSpecification::SetWidgetTarget);

	return RowWidgetSpecification;
}

void UBBContextModel::UpdateContext(UIBBContextComponent * NewContextComponent)
{
	verifyf(IsValid(NewContextComponent), TEXT("New Context Component is invalid."));

	InitializeComponent(NewContextComponent);
}