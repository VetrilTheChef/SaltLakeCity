// SaltLakeCity 4.27

#include "BBProgressWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBProgressWidgetSpecification::UBBProgressWidgetSpecification() :
	Super()
{
	Component = nullptr;
}

void UBBProgressWidgetSpecification::SetComponent(UIBBProgressComponent * NewComponent)
{
	Component = NewComponent;
}

bool UBBProgressWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	return (IsValid(Model) && IsValid(Model->GetWidget()) && (Model->GetWidget()->GetType() == EBBWidget::Progress));
}

bool UBBProgressWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewProgressWidget((UIBBProgressWidget * &)Widget, Component);
}