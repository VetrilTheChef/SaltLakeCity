// SaltLakeCity 4.27

#include "BBContextWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBContextWidgetSpecification::UBBContextWidgetSpecification() :
	Super()
{
}

bool UBBContextWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	return (IsValid(Model) && IsValid(Model->GetWidget()) && (Model->GetWidget()->GetType() == EBBWidget::Context));
}

bool UBBContextWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewContextWidget((UIBBContextWidget * &)Widget);
}