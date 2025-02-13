// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "IBBSelectionComponent.generated.h"

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSelectionComponent : public UIBBWidgetComponent
{
	GENERATED_BODY()

	public:	
		UIBBSelectionComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(TScriptInterface<IBBSelectable> && NewSelectable) PURE_VIRTUAL(UIBBSelectionComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBSelectionComponent::Finalize, );

		virtual TScriptInterface<IBBSelectable> GetSelectable() const PURE_VIRTUAL(UIBBSelectionComponent::GetSelectable, return TScriptInterface<IBBSelectable>(); );

		virtual void SetSelectable(TScriptInterface<IBBSelectable> && NewSelectable) PURE_VIRTUAL(UIBBSelectionComponent::SetSelectable, );

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override PURE_VIRTUAL(UIBBSelectionComponent::GetWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );
};