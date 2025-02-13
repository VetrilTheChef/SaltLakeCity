// SaltLakeCity 4.27

#include "BBDateTimeWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBDateTimeWidgetSpecification::UBBDateTimeWidgetSpecification() :
	Super()
{
}

bool UBBDateTimeWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	return (IsValid(Model) && IsValid(Model->GetWidget()) && (Model->GetWidget()->GetType() == EBBWidget::DateTime));
}

bool UBBDateTimeWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewDateTimeWidget((UIBBDateTimeWidget * &)Widget);
}