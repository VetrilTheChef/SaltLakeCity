// SaltLakeCity 4.27

#include "BBContextRowWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBContextRowWidgetSpecification::UBBContextRowWidgetSpecification() :
	Super()
{
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
	RowData = FBBContextRowData();
}

void UBBContextRowWidgetSpecification::SetRowData(FBBContextRowData NewRowData)
{
	RowData = NewRowData;
}

void UBBContextRowWidgetSpecification::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

bool UBBContextRowWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	bool Result = false;

	/*const UIBBContextModel * ContextModel = Cast<UIBBContextModel>(Model);

	if (IsValid(ContextModel))
	{
		Result = IsValid(ContextRowModel->GetWidget()) &&
			(ContextModel->GetWidget()->GetType() == EBBWidget::None) &&
			(ContextModel->GetRowName().EqualTo(RowData.Name)) &&
			(ContextModel->GetRowIcon() == RowData.Icon) &&
			(ContextModel->GetRowTooltip().EqualTo(RowData.Tooltip)) &&
			(ContextModel->GetRowContextType() == RowData.ContextType) &&
			(ContextModel->GetRowWidgetToOpen() == RowData.WidgetToOpen);
	}*/

	return Result;
}

bool UBBContextRowWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewContextRowWidget((UIBBContextRowWidget * &)Widget, RowData);
}