// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "BBProgressComponentStub.generated.h"

UCLASS(NotBlueprintable)

class UBBProgressComponentStub : public UIBBProgressComponent
{
	GENERATED_BODY()

	public:	
		UBBProgressComponentStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBProgressable> && NewProgressable) override;

		virtual void Finalize() override;

		virtual TScriptInterface<IBBProgressable> GetProgressable() const override;

		virtual void SetProgressable(TScriptInterface<IBBProgressable> && NewProgressable) override;

		virtual float GetProgress() override;

		void SetProgress(float NewProgress);

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBProgressable> Progressable;

		float Progress;
};