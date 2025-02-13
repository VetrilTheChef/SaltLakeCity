// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBGUIController.generated.h"

/**
 * 
 */

class UBBGUIModel;
class UBBWidget;

UCLASS(Abstract)

class SALTLAKECITY_API UBBGUIController : public UObject
{
	GENERATED_BODY()
	
	public:
		UBBGUIController();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;
};