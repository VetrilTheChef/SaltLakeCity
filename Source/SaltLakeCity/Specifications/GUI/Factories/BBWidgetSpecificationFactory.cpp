// SaltLakeCity 4.26

#include "BBWidgetSpecificationFactory.h"
#include "Specifications/GUI/Interfaces/IBBBuildWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBContextWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBDateTimeWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBDossierWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBJobWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBModesWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBProgressWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBSelectionWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBTitleWidgetSpecification.h"

UBBWidgetSpecificationFactory::UBBWidgetSpecificationFactory() :
	Super()
{
}

void UBBWidgetSpecificationFactory::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBWidgetSpecificationFactory::BeginDestroy()
{
	Super::BeginDestroy();
}

bool UBBWidgetSpecificationFactory::NewBuildWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	verifyf(!BuildWidgetSpecificationClass.IsNull(), TEXT("Build Widget Specification class is null."));

	WidgetSpecification = NewObject<UIBBBuildWidgetSpecification>(Outer, BuildWidgetSpecificationClass.LoadSynchronous());
	
	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactory::NewContextWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	verifyf(!ContextWidgetSpecificationClass.IsNull(), TEXT("Context Widget Specification class is null."));

	WidgetSpecification = NewObject<UIBBContextWidgetSpecification>(Outer, ContextWidgetSpecificationClass.LoadSynchronous());

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactory::NewDateTimeWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	verifyf(!DateTimeWidgetSpecificationClass.IsNull(), TEXT("Date Time Widget Specification class is null."));

	WidgetSpecification = NewObject<UIBBDateTimeWidgetSpecification>(Outer, DateTimeWidgetSpecificationClass.LoadSynchronous());

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactory::NewDossierWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const
{
	verifyf(!DossierWidgetSpecificationClass.IsNull(), TEXT("Dossier Widget Specification class is null."));

	UIBBDossierWidgetSpecification * DossierWidgetSpecification = NewObject<UIBBDossierWidgetSpecification>(Outer, DossierWidgetSpecificationClass.LoadSynchronous());

	if (IsValid(DossierWidgetSpecification))
	{
		DossierWidgetSpecification->SetWidgetTarget(WidgetTarget);

		WidgetSpecification = DossierWidgetSpecification;

		return true;
	}

	return false;
}

bool UBBWidgetSpecificationFactory::NewJobWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const
{
	verifyf(!JobWidgetSpecificationClass.IsNull(), TEXT("Job Widget Specification class is null."));
	
	UIBBJobWidgetSpecification * JobWidgetSpecification = NewObject<UIBBJobWidgetSpecification>(Outer, JobWidgetSpecificationClass.LoadSynchronous());
	
	if (IsValid(JobWidgetSpecification))
	{
		JobWidgetSpecification->SetWidgetTarget(WidgetTarget);

		WidgetSpecification = JobWidgetSpecification;

		return true;
	}

	return false;
}

bool UBBWidgetSpecificationFactory::NewModesWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	verifyf(!ModesWidgetSpecificationClass.IsNull(), TEXT("Modes Widget Specification class is null."));

	WidgetSpecification = NewObject<UIBBModesWidgetSpecification>(Outer, ModesWidgetSpecificationClass.LoadSynchronous());

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactory::NewProgressWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	verifyf(!ProgressWidgetSpecificationClass.IsNull(), TEXT("Progress Widget Specification class is null."));

	WidgetSpecification = NewObject<UIBBProgressWidgetSpecification>(Outer, ProgressWidgetSpecificationClass.LoadSynchronous());

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactory::NewSelectionWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	verifyf(!SelectionWidgetSpecificationClass.IsNull(), TEXT("Selection Widget Specification class is null."));

	WidgetSpecification = NewObject<UIBBSelectionWidgetSpecification>(Outer, SelectionWidgetSpecificationClass.LoadSynchronous());

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactory::NewTitleWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const
{
	verifyf(!TitleWidgetSpecificationClass.IsNull(), TEXT("Title Widget Specification class is null."));

	UIBBTitleWidgetSpecification * TitleWidgetSpecification = NewObject<UIBBTitleWidgetSpecification>(Outer, TitleWidgetSpecificationClass.LoadSynchronous());

	if (IsValid(TitleWidgetSpecification))
	{
		TitleWidgetSpecification->SetWidgetTarget(WidgetTarget);

		WidgetSpecification = TitleWidgetSpecification;

		return true;
	}

	return false;
}
