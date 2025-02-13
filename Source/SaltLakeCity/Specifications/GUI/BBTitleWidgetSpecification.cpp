// SaltLakeCity 4.27

#include "BBTitleWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBTitleModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBTitleWidgetSpecification::UBBTitleWidgetSpecification() :
	Super()
{
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
}

void UBBTitleWidgetSpecification::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

bool UBBTitleWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	bool Result = false;
	const UIBBTitleModel * TitleModel = Cast<UIBBTitleModel>(Model);

	if (IsValid(TitleModel))
	{
		Result = IsValid(TitleModel->GetWidget()) &&
			(TitleModel->GetWidget()->GetType() == EBBWidget::Title) &&
			(TitleModel->GetWidgetTarget() == WidgetTarget);
	}

	return Result;
}

bool UBBTitleWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewTitleWidget((UIBBTitleWidget * &)Widget, Cast<UIBBGUIModel>(WidgetTarget.GetObject()));
}