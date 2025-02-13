// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Specifications/Factories/Interfaces/IBBSpecificationFactory.h"
#include "BBSpecificationFactory.generated.h"

/**
 * 
 */

class IBBWidgetSpecificationVisitor;
class UBBHasBuildableSurfaceSpecification;
class UBBHasDossierSpecification;
class UBBHasInventorySpecification;
class UBBHasJobSpecification;
class UIBBCompositeWidgetSpecification;
class UIBBTargetSpecification;
class UIBBWidgetTargetSpecification;

typedef void (UBBSpecificationFactory::* SpecificationConstructor) (UIBBCompositeWidgetSpecification * & Specification, UObject * Outer) const;

USTRUCT()

struct FBBSpecificationConstructors
{
	GENERATED_BODY()

	public:
		TArray<SpecificationConstructor> Pointers;

		FBBSpecificationConstructors()
		{
			Pointers.Empty();
		};

		~FBBSpecificationConstructors()
		{
			Pointers.Empty();
		};
};

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBSpecificationFactory : public UIBBSpecificationFactory
{
	GENERATED_BODY()

	public:
		UBBSpecificationFactory();

		virtual void PostInitProperties() override;
		
		virtual void BeginDestroy() override;

		virtual bool NewHasBuildableSurfaceSpecification(UBBHasBuildableSurfaceSpecification * & Specification, UObject * Outer) override;

		virtual bool NewHasDossierSpecification(UBBHasDossierSpecification * & Specification, UObject * Outer) override;

		virtual bool NewHasInventorySpecification(UBBHasInventorySpecification * & Specification, UObject * Outer) override;

		virtual bool NewHasJobSpecification(UBBHasJobSpecification * & Specification, UObject * Outer) override;

		virtual bool NewTargetSpecification(UIBBTargetSpecification * & Specification, UObject * Outer, UObject * Target) const override;

		virtual bool NewWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer, EBBWidget WidgetType, IBBWidgetSpecificationVisitor & Visitor) const override;

		virtual bool NewJobWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer) const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UBBHasBuildableSurfaceSpecification> HasBuildableSurfaceSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UBBHasDossierSpecification> HasDossierSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UBBHasInventorySpecification> HasInventorySpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UBBHasJobSpecification> HasJobSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBTargetSpecification> TargetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBWidgetSpecification> WidgetSpecificationClass;

		//UPROPERTY(EditDefaultsOnly, Category = "Classes")
		//TSoftClassPtr<UIBBWidgetTargetSpecification> WidgetTargetSpecificationClass;

		UPROPERTY()
		TMap<EBBWidget, FBBSpecificationConstructors> ConstructorsMap;

		void MapSpecificationConstructors();

		void AddTargetSpecification(UIBBCompositeWidgetSpecification * & Specification, UObject * Outer) const;
};