// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "BBProgressComponent.generated.h"

class UIBBAttachWidgetCommand;
class UIBBCommandFactory;
class UIBBDetachWidgetCommand;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBProgressComponent : public UIBBProgressComponent
{
	GENERATED_BODY()

	public:	
		UBBProgressComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(TScriptInterface<IBBProgressable> && NewProgressable) override;

		virtual void Finalize() override;

		virtual TScriptInterface<IBBProgressable> GetProgressable() const override;

		virtual void SetProgressable(TScriptInterface<IBBProgressable> && NewProgressable) override;

		virtual void SetWidget(UUserWidget * NewWidget) override;

		virtual float GetProgress() override;

		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Widget Colors")
		FLinearColor SelectedColor;

		UPROPERTY(EditDefaultsOnly, Category = "Widget Colors")
		FLinearColor DeselectedColor;

		UPROPERTY()
		TScriptInterface<IBBProgressable> Progressable;

		UPROPERTY()
		UIBBAttachWidgetCommand * AttachCommand;

		UPROPERTY()
		UIBBDetachWidgetCommand * DetachCommand;

		void Subscribe(TScriptInterface<IBBProgressable> && NewProgressable);

		void Unsubscribe(TScriptInterface<IBBProgressable> & OldProgressable);

		void InitializeCommands(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory);

		void InitializeAttachWidgetCommand(const UIBBCommandFactory & CommandFactory, const UIBBWidgetSpecificationFactory & WidgetSpecificationFactory);

		void InitializeDetachWidgetCommand(const UIBBCommandFactory & CommandFactory);

		void FinalizeCommands();

		void FinalizeAttachWidgetCommand();

		void FinalizeDetachWidgetCommand();

		UFUNCTION()
		void UpdateComponent(UIBBProgressComponent * NewProgressComponent);

		UFUNCTION()
		void AttachWidget();

		UFUNCTION()
		void DetachWidget();

		UFUNCTION()
		void UpdateProgress(float NewProgress);
};