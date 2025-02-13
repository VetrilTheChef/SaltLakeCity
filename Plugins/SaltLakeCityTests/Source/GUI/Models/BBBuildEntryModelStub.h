// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBBuildEntryModel.h"
#include "BBBuildEntryModelStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBBuildEntryModelStub : public UIBBBuildEntryModel
{
	GENERATED_BODY()

	public:
		UBBBuildEntryModelStub();
		
		virtual UIBBWidget * GetWidget() const;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBBuildEntryWidget * NewView, const UIBBBuildEntry * NewEntry) override;

		virtual void Finalize() override;

		virtual const FText GetEntryName() const override;

		void SetEntryName(const FText NewName);

		virtual const TSoftObjectPtr<UTexture2D> GetEntryIcon() const override;

		void SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon);

		virtual const float GetEntryPrice() const override;

		void SetEntryPrice(const float NewPrice);

		virtual const float GetEntryTime() const override;

		void SetEntryTime(const float NewTime);

		virtual const TSoftClassPtr<UIBBBuildData> GetEntryBuildDataClass() const override;

		void SetEntryBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass);

		virtual const TSoftClassPtr<AIBBTargetingActor> GetEntryTargetingClass() const override;

		void SetEntryTargetingClass(const TSoftClassPtr<AIBBTargetingActor> NewTargetingClass);

		virtual const TArray<FBBBuildablePtr> GetEntryBuildableClasses() const override;

		void SetEntryBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses);

	protected:
		UPROPERTY()
		UIBBBuildEntryWidget * View;

		UPROPERTY()
		TSoftObjectPtr<UTexture2D> EntryIcon;

		UPROPERTY()
		TSoftClassPtr<AIBBTargetingActor> TargetingClass;

		UPROPERTY()
		TSoftClassPtr<UIBBBuildData> BuildDataClass;

		UPROPERTY()
		TArray<FBBBuildablePtr> BuildableClasses;

		FText EntryName;

		float EntryPrice;

		float EntryTime;
};