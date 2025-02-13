// SaltLakeCity 4.27

#include "BBSelectionWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBSelectionWidgetSpecification::UBBSelectionWidgetSpecification() :
	Super()
{
}

bool UBBSelectionWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	return (IsValid(Model) && IsValid(Model->GetWidget()) && (Model->GetWidget()->GetType() == EBBWidget::Selection));
}

bool UBBSelectionWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewSelectionWidget((UIBBSelectionWidget * &)Widget);
}