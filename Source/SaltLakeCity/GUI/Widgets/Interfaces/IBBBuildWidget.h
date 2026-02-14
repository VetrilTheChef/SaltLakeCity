// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBBuildWidget.generated.h"

/**
 * 
 */

class UIBBBuildEntry;
class UIBBTitleWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildWidget : public UIBBWidget
{
	GENERATED_BODY()

	public:
		UIBBBuildWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeDestruct() override
			{ Super::NativeDestruct(); };

		virtual void NativeOnInitialized() override
			{ Super::NativeOnInitialized(); };

		virtual EBBWidget GetType() const
			PURE_VIRTUAL(UIBBBuildWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBuildWidget::AddToScreen, );

		virtual void Bind()
			PURE_VIRTUAL(UIBBBuildWidget::Bind, );

		virtual void Unbind()
			PURE_VIRTUAL(UIBBBuildWidget::Unbind, );

		virtual void AddEntry(EBBBuildCategory Category, UIBBBuildEntry*& NewEntry)
			PURE_VIRTUAL(UIBBBuildWidget::AddEntry, );

		virtual void ClearEntries(EBBBuildCategory Category)
			PURE_VIRTUAL(UIBBBuildWidget::ClearEntries, );
};