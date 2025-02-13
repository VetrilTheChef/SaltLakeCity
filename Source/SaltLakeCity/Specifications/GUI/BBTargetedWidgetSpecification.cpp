// SaltLakeCity 4.27

#include "BBTargetedWidgetSpecification.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Models/Interfaces/IBBTargetedModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"

UBBTargetedWidgetSpecification::UBBTargetedWidgetSpecification() :
	Super()
{
	WidgetType = EBBWidget::None;
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();

	WidgetCreatorsMap.Empty();
	WidgetCreatorsMap.Emplace(EBBWidget::Dossier, & UBBTargetedWidgetSpecification::CreateDossierWidget);
	WidgetCreatorsMap.Emplace(EBBWidget::Progress, & UBBTargetedWidgetSpecification::CreateProgressWidget);
	WidgetCreatorsMap.Emplace(EBBWidget::Title, & UBBTargetedWidgetSpecification::CreateTitleWidget);
}

void UBBTargetedWidgetSpecification::SetWidgetType(EBBWidget NewWidgetType)
{
	WidgetType = NewWidgetType;
}

void UBBTargetedWidgetSpecification::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

bool UBBTargetedWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	bool Result = false;
	const UIBBTargetedModel * TargetedModel = Cast<UIBBTargetedModel>(Model);

	if (IsValid(TargetedModel))
	{
		Result = IsValid(TargetedModel->GetWidget()) &&
			(TargetedModel->GetWidget()->GetType() == WidgetType) &&
			(TargetedModel->GetWidgetTarget() == WidgetTarget);
	}

	return Result;
}

bool UBBTargetedWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	WidgetCreator Creator = WidgetCreatorsMap.FindRef(WidgetType);

	return (this->* Creator) (Widget, WidgetFactory);
}



bool UBBTargetedWidgetSpecification::CreateDossierWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBDossierWidget * DossierWidget = nullptr;

	bool Result = WidgetFactory.NewDossierWidget(DossierWidget, Cast<AIBBCharacter>(WidgetTarget.GetObject()));

	Widget = DossierWidget;

	return Result;
}

bool UBBTargetedWidgetSpecification::CreateProgressWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBProgressWidget * ProgressWidget = nullptr;

	bool Result = WidgetFactory.NewProgressWidget(ProgressWidget, Cast<UIBBProgressComponent>(WidgetTarget.GetObject()));

	Widget = ProgressWidget;

	return Result;
}

bool UBBTargetedWidgetSpecification::CreateTitleWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	UIBBTitleWidget * TitleWidget = nullptr;

	bool Result = WidgetFactory.NewTitleWidget(TitleWidget, Cast<UIBBGUIModel>(WidgetTarget.GetObject()));

	Widget = TitleWidget;

	return Result;
}