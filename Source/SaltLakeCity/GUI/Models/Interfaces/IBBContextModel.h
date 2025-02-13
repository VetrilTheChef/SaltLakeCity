// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBContextRowData.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Models/Interfaces/IBBTargetedModel.h"
#include "IBBContextModel.generated.h"

/**
 * 
 */

class AIBBHUD;
class UDataTable;
class UIBBContextWidget;
class UIBBWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBContextModel : public UIBBTargetedModel
{
	GENERATED_BODY()

	public:
		UIBBContextModel() : Super() { };

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const PURE_VIRTUAL(UIBBContextModel::GetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBContextModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBContextModel::GetWidgetSpecification, return nullptr; );

		virtual UIBBWidgetSpecification * GetRowWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, int RowIndex) PURE_VIRTUAL(UIBBContextModel::GetRowWidgetSpecification, return nullptr; );

		virtual UDataTable * GetDataTable() PURE_VIRTUAL(UIBBContextModel::GetDataTable, return nullptr; );

		virtual void Initialize(UIBBContextWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table) PURE_VIRTUAL(UIBBContextModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBContextModel::Finalize, );

		virtual int GetNumRows() PURE_VIRTUAL(UIBBContextModel::GetNumRows, return 0; );

		virtual FBBContextRowData GetRowData(int Index) PURE_VIRTUAL(UIBBContextModel::GetRowData, return FBBContextRowData(); );

		virtual bool GetRowVisibility(EBBContext RowContextType) const PURE_VIRTUAL(UIBBContextModel::GetRowVisibility, return false; );

		DECLARE_EVENT(UIBBContextModel, FBBContextUpdate);

		FBBContextUpdate & OnContextUpdate() { return UpdateContext; };

	protected:
		FBBContextUpdate UpdateContext;
};