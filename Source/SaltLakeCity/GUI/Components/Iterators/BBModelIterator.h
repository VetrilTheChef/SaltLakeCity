// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Iterators/Interfaces/IBBModelIterator.h"
#include "BBModelIterator.generated.h"

/**
 *
 */

class UIBBGUIModel;
class UIBBGUIModelContainer;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBModelIterator : public UIBBModelIterator
{
	GENERATED_BODY()

	public:
		UBBModelIterator();

		virtual void SetModelContainer(UIBBGUIModelContainer * NewModelContainer) override;

		virtual bool HasNext() const override;

		virtual UIBBGUIModel * Next() const override;

	protected:
		UPROPERTY()
		UIBBGUIModelContainer * ModelContainer;

		UPROPERTY()
		mutable int Index;
};