// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Components/DecalComponent.h"
#include "IBBDecalComponent.generated.h"

class IBBActorComponentVisitor;
class IBBHighlightable;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDecalComponent : public UDecalComponent
{
	GENERATED_BODY()

	public:	
		UIBBDecalComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(TScriptInterface<IBBHighlightable> && NewHighlightable) PURE_VIRTUAL(UIBBDecalComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBDecalComponent::Finalize, );

		virtual TScriptInterface<IBBHighlightable> GetHighlightable() const PURE_VIRTUAL(UIBBDecalComponent::GetHighlightable, return TScriptInterface<IBBHighlightable>(); );

		virtual void SetHighlightable(TScriptInterface<IBBHighlightable> && NewHighlightable) PURE_VIRTUAL(UIBBDecalComponent::SetHighlightable, );
};