// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWidgetTargetComponent.h"
#include "Components/WidgetComponent.h"
#include "IBBWidgetComponent.generated.h"

class IBBWidgetTarget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBWidgetComponent : public UWidgetComponent, public IBBWidgetTargetComponent
{
	GENERATED_BODY()

	public:	
		UIBBWidgetComponent() : Super() { };

		virtual void SetWidget(UUserWidget* NewWidget) override { Super::SetWidget(NewWidget); };

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const
			PURE_VIRTUAL(UIBBWidgetComponent::GetWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		DECLARE_DERIVED_EVENT(
			UIBBWidgetComponent,
			IBBWidgetTargetComponent::FBBWidgetTargetUpdate,
			FBBWidgetTargetUpdate
		);

		virtual FBBWidgetTargetUpdate& OnWidgetTargetUpdate() final override { return WidgetTargetUpdate; };

	protected:
		FBBWidgetTargetUpdate WidgetTargetUpdate;
};