// SaltLakeCity 4.27

#include "BBBuildWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBBuildWidgetSpecification::UBBBuildWidgetSpecification() :
	Super()
{
}

bool UBBBuildWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	return (IsValid(Model) && IsValid(Model->GetWidget()) && (Model->GetWidget()->GetType() == EBBWidget::Build));
}

bool UBBBuildWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewBuildWidget((UIBBBuildWidget * &)Widget);
}