// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Previews/Interfaces/IBBCharacterPreview.h"
#include "BBCharacterPreviewStub.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType)

class ABBCharacterPreviewStub : public AIBBCharacterPreview
{
	GENERATED_BODY()

	public:
		ABBCharacterPreviewStub();

		virtual void CreatePreview(const AIBBCharacter * TemplateCharacter) override;
		
		virtual void ShowActors(TArray<AActor *> Actors) override;
};