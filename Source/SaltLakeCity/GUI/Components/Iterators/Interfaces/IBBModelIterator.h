// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Includes/BBGUIModelContainers.h"
#include "IBBModelIterator.generated.h"

/**
 *
 */

class UIBBGUIModel;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBModelIterator : public UObject
{
	GENERATED_BODY()

	public:
		UIBBModelIterator() : Super() { };

		virtual void SetModelContainer(UIBBGUIModelContainer * NewModelContainer) PURE_VIRTUAL(UIBBModelIterator::SetModelContainer, );

		virtual bool HasNext() const PURE_VIRTUAL(UIBBModelIterator::HasNext, return false; );

		virtual UIBBGUIModel * Next() const PURE_VIRTUAL(UIBBModelIterator::Next, return nullptr; );
};