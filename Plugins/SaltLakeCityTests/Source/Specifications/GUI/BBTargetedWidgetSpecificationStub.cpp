// SaltLakeCity 4.26

#include "BBTargetedWidgetSpecificationStub.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"


UBBTargetedWidgetSpecificationStub::UBBTargetedWidgetSpecificationStub() :
	Super()
{
	DesiredModel = nullptr;
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
	ReturnWidget = nullptr;
	Evaluation = false;
}

TScriptInterface<IBBWidgetTarget> UBBTargetedWidgetSpecificationStub::GetWidgetTarget()
{
	return WidgetTarget;
}

void UBBTargetedWidgetSpecificationStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

bool UBBTargetedWidgetSpecificationStub::GetEvaluation() const
{
	return Evaluation;
}

void UBBTargetedWidgetSpecificationStub::SetEvaluation(bool NewEvaluation, const UIBBGUIModel * NewDesiredModel)
{
	Evaluation = NewEvaluation;
	DesiredModel = NewDesiredModel;
}

bool UBBTargetedWidgetSpecificationStub::Evaluate(const UIBBGUIModel * Model) const
{
	return Evaluation ? ( (DesiredModel != nullptr) ? (DesiredModel == Model) : true ) : false;
}

void UBBTargetedWidgetSpecificationStub::SetWidget(UIBBWidget * NewWidget)
{
	ReturnWidget = NewWidget;
}

bool UBBTargetedWidgetSpecificationStub::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	Widget = ReturnWidget;

	return IsValid(Widget);
}