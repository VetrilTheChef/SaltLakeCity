// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBContextRowData.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "BBContextModel.generated.h"

/**
 * 
 */

typedef UIBBWidgetSpecification * (UBBContextModel::* RowWidgetSpecificator) (const UIBBWidgetSpecificationFactory &, FBBContextRowData);

USTRUCT()

struct FBBRowWidgetSpecificator
{
	GENERATED_BODY()

	public:
		FBBRowWidgetSpecificator()
		{
			Specificator = nullptr;
		};

		FBBRowWidgetSpecificator(RowWidgetSpecificator NewSpecificator) :
			Specificator(NewSpecificator)
		{
		};

		RowWidgetSpecificator Specificator;
};

class UDataTable;
class UIBBContextComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBContextModel : public UIBBContextModel
{
	GENERATED_BODY()

	public:
		UBBContextModel();

		virtual void PostInitProperties() override;

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual UIBBWidgetSpecification * GetRowWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, int RowIndex) override;

		virtual UDataTable * GetDataTable() override;

		virtual void Initialize(UIBBContextWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table) override;

		virtual void Finalize() override;

		virtual int GetNumRows() override;

		virtual FBBContextRowData GetRowData(int Index) override;

		virtual bool GetRowVisibility(EBBContext RowContextType) const override;

	protected:
		UPROPERTY(Category = "Data Table", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> TableAsset;

		UPROPERTY()
		UIBBContextWidget * View;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBContextComponent * Component;

		UPROPERTY()
		TArray<FBBContextRowData> ContextRows;

		UPROPERTY()
		TMap<EBBWidget, FBBRowWidgetSpecificator> RowWidgetSpecificators;

		void InitializeRows(UDataTable * Table);

		void InitializeView(UIBBContextWidget * NewView);

		void InitializeHUD(AIBBHUD * NewHUD);

		void InitializeComponent(UIBBContextComponent * NewContextComponent);

		void FinalizeRows();

		void FinalizeView();
		
		void FinalizeHUD();

		void FinalizeComponent();

		UIBBWidgetSpecification * NewNoWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewBuildWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewContextWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewDateTimeWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewDossierWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewJobWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewModesWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewProgressWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewSelectionWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UIBBWidgetSpecification * NewTitleWidgetSpecification(const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory, FBBContextRowData RowData);

		UFUNCTION()
		void UpdateContext(UIBBContextComponent * NewContextComponent);
};