// SaltLakeCity 4.26

#include "BBSpecificationFactory.h"
#include "Specifications/Actors/BBHasBuildableSurfaceSpecification.h"
#include "Specifications/Actors/BBHasDossierSpecification.h"
#include "Specifications/Actors/BBHasInventorySpecification.h"
#include "Specifications/Actors/BBHasJobSpecification.h"
#include "Specifications/Targets/Interfaces/IBBTargetSpecification.h"

UBBSpecificationFactory::UBBSpecificationFactory() :
	Super()
{
	ConstructorsMap.Empty();
}

void UBBSpecificationFactory::PostInitProperties()
{
	Super::PostInitProperties();

	MapSpecificationConstructors();
}

void UBBSpecificationFactory::BeginDestroy()
{
	Super::BeginDestroy();
}

bool UBBSpecificationFactory::NewHasBuildableSurfaceSpecification(UBBHasBuildableSurfaceSpecification * & Specification, UObject * Outer)
{
	verifyf(!HasBuildableSurfaceSpecificationClass.IsNull(), TEXT("Has Buildable Surface Specification class is null."));

	Specification = NewObject<UBBHasBuildableSurfaceSpecification>(Outer, HasBuildableSurfaceSpecificationClass.LoadSynchronous());

	return IsValid(Specification);
}

bool UBBSpecificationFactory::NewHasDossierSpecification(UBBHasDossierSpecification * & Specification, UObject * Outer)
{
	verifyf(!HasDossierSpecificationClass.IsNull(), TEXT("Has Dossier Specification class is null."));
	
	Specification = NewObject<UBBHasDossierSpecification>(Outer, HasDossierSpecificationClass.LoadSynchronous());

	return IsValid(Specification);
}

bool UBBSpecificationFactory::NewHasInventorySpecification(UBBHasInventorySpecification * & Specification, UObject * Outer)
{
	verifyf(!HasInventorySpecificationClass.IsNull(), TEXT("Has Inventory Specification class is null."));

	Specification = NewObject<UBBHasInventorySpecification>(Outer, HasInventorySpecificationClass.LoadSynchronous());

	return IsValid(Specification);
}

bool UBBSpecificationFactory::NewHasJobSpecification(UBBHasJobSpecification * & Specification, UObject * Outer)
{
	verifyf(!HasJobSpecificationClass.IsNull(), TEXT("Has Job Specification class is null."));

	Specification = NewObject<UBBHasJobSpecification>(Outer, HasJobSpecificationClass.LoadSynchronous());

	return IsValid(Specification);
}

bool UBBSpecificationFactory::NewTargetSpecification(UIBBTargetSpecification * & Specification, UObject * Outer, UObject * Target) const
{
	verifyf(!TargetSpecificationClass.IsNull(), TEXT("Target Specification class is null."));

	Specification = NewObject<UIBBTargetSpecification>(Outer, TargetSpecificationClass.LoadSynchronous());

	if (IsValid(Specification))
	{
		Specification->SetTarget(Target);

		return true;
	}

	return false;
}

bool UBBSpecificationFactory::NewWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer, EBBWidget WidgetType, IBBWidgetSpecificationVisitor & Visitor) const
{
	/*verifyf(!WidgetSpecificationClass.IsNull(), TEXT("Widget Specification class is null."));

	Specification = NewObject<UIBBWidgetSpecification>(Outer, WidgetSpecificationClass.LoadSynchronous());

	if (IsValid(Specification))
	{
		Specification->SetWidgetType(WidgetType);

		FBBSpecificationConstructors Constructors = ConstructorsMap.FindRef(WidgetType);

		TArray<SpecificationConstructor> Pointers = Constructors.Pointers;

		for (auto& Pointer : Pointers)
		{
			(this->* Pointer)(Specification, Outer);
		}

		Specification->Accept(Visitor);

		return true;
	}*/

	return false;
}

bool UBBSpecificationFactory::NewJobWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer) const
{
	/*verifyf(!WidgetSpecificationClass.IsNull(), TEXT("Widget Specification class is null."));

	Specification = NewObject<UIBBWidgetSpecification>(Outer, WidgetSpecificationClass.LoadSynchronous());

	if (IsValid(Specification))
	{
		Specification->SetWidgetType(EBBWidget::Job);

		FBBSpecificationConstructors Constructors = ConstructorsMap.FindRef(EBBWidget::Job);

		TArray<SpecificationConstructor> Pointers = Constructors.Pointers;

		for (auto& Pointer : Pointers)
		{
			(this->*Pointer)(Specification, Outer);
		}

		return true;
	}*/

	return false;
}



void UBBSpecificationFactory::MapSpecificationConstructors()
{
	ConstructorsMap.Empty();
	ConstructorsMap.Emplace(EBBWidget::Build, FBBSpecificationConstructors());
	ConstructorsMap.Emplace(EBBWidget::BuildEntry, FBBSpecificationConstructors());
	ConstructorsMap.Emplace(EBBWidget::Context, FBBSpecificationConstructors());
	ConstructorsMap.Emplace(EBBWidget::DateTime, FBBSpecificationConstructors());
	ConstructorsMap.Emplace(EBBWidget::Job, FBBSpecificationConstructors());
	ConstructorsMap.Emplace(EBBWidget::None, FBBSpecificationConstructors());
	ConstructorsMap.Emplace(EBBWidget::Progress, FBBSpecificationConstructors());
	ConstructorsMap.Emplace(EBBWidget::Title, FBBSpecificationConstructors());
}

void UBBSpecificationFactory::AddTargetSpecification(UIBBCompositeWidgetSpecification * & Specification, UObject * Outer) const
{
	//verifyf(!WidgetTargetSpecificationClass.IsNull(), TEXT("Widget Target Specification class is null."));

	//Specification->AddSpecification(NewObject<UIBBWidgetTargetSpecification>(Outer, WidgetTargetSpecificationClass.LoadSynchronous()));
}