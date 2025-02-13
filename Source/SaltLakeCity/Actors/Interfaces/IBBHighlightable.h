// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBBHighlightable.generated.h"

class UIBBDecalComponent;

UINTERFACE(MinimalAPI)

class UBBHighlightable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class SALTLAKECITY_API IBBHighlightable
{
	GENERATED_BODY()

	public:
		virtual void UpdateHighlight(bool Highlighted) PURE_VIRTUAL(IBBHighlightable::UpdateHighlight, );
		
		virtual UIBBDecalComponent * GetDecalComponent() const PURE_VIRTUAL(IBBSelectable::GetContextComponent, return nullptr; );

		virtual AActor * ToActor() PURE_VIRTUAL(IBBHighlightable::ToActor, return nullptr; );

		DECLARE_EVENT_OneParam(IBBHighlightable, FBBHighlightUpdate, bool);

		virtual FBBHighlightUpdate & OnHighlightUpdate() = 0;
};