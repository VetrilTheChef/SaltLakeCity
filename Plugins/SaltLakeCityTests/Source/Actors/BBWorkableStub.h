// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "BBWorkableStub.generated.h"

UCLASS(NotBlueprintable)

class UBBWorkableStub : public UObject, public IBBWorkable
{
	GENERATED_BODY()

	public:
		UBBWorkableStub();

		virtual UIBBWorkComponent * GetWorkComponent() const override;

		void SetSelectionComponent(UIBBWorkComponent * NewWorkComponent);

		virtual AActor * ToActor() override;

		void SetActor(AActor * NewWorkableActor);

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget);

	protected:
		UPROPERTY()
		UIBBWorkComponent * WorkComponent;

		UPROPERTY()
		AActor * WorkableActor;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;
};