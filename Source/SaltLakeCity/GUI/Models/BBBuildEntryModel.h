// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBBuildEntryModel.h"
#include "BBBuildEntryModel.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildEntryModel : public UIBBBuildEntryModel
{
	GENERATED_BODY()

	public:
		UBBBuildEntryModel();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBBuildEntryWidget * NewView, const UIBBBuildEntry * NewEntry) override;

		virtual void Finalize() override;

		virtual const FText GetEntryName() const override;

		virtual const TSoftObjectPtr<UTexture2D> GetEntryIcon() const override;

		virtual const float GetEntryPrice() const override;

		virtual const float GetEntryTime() const override;

		virtual const TSoftClassPtr<UIBBBuildData> GetEntryBuildDataClass() const override;

		virtual const TSoftClassPtr<AIBBTargetingActor> GetEntryTargetingClass() const override;
		
		virtual const TArray<FBBBuildablePtr> GetEntryBuildableClasses() const override;

	protected:
		UPROPERTY(Category = "Classes", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSoftClassPtr<AIBBTargetingActor> TargetingClass;

		UPROPERTY()
		UIBBBuildEntryWidget * View;

		UPROPERTY()
		const UIBBBuildEntry * Entry;

		void InitializeEntry(const UIBBBuildEntry * NewEntry);

		void FinalizeEntry();

		void InitializeView(UIBBBuildEntryWidget * NewView, const UIBBBuildEntry & BuildEntry);

		void FinalizeView();
};