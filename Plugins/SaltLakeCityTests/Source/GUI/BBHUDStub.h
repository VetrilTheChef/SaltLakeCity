// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "BBHUDStub.generated.h"

/**
 * 
 */

UCLASS()

class ABBHUDStub : public AIBBHUD
{
	GENERATED_BODY()
	
	public:
		ABBHUDStub();

		virtual void BeginPlay() override;
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(UIBBGameInstance * GameInstance, AIBBGameMode * GameMode, AIBBGameState * GameState, APlayerController * PlayerController) override;

		virtual void Finalize() override;

		virtual const UIBBWidgetFactory * GetWidgetFactory() const override;

		virtual void SetWidgetFactory(UIBBWidgetFactory * NewWidgetFactory) override;

		virtual const UIBBWidgetSpecificationFactory * GetWidgetSpecificationFactory() const override;

		void SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory);

		virtual void CloseWidget(UIBBWidgetSpecification * Specification) override;

		virtual void OpenWidget(UIBBWidgetSpecification * Specification, bool PopUp) override;

		virtual void AttachWidget(UIBBWidgetSpecification * Specification, UIBBWidgetComponent * WidgetComponent) override;

		virtual void DetachWidget(UIBBWidgetComponent * WidgetComponent) override;

		virtual bool ConvertToPIEViewportSpace(FVector2D & Position) override;

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

		EBBGameMode GetActiveMode();

		UIBBWidgetSpecification * GetWidgetSpecification();

		bool GetPopUp();

		void SetAttachmentWidget(UUserWidget * NewAttachmentWidget);

		void BroadcastContextUpdate(UIBBContextComponent * ContextComponent);

		void BroadcastProgressUpdate(UIBBProgressComponent * ProgressComponent);

		void BroadcastSelectionUpdate(UIBBSelectionComponent * SelectionComponent);

		void BroadcastConsumerUpdate(UIBBWorkComponent * WorkComponent);

	private:
		UPROPERTY()
		UIBBWidgetFactory * WidgetFactory;

		UPROPERTY()
		UIBBWidgetSpecificationFactory * WidgetSpecificationFactory;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;

		UPROPERTY()
		UUserWidget * AttachmentWidget;

		EBBGameMode ActiveGameMode;

		bool WidgetPopUp;
};