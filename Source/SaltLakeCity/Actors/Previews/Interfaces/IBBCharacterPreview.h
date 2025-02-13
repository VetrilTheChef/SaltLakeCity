// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "IBBCharacterPreview.generated.h"

/**
*
*/

class AIBBCharacter;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBCharacterPreview : public ASkeletalMeshActor
{
	GENERATED_BODY()

	public:
		AIBBCharacterPreview() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void CreatePreview(const AIBBCharacter * TemplateCharacter) PURE_VIRTUAL(AIBBCharacterPreview::CreatePreview, );

		virtual void ShowActors(TArray<AActor *> Actors) PURE_VIRTUAL(AIBBCharacterPreview::ShowActors, );

		virtual UTexture * GetPreview() PURE_VIRTUAL(AIBBCharacterPreview::GetPreview, return nullptr; );
};