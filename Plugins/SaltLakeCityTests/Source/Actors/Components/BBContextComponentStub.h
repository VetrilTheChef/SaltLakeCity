// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "BBContextComponentStub.generated.h"

class UIBBCloseWidgetCommand;
class UIBBOpenWidgetCommand;

struct FKey;

UCLASS(NotBlueprintable)

class UBBContextComponentStub : public UIBBContextComponent
{
	GENERATED_BODY()

	public:	
		UBBContextComponentStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBContextualizable> && NewContextualizable) override;

		virtual void Finalize() override;

		virtual TScriptInterface<IBBContextualizable> GetContextualizable() const;

		virtual void SetContextualizable(TScriptInterface<IBBContextualizable> && NewContextualizable);

		virtual void AddOption(EBBContext Option);

		virtual void RemoveOption(EBBContext Option);

		virtual void ClearOptions();

		virtual bool IsOption(EBBContext Option) const override;

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBContextualizable> Contextualizable;

		UPROPERTY()
		TSet<EBBContext> Context;

		UFUNCTION()
		void ShowContext();

		UFUNCTION()
		void HideContext();
};