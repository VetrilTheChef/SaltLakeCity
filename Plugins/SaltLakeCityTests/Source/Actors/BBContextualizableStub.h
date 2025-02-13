// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "BBContextualizableStub.generated.h"

UCLASS(NotBlueprintable)

class UBBContextualizableStub : public UObject, public IBBContextualizable
{
	GENERATED_BODY()

	public:
		UBBContextualizableStub();

		virtual void UpdateContext(bool Contextualized) override;

		bool GetIsContextualized() const;

		virtual bool IsContextOption(EBBContext ContextOption) const override;

		virtual void SetContextOptions(TSet<EBBContext> NewValidContextOptions);

		virtual UIBBContextComponent * GetContextComponent() const override;

		void SetContextComponent(UIBBContextComponent * NewContextComponent);

		virtual AActor * ToActor() override;

		void SetActor(AActor * NewContextualizableActor);

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget);

		DECLARE_DERIVED_EVENT(UBBContextualizableStub, IBBContextualizable::FBBContextUpdate, FBBContextUpdate);

		virtual FBBContextUpdate & OnContextUpdate() final override { return ContextUpdate; };

	protected:
		UPROPERTY()
		UIBBContextComponent * ContextComponent;

		UPROPERTY()
		AActor * ContextualizableActor;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		bool IsContextualized;

		TSet<EBBContext> ContextOptions;

		FBBContextUpdate ContextUpdate;
};