// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBDossierEntryModel.generated.h"

/**
 * 
 */

class UIBBDossierEntry;
class UIBBDossierEntryWidget;
class UTexture2D;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierEntryModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBDossierEntryModel() : Super() { };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBDossierEntryModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBDossierEntryModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBDossierEntryWidget * NewView, UIBBDossierEntry * Entry) PURE_VIRTUAL(UIBBDossierEntryModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBDossierEntryModel::Finalize, );

		virtual FText GetEntryName() const PURE_VIRTUAL(UIBBDossierEntryModel::GetEntryName, return FText::FromString(""); );

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const PURE_VIRTUAL(UIBBDossierEntryModel::GetIcon, return TSoftObjectPtr<UTexture2D>(); );

		virtual float GetValue() const PURE_VIRTUAL(UIBBDossierEntryModel::GetValue, return -1.0f; );

		virtual float GetMaxValue() const PURE_VIRTUAL(UIBBDossierEntryModel::GetMaxValue, return -1.0f; );

		DECLARE_EVENT_OneParam(UIBBDossierEntryModel, FBBValueUpdate, float);

		FBBValueUpdate & OnValueUpdate() { return ValueUpdate; };

		DECLARE_EVENT_OneParam(UIBBDossierEntryModel, FBBMaxValueUpdate, float);

		FBBMaxValueUpdate & OnMaxValueUpdate() { return MaxValueUpdate; };

	protected:
		FBBValueUpdate ValueUpdate;

		FBBMaxValueUpdate MaxValueUpdate;
};