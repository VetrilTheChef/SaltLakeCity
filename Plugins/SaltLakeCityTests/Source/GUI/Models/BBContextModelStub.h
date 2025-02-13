// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBContextRowData.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "BBContextModelStub.generated.h"

/**
 * 
 */

class AIBBHUD;
class UIBBContextComponent;

UCLASS(NotBlueprintable)

class UBBContextModelStub : public UIBBContextModel
{
	GENERATED_BODY()

	public:
		UBBContextModelStub();

		virtual void PostInitProperties() override;

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		void SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

		virtual UIBBWidgetSpecification * GetRowWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, int RowIndex) override;

		void SetRowWidgetSpecification(UIBBWidgetSpecification * NewRowWidgetSpecification);

		virtual UDataTable * GetDataTable() override;

		virtual void Initialize(UIBBContextWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table) override;

		virtual void Finalize() override;

		const UIBBContextComponent * GetComponent() const;

		virtual void AddRow(FText NewName, UClass * NewSpecification, UTexture2D * NewIcon, FText NewTooltip, EBBContext NewContextType, EBBWidget NewWidgetType);

		virtual int GetNumRows() override;

		virtual FBBContextRowData GetRowData(int Index) override;

	protected:
		UPROPERTY()
		UIBBContextWidget * View;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		TArray<FBBContextRowData> Rows;

		UPROPERTY()
		const UIBBContextComponent * ContextComponent;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;

		UPROPERTY()
		UIBBWidgetSpecification * RowWidgetSpecification;

		UFUNCTION()
		void UpdateContext(UIBBContextComponent * NewContextComponent);
};