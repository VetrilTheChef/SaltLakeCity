// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBBuildModel.generated.h"

/**
 * 
 */

class UIBBBuildEntry;
class UIBBBuildWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBBuildModel() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBBuildModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBBuildModel::GetWidgetSpecification, return nullptr; );

		virtual UDataTable * GetDataTable() PURE_VIRTUAL(UIBBBuildModel::GetDataTable, return nullptr; );

		virtual TSoftClassPtr<UIBBBuildEntry> GetEntryClass() PURE_VIRTUAL(UIBBBuildModel::GetEntryClass, return nullptr; );

		virtual void Initialize(UIBBBuildWidget * NewView, UDataTable * Table, TSoftClassPtr<UIBBBuildEntry> NewBuildEntryClass) PURE_VIRTUAL(UIBBBuildModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBBuildModel::Finalize, );

		virtual int GetNumEntries(EBBBuildCategory Category) PURE_VIRTUAL(UIBBBuildModel::GetNumEntries, return -1; );

		virtual UIBBBuildEntry * GetEntry(EBBBuildCategory Category, int Index) PURE_VIRTUAL(UIBBBuildModel::GetEntry, return nullptr; );
};