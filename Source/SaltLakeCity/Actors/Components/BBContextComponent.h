// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "BBContextComponent.generated.h"

class UIBBCloseWidgetCommand;
class UIBBCommandFactory;
class UIBBOpenWidgetCommand;
class UIBBSetContextCommand;
class UIBBWidgetSpecification;
class UIBBWidgetSpecificationFactory;

struct FKey;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Components), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBContextComponent : public UIBBContextComponent
{
	GENERATED_BODY()

	public:	
		UBBContextComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBContextualizable> && NewContextualizable) override;

		virtual void Finalize() override;

		virtual bool IsOption(EBBContext Option) const override;

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBContextualizable> Contextualizable;

		UPROPERTY()
		UIBBSetContextCommand * ContextCommand;

		UPROPERTY()
		UIBBOpenWidgetCommand * OpenCommand;

		UPROPERTY()
		UIBBCloseWidgetCommand * CloseCommand;

		void Subscribe(TScriptInterface<IBBContextualizable> && NewContextualizable);

		void Unsubscribe(TScriptInterface<IBBContextualizable> & OldContextualizable);

		void InitializeCommands(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory);
		
		void InitializeSetContextCommand(const UIBBCommandFactory & CommandFactory, TScriptInterface<IBBContextualizable> & NewContextualizable);

		void InitializeOpenWidgetCommand(const UIBBCommandFactory & CommandFactory, UIBBWidgetSpecification * WidgetSpecification);

		void InitializeCloseWidgetCommand(const UIBBCommandFactory & CommandFactory, UIBBWidgetSpecification * WidgetSpecification);

		void FinalizeCommands();

		void FinalizeSetContextCommand();

		void FinalizeOpenWidgetCommand();

		void FinalizeCloseWidgetCommand();

		UFUNCTION()
		void ToggleContext(bool Contextualized);
};