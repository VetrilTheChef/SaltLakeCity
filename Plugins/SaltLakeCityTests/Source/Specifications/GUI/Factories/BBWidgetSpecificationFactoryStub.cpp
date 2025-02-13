// SaltLakeCity 4.26

#include "BBWidgetSpecificationFactoryStub.h"
#include "Specifications/GUI/Interfaces/IBBBuildWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBContextWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBDateTimeWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBDossierWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBJobWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBModesWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBProgressWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBSelectionWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBTitleWidgetSpecification.h"

UBBWidgetSpecificationFactoryStub::UBBWidgetSpecificationFactoryStub() :
	Super()
{
	WidgetSpecifications.Empty();
}

void UBBWidgetSpecificationFactoryStub::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBWidgetSpecificationFactoryStub::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBBWidgetSpecificationFactoryStub::AddWidgetSpecification(UIBBWidgetSpecification * WidgetSpecification)
{
	WidgetSpecifications.EmplaceAt(0, WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewBuildWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? WidgetSpecifications.Pop() : nullptr;
	
	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewContextWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? WidgetSpecifications.Pop() : nullptr;

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewDateTimeWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? WidgetSpecifications.Pop() : nullptr;

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewDossierWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? Cast<UIBBTargetedWidgetSpecification>(WidgetSpecifications.Pop()) : nullptr;

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewJobWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? Cast<UIBBTargetedWidgetSpecification>(WidgetSpecifications.Pop()) : nullptr;

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewModesWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? WidgetSpecifications.Pop() : nullptr;

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewProgressWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? WidgetSpecifications.Pop() : nullptr;

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewSelectionWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? WidgetSpecifications.Pop() : nullptr;

	return IsValid(WidgetSpecification);
}

bool UBBWidgetSpecificationFactoryStub::NewTitleWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const
{
	WidgetSpecification = WidgetSpecifications.Num() > 0 ? Cast<UIBBTargetedWidgetSpecification>(WidgetSpecifications.Pop()) : nullptr;

	return IsValid(WidgetSpecification);
}
