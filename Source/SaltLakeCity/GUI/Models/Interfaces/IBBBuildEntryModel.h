// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBBuildEntryModel.generated.h"

/**
 * 
 */

class AIBBTargetingActor;
class UIBBBuildEntry;
class UIBBBuildEntryWidget;
class UIBBBuildData;
class UTexture2D;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildEntryModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBBuildEntryModel() : Super() { };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBBuildEntryModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBBuildEntryModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBBuildEntryWidget * NewView, const UIBBBuildEntry * NewEntry) PURE_VIRTUAL(UIBBBuildEntryModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBBuildEntryModel::Finalize, );

		virtual const FText GetEntryName() const PURE_VIRTUAL(UIBBBuildEntryModel::GetEntryName, return FText::FromString(""); );

		virtual const TSoftObjectPtr<UTexture2D> GetEntryIcon() const PURE_VIRTUAL(UIBBBuildEntryModel::GetEntryIcon, return TSoftObjectPtr<UTexture2D>(); );

		virtual const float GetEntryPrice() const PURE_VIRTUAL(UIBBBuildEntryModel::GetEntryPrice, return -1.0f; );

		virtual const float GetEntryTime() const PURE_VIRTUAL(UIBBBuildEntryModel::GetEntryTime, return -1.0f; );

		virtual const TSoftClassPtr<UIBBBuildData> GetEntryBuildDataClass() const PURE_VIRTUAL(UIBBBuildEntryModel::GetEntryBuildDataClass, return TSoftClassPtr<UIBBBuildData>(); );

		virtual const TSoftClassPtr<AIBBTargetingActor> GetEntryTargetingClass() const PURE_VIRTUAL(UIBBBuildEntryModel::GetEntryTargetingClass, return TSoftClassPtr<AIBBTargetingActor>(); );
		
		virtual const TArray<FBBBuildablePtr> GetEntryBuildableClasses() const PURE_VIRTUAL(UIBBBuildEntryModel::GetEntryBuildableClasses, return TArray<FBBBuildablePtr>(); );
};