// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "BBTitleWidget.generated.h"

/**
 * 
 */

class UIBBButton;
class UIBBCommand;
class UIBBWidget;
class UImage;
class UTextBlock;
class UTexture2D;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBTitleWidget : public UIBBTitleWidget
{
	GENERATED_BODY()

	public:
		UBBTitleWidget(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual EBBWidget GetType() const override;

		virtual void SetCloseCommand(UIBBCommand * NewCommand) override;

	protected:
		UPROPERTY(Category = "Title", EditAnywhere, BlueprintReadWrite)
		UTexture2D * Icon;

		UPROPERTY(Category = "Title", EditAnywhere, BlueprintReadWrite)
		FText Text;

		UPROPERTY(meta = (BindWidget))
		UImage * TitleIcon;

		UPROPERTY(meta = (BindWidget))
		UTextBlock * TitleText;

		UPROPERTY(meta = (BindWidget))
		UIBBButton * CloseButton;

		UPROPERTY()
		FVector2D DragOffset;

		virtual void NativeOnDragCancelled(const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override;

		virtual void NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent, UDragDropOperation * & OutOperation) override;

		virtual FReply NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

		virtual FReply NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

		void InitializeTitle();

		void InitializeIcon();

		void InitializeText();

		bool ClampPosition(FVector2D & Position, FVector2D Min, FVector2D Max);
};