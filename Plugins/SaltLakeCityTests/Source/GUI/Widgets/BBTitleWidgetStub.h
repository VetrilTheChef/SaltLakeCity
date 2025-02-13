// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "BBTitleWidgetStub.generated.h"

/**
 * 
 */

class UIBBButton;
class UIBBCommand;
class UTexture2D;

UCLASS(NotBlueprintable)

class UBBTitleWidgetStub : public UIBBTitleWidget
{
	GENERATED_BODY()

	public:
		UBBTitleWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual EBBWidget GetType() const override;

		virtual void SetCloseCommand(UIBBCommand * NewCommand) override;

		void Drag(FVector2D NewPosition);

		FVector2D GetPosition() const;

	protected:
		UPROPERTY()
		UTexture2D * Icon;

		UPROPERTY()
		FText Text;

		UPROPERTY()
		UIBBCommand * CloseCommand;

		UPROPERTY()
		FVector2D Position;
};