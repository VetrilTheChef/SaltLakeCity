// SaltLakeCity 4.25

#include "BBSpecificationFactoryStub.h"
#include "Specifications/Actors/BBHasBuildableSurfaceSpecification.h"
#include "Specifications/Actors/BBHasDossierSpecification.h"
#include "Specifications/Actors/BBHasInventorySpecification.h"
#include "Specifications/Actors/BBHasJobSpecification.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecificationVisitor.h"
#include "Specifications/Targets/Interfaces/IBBTargetSpecification.h"

UBBSpecificationFactoryStub::UBBSpecificationFactoryStub() :
	Super()
{
	TargetSpecifications.Empty();
	WidgetSpecifications.Empty();
}

void UBBSpecificationFactoryStub::PostInitProperties()
{
	Super::PostInitProperties();
}

bool UBBSpecificationFactoryStub::NewHasBuildableSurfaceSpecification(UBBHasBuildableSurfaceSpecification * & Specification, UObject * Outer)
{
	Specification = nullptr;

	return false;
}

bool UBBSpecificationFactoryStub::NewHasDossierSpecification(UBBHasDossierSpecification * & Specification, UObject * Outer)
{
	Specification = nullptr;

	return false;
}

bool UBBSpecificationFactoryStub::NewHasInventorySpecification(UBBHasInventorySpecification * & Specification, UObject * Outer)
{
	Specification = nullptr;

	return false;
}

bool UBBSpecificationFactoryStub::NewHasJobSpecification(UBBHasJobSpecification * & Specification, UObject * Outer)
{
	Specification = nullptr;

	return false;
}

void UBBSpecificationFactoryStub::AddTargetSpecification(UIBBTargetSpecification * NewTargetSpecification)
{
	TargetSpecifications.Emplace(NewTargetSpecification);
}

bool UBBSpecificationFactoryStub::NewTargetSpecification(UIBBTargetSpecification * & Specification, UObject * Outer, UObject * Target) const
{
	Specification = TargetSpecifications.Num() > 0 ? TargetSpecifications.Pop() : nullptr;

	if (IsValid(Specification))
	{
		Specification->SetTarget(Target);

		return true;
	}

	return false;
}

void UBBSpecificationFactoryStub::AddWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecifications.Emplace(NewWidgetSpecification);
}

bool UBBSpecificationFactoryStub::NewWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer, EBBWidget WidgetType, IBBWidgetSpecificationVisitor & Visitor) const
{
	Specification = WidgetSpecifications.Num() > 0 ? WidgetSpecifications.Pop() : nullptr;

	if (IsValid(Specification))
	{
		//Specification->Accept(Visitor);

		//return true;
	}

	return false;
}
