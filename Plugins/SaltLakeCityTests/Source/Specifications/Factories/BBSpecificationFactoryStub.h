// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Specifications/Factories/Interfaces/IBBSpecificationFactory.h"
#include "BBSpecificationFactoryStub.generated.h"

/**
 * 
 */

class UBBActorSpecification;
class UBBHasBuildableSurfaceSpecification;
class UBBHasDossierSpecification;
class UBBHasInventorySpecification;
class UBBHasJobSpecification;
class UIBBTargetSpecification;
class UIBBWidgetSpecification;

UCLASS(NotBlueprintable)

class UBBSpecificationFactoryStub : public UIBBSpecificationFactory
{
	GENERATED_BODY()

	public:
		UBBSpecificationFactoryStub();

		virtual void PostInitProperties() override;

		virtual bool NewHasBuildableSurfaceSpecification(UBBHasBuildableSurfaceSpecification * & Specification, UObject * Outer) override;

		virtual bool NewHasDossierSpecification(UBBHasDossierSpecification * & Specification, UObject * Outer) override;

		virtual bool NewHasInventorySpecification(UBBHasInventorySpecification * & Specification, UObject * Outer) override;

		virtual bool NewHasJobSpecification(UBBHasJobSpecification * & Specification, UObject * Outer) override;

		virtual void AddTargetSpecification(UIBBTargetSpecification * NewTargetSpecification);

		virtual bool NewTargetSpecification(UIBBTargetSpecification * & Specification, UObject * Outer, UObject * Target) const override;
		
		virtual void AddWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

		virtual bool NewWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer, EBBWidget WidgetType, IBBWidgetSpecificationVisitor & Visitor) const override;

	protected:
		UPROPERTY()
		mutable TArray<UIBBTargetSpecification *> TargetSpecifications;

		UPROPERTY()
		mutable TArray<UIBBWidgetSpecification *> WidgetSpecifications;
};