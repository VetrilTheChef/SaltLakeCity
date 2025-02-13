// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBActorComponent.h"
#include "Actors/Components/Interfaces/IBBWidgetTargetComponent.h"
#include "GUI/Includes/BBContextEnum.h"
#include "IBBContextComponent.generated.h"

class IBBContextualizable;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBContextComponent : public UActorComponent, public IBBWidgetTargetComponent
{
	GENERATED_BODY()

	public:	
		UIBBContextComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(TScriptInterface<IBBContextualizable> && NewContextualizable) PURE_VIRTUAL(UIBBContextComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBContextComponent::Finalize, );

		virtual bool IsOption(EBBContext Option) const PURE_VIRTUAL(UIBBContextComponent::IsOption, return false; );

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override PURE_VIRTUAL(UIBBContextComponent::GetWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );
		
		DECLARE_DERIVED_EVENT(UIBBContextComponent, IBBWidgetTargetComponent::FBBWidgetTargetUpdate, FBBWidgetTargetUpdate);

		virtual FBBWidgetTargetUpdate & OnWidgetTargetUpdate() final override { return WidgetTargetUpdate; };

	protected:
		FBBWidgetTargetUpdate WidgetTargetUpdate;
};