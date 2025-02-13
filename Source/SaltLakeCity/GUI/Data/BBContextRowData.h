// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "BBContextRowData.generated.h"

/**
 * 
 */

class UTexture2D;

USTRUCT()

struct FBBContextRowData
{
	GENERATED_BODY()

	public:
		FText Name;

		UPROPERTY()
		UClass * Specification;

		UPROPERTY()
		UTexture2D * Icon;

		FText Tooltip;

		EBBContext ContextType;

		EBBWidget WidgetToOpen;

		FBBContextRowData() :
			Name(FText::FromString("")),
			Specification(nullptr),
			Icon(nullptr),
			Tooltip(FText::FromString("")),
			ContextType(EBBContext::None),
			WidgetToOpen(EBBWidget::None)
		{
		}

		FBBContextRowData(FText NewName,
						  UClass * NewSpecification,
						  UTexture2D * NewIcon,
						  FText NewTooltip,
						  EBBContext NewContextType,
						  EBBWidget NewWidgetToOpen) :
			Name(NewName),
			Specification(NewSpecification),
			Icon(NewIcon),
			Tooltip(NewTooltip),
			ContextType(NewContextType),
			WidgetToOpen(NewWidgetToOpen)
		{
		}

		~FBBContextRowData()
		{
			Name = FText::FromString("");
			Specification = nullptr;
			Icon = nullptr;
			Tooltip = FText::FromString("");
			ContextType = EBBContext::None;
			WidgetToOpen = EBBWidget::None;
		}
};