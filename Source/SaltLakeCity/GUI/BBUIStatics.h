// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BBUIStatics.generated.h"

/**
 *
 */

class UIBBWidget;

UCLASS()

class SALTLAKECITY_API UBBUIStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
		static FVector2D GetPopUpCoordinates(const UWorld* World, const UIBBWidget* Widget);

		static bool ConvertToPIEViewportSpace(const UWorld* World, FVector2D& Position);
};