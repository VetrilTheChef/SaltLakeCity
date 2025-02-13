// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBSkillEntryModel.generated.h"

/**
 *
 */

class UIBBSkillEntry;
class UIBBSkillEntryWidget;
class UTexture2D;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSkillEntryModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBSkillEntryModel() : Super() { };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBSkillEntryModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBSkillEntryModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBSkillEntryWidget * NewView, const UIBBSkillEntry * NewEntry) PURE_VIRTUAL(UIBBSkillEntryModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBSkillEntryModel::Finalize, );

		virtual const FText GetEntryName() const PURE_VIRTUAL(UIBBSkillEntryModel::GetEntryName, return FText::FromString(""); );

		virtual const TSoftObjectPtr<UTexture2D> GetEntryIcon() const PURE_VIRTUAL(UIBBSkillEntryModel::GetEntryIcon, return TSoftObjectPtr<UTexture2D>(); );

		virtual const float GetEntryValue() const PURE_VIRTUAL(UIBBSkillEntryModel::GetEntryValue, return -1.0f; );

		virtual const float GetEntryMaxValue() const PURE_VIRTUAL(UIBBSkillEntryModel::GetEntryMaxValue, return -1.0f; );

		DECLARE_EVENT(UIBBSkillEntryModel, FBBValueUpdate);

		FBBValueUpdate & OnValueUpdate() { return UpdateValue; };

		DECLARE_EVENT(UIBBSkillEntryModel, FBBMaxValueUpdate);

		FBBMaxValueUpdate & OnMaxValueUpdate() { return UpdateMaxValue; };

	protected:
		FBBValueUpdate UpdateValue;

		FBBMaxValueUpdate UpdateMaxValue;
};