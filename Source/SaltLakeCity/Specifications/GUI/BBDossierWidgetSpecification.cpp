// SaltLakeCity 4.27

#include "BBDossierWidgetSpecification.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBDossierWidgetSpecification::UBBDossierWidgetSpecification() :
	Super()
{
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
}

void UBBDossierWidgetSpecification::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

bool UBBDossierWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	bool Result = false;
	const UIBBDossierModel * DossierModel = Cast<UIBBDossierModel>(Model);

	if (IsValid(DossierModel))
	{
		Result = IsValid(DossierModel->GetWidget()) &&
			(DossierModel->GetWidget()->GetType() == EBBWidget::Dossier) &&
			(DossierModel->GetWidgetTarget() == WidgetTarget.GetObject());
	}

	return Result;
}

bool UBBDossierWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewDossierWidget((UIBBDossierWidget * &)Widget, Cast<AIBBCharacter>(WidgetTarget.GetObject()));
}