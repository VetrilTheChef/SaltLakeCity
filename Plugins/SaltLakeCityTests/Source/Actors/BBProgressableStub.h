// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBProgressable.h"
#include "BBProgressableStub.generated.h"

UCLASS(NotBlueprintable)

class UBBProgressableStub : public UObject, public IBBProgressable
{
	GENERATED_BODY()

	public:
		UBBProgressableStub();

		virtual float GetProgress() const override;

		virtual void SetProgress(float NewProgress) override;

		virtual UIBBProgressComponent * GetProgressComponent() const override;

		void SetProgressComponent(UIBBProgressComponent * NewProgressComponent);

		virtual AActor * ToActor() override;

		void SetActor(AActor * NewProgressableActor);

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget);

		void BroadcastProgressInitiation();

		void BroadcastProgressUpdate();

		void BroadcastProgressCompletion();

		DECLARE_DERIVED_EVENT(UBBProgressableStub, IBBProgressable::FBBProgressInitiation, FBBProgressInitiation);

		virtual FBBProgressInitiation & OnProgressInitiation() final override { return ProgressInitiation; };

		DECLARE_DERIVED_EVENT(UBBProgressableStub, IBBProgressable::FBBProgressUpdate, FBBProgressUpdate);

		virtual FBBProgressUpdate & OnProgressUpdate() final override { return ProgressUpdate; };

		DECLARE_DERIVED_EVENT(UBBProgressableStub, IBBProgressable::FBBProgressCompletion, FBBProgressCompletion);

		virtual FBBProgressCompletion & OnProgressCompletion() final override { return ProgressCompletion; };

	protected:
		UPROPERTY()
		UIBBProgressComponent * ProgressComponent;

		UPROPERTY()
		AActor * ProgressableActor;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		float Progress;

		FBBProgressInitiation ProgressInitiation;

		FBBProgressUpdate ProgressUpdate;

		FBBProgressCompletion ProgressCompletion;
};