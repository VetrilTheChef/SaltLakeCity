// SaltLakeCity 4.27

#include "BBBuildEntryWidgetSpecification.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Models/Interfaces/IBBBuildEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBBuildEntryWidgetSpecification::UBBBuildEntryWidgetSpecification() :
	Super()
{
	BuildEntry = nullptr;
}

void UBBBuildEntryWidgetSpecification::SetBuildEntry(const UIBBBuildEntry * NewBuildEntry)
{
	BuildEntry = NewBuildEntry;
}

bool UBBBuildEntryWidgetSpecification::Evaluate(const UIBBGUIModel * Model) const
{
	verifyf(IsValid(BuildEntry), TEXT("Build Entry is invalid."));

	bool Result = false;

	const UIBBBuildEntryModel * BuildEntryModel = Cast<UIBBBuildEntryModel>(Model);

	if (IsValid(BuildEntryModel))
	{
		Result = IsValid(BuildEntryModel->GetWidget()) &&
			(BuildEntryModel->GetWidget()->GetType() == EBBWidget::BuildEntry) &&
			(BuildEntryModel->GetEntryName().EqualTo(BuildEntry->GetEntryName())) &&
			(BuildEntryModel->GetEntryIcon() == BuildEntry->GetEntryIcon()) &&
			(BuildEntryModel->GetEntryPrice() == BuildEntry->GetEntryPrice()) &&
			(BuildEntryModel->GetEntryTime() == BuildEntry->GetEntryTime()) &&
			(BuildEntryModel->GetEntryBuildableClasses() == BuildEntry->GetEntryBuildables()) &&
			(BuildEntryModel->GetEntryBuildDataClass() == BuildEntry->GetEntryBuildDataClass());
	}

	return Result;
}

bool UBBBuildEntryWidgetSpecification::CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const
{
	return WidgetFactory.NewBuildEntryWidget((UIBBBuildEntryWidget * &)Widget, BuildEntry);
}