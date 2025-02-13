// SaltLakeCity 4.27

#include "BBWidgetSpecificationStub.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "GUI/Models/Interfaces/IBBTargetedModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"


UBBWidgetSpecificationStub::UBBWidgetSpecificationStub() :
	Super()
{
	DesiredModel = nullptr;
	ReturnWidget = nullptr;
	Evaluation = false;
}

bool UBBWidgetSpecificationStub::GetEvaluation() const
{
	return Evaluation;
}

void UBBWidgetSpecificationStub::SetEvaluation(bool NewEvaluation, const UIBBGUIModel * NewDesiredModel)
{
	Evaluation = NewEvaluation;
	DesiredModel = NewDesiredModel;
}

bool UBBWidgetSpecificationStub::Evaluate(const UIBBGUIModel * Model) const
{
	return Evaluation ? ( (DesiredModel != nullptr) ? (DesiredModel == Model) : true ) : false;
}

void UBBWidgetSpecificationStub::SetWidget(UIBBWidget * NewWidget)
{
	ReturnWidget = NewWidget;
}

bool UBBWidgetSpecificationStub::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	Widget = ReturnWidget;

	return IsValid(Widget);
}