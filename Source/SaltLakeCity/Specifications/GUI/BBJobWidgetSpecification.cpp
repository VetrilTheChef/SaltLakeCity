// SaltLakeCity 4.27

#include "BBJobWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBJobModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBJobWidgetSpecification::UBBJobWidgetSpecification() :
	Super()
{
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
}

void UBBJobWidgetSpecification::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

bool UBBJobWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	bool Result = false;
	const UIBBJobModel * JobModel = Cast<UIBBJobModel>(Model);

	if (IsValid(JobModel))
	{
		Result = IsValid(JobModel->GetWidget()) &&
			(JobModel->GetWidget()->GetType() == EBBWidget::Job) &&
			(JobModel->GetWidgetTarget() == WidgetTarget);
	}

	return Result;
}

bool UBBJobWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewJobWidget((UIBBJobWidget * &)Widget);
}