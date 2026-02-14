// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Containers/SortedMap.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "BBBuildWidget.generated.h"

/**
 * 
 */

class UIBBBuildEntry;
class UIBBRadioBox;
class UIBBWidgetFactory;
class UTileView;
class UWidgetSwitcher;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildWidget : public UIBBBuildWidget
{
	GENERATED_BODY()

	public:
		UBBBuildWidget(const FObjectInitializer& ObjectInitializer);

		virtual void NativeDestruct() override;

		virtual void NativeOnInitialized() override;

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		virtual void AddEntry(EBBBuildCategory Category, UIBBBuildEntry*& NewEntry) override;

		virtual void ClearEntries(EBBBuildCategory Category) override;

	protected:
		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox* Tab0;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox* Tab1;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox* Tab2;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox* Tab3;

		TSortedMap<EBBBuildCategory, UIBBRadioBox *, FDefaultAllocator, TLess<EBBBuildCategory>> Tabs;

		UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* CategorySwitcher;

		UPROPERTY(meta = (BindWidget))
		UTileView* Tile0;

		UPROPERTY(meta = (BindWidget))
		UTileView* Tile1;

		UPROPERTY(meta = (BindWidget))
		UTileView* Tile2;

		UPROPERTY(meta = (BindWidget))
		UTileView* Tile3;

		TSortedMap<EBBBuildCategory, UTileView *> Tiles;

		void InitializeTabs();

		void InitializeTiles();

		void FinalizeTabs();

		void FinalizeTiles();

		UFUNCTION()
		void ChangeRadioState(int Index);
};