// SaltLakeCity 4.27

#include "BBModesWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBModesModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBModesWidgetSpecification::UBBModesWidgetSpecification() :
	Super()
{
}

bool UBBModesWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	return (IsValid(Model) && IsValid(Model->GetWidget()) && (Model->GetWidget()->GetType() == EBBWidget::Modes));
}

bool UBBModesWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewModesWidget((UIBBModesWidget * &)Widget);
}