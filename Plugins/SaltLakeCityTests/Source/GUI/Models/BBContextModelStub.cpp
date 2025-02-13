// SaltLakeCity 4.27

#include "BBContextModelStub.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"

UBBContextModelStub::UBBContextModelStub() :
	Super()
{
	View = nullptr;
	HUD = nullptr;
	Rows.Empty();

	ContextComponent = nullptr;
	WidgetSpecification = nullptr;
	RowWidgetSpecification = nullptr;
}

void UBBContextModelStub::PostInitProperties()
{
	Super::PostInitProperties();
}

TScriptInterface<IBBWidgetTarget> UBBContextModelStub::GetWidgetTarget() const
{
	return TScriptInterface<IBBWidgetTarget>();
}

UIBBWidget * UBBContextModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBContextModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return WidgetSpecification;
}

void UBBContextModelStub::SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecification = NewWidgetSpecification;
}

UIBBWidgetSpecification * UBBContextModelStub::GetRowWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, int RowIndex)
{
	return RowWidgetSpecification;
}

void UBBContextModelStub::SetRowWidgetSpecification(UIBBWidgetSpecification * NewRowWidgetSpecification)
{
	RowWidgetSpecification = NewRowWidgetSpecification;
}

UDataTable * UBBContextModelStub::GetDataTable()
{
	return nullptr;
}

void UBBContextModelStub::Initialize(UIBBContextWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table)
{
	View = NewView;
	HUD = NewHUD;

	if (IsValid(HUD))
	{
		HUD->OnContextUpdate().AddUObject(this, & UBBContextModelStub::UpdateContext);
	}
}

void UBBContextModelStub::Finalize()
{
	if (IsValid(HUD))
	{
		HUD->OnContextUpdate().RemoveAll(this);
	}

	HUD = nullptr;
	View = nullptr;
}

const UIBBContextComponent * UBBContextModelStub::GetComponent() const
{
	return ContextComponent;
}

void UBBContextModelStub::AddRow(FText NewName, UClass * NewSpecification, UTexture2D * NewIcon, FText NewTooltip, EBBContext NewOptionType, EBBWidget NewWidgetType)
{
	Rows.Emplace(FBBContextRowData(NewName, NewSpecification, NewIcon, NewTooltip, NewOptionType, NewWidgetType));
}

int UBBContextModelStub::GetNumRows()
{
	return Rows.Num();
}

FBBContextRowData UBBContextModelStub::GetRowData(int Index)
{
	return Rows.IsValidIndex(Index) ? Rows[Index] : FBBContextRowData();
}



void UBBContextModelStub::UpdateContext(UIBBContextComponent * NewContextComponent)
{
	ContextComponent = NewContextComponent;
}