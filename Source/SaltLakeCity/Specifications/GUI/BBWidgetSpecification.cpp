// SaltLakeCity 4.27

#include "BBWidgetSpecification.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"

UBBWidgetSpecification::UBBWidgetSpecification() :
	Super()
{
	WidgetType = EBBWidget::None;

	WidgetCreatorsMap.Empty();
	WidgetCreatorsMap.Emplace(EBBWidget::Build, & UBBWidgetSpecification::CreateBuildWidget);
	WidgetCreatorsMap.Emplace(EBBWidget::Context, & UBBWidgetSpecification::CreateContextWidget);
	WidgetCreatorsMap.Emplace(EBBWidget::DateTime, & UBBWidgetSpecification::CreateDateTimeWidget);
	WidgetCreatorsMap.Emplace(EBBWidget::Job, & UBBWidgetSpecification::CreateJobWidget);
	WidgetCreatorsMap.Emplace(EBBWidget::Modes, & UBBWidgetSpecification::CreateModesWidget);
	WidgetCreatorsMap.Emplace(EBBWidget::Selection, & UBBWidgetSpecification::CreateSelectionWidget);
}

void UBBWidgetSpecification::SetWidgetType(EBBWidget NewWidgetType)
{
	WidgetType = NewWidgetType;
}

bool UBBWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	return (IsValid(Model) && IsValid(Model->GetWidget()) && (Model->GetWidget()->GetType() == WidgetType));
}

bool UBBWidgetSpecification::CreateWidget(UIBBWidget *& Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	WidgetCreator Creator = WidgetCreatorsMap.FindRef(WidgetType);

	return (this->*Creator) (Widget, WidgetFactory);
}



bool UBBWidgetSpecification::CreateBuildWidget(UIBBWidget *& Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBBuildWidget * BuildWidget = nullptr;

	bool Result = WidgetFactory.NewBuildWidget(BuildWidget);

	Widget = BuildWidget;

	return Result;
}

bool UBBWidgetSpecification::CreateContextWidget(UIBBWidget *& Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBContextWidget * ContextWidget = nullptr;

	bool Result = WidgetFactory.NewContextWidget(ContextWidget);

	Widget = ContextWidget;

	return Result;
}

bool UBBWidgetSpecification::CreateDateTimeWidget(UIBBWidget *& Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBDateTimeWidget * DateTimeWidget = nullptr;

	bool Result = WidgetFactory.NewDateTimeWidget(DateTimeWidget);

	Widget = DateTimeWidget;

	return Result;
}

bool UBBWidgetSpecification::CreateJobWidget(UIBBWidget *& Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBJobWidget * JobWidget = nullptr;

	bool Result = WidgetFactory.NewJobWidget(JobWidget);

	Widget = JobWidget;

	return Result;
}

bool UBBWidgetSpecification::CreateModesWidget(UIBBWidget *& Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBModesWidget * ModesWidget = nullptr;

	bool Result = WidgetFactory.NewModesWidget(ModesWidget);

	Widget = ModesWidget;

	return Result;
}

bool UBBWidgetSpecification::CreateSelectionWidget(UIBBWidget *& Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBSelectionWidget * SelectionWidget = nullptr;

	bool Result = WidgetFactory.NewSelectionWidget(SelectionWidget);

	Widget = SelectionWidget;

	return Result;
}
