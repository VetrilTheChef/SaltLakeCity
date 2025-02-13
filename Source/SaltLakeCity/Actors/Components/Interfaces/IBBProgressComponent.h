// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBActorComponent.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "Actors/Interfaces/IBBProgressable.h"
#include "IBBProgressComponent.generated.h"

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBProgressComponent : public UIBBWidgetComponent, public IBBActorComponent
{
	GENERATED_BODY()

	public:	
		UIBBProgressComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(TScriptInterface<IBBProgressable> && NewProgressable) PURE_VIRTUAL(UIBBProgressComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBProgressComponent::Finalize, );

		virtual TScriptInterface<IBBProgressable> GetProgressable() const PURE_VIRTUAL(UIBBProgressComponent::GetProgressable, return TScriptInterface<IBBProgressable>(); );

		virtual void SetProgressable(TScriptInterface<IBBProgressable> && NewProgressable) PURE_VIRTUAL(UIBBProgressComponent::SetProgressable, );
		
		virtual float GetProgress() PURE_VIRTUAL(UIBBProgressComponent::GetProgress, return -1.0f; );

		DECLARE_EVENT_OneParam(UIBBProgressComponent, FBBProgressUpdate, float);

		virtual FBBProgressUpdate & OnProgressUpdate() { return ProgressUpdate; };
		
		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override PURE_VIRTUAL(UIBBProgressComponent::GetWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

	protected:
		FBBProgressUpdate ProgressUpdate;
};