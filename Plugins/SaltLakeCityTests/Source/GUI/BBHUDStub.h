// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "BBHUDStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class ABBHUDStub : public AIBBHUD
{
	GENERATED_BODY()
	
	public:
		ABBHUDStub();

		virtual void BeginPlay() override;
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(
			UIBBPresentationSubsystem* NewPresentationSubsystem,
			UIBBWidgetManager* NewWidgetManager
		) override;

		virtual void Finalize() override;

		virtual void CloseWidget(UIBBWidgetSpecification* Specification) override;

		virtual void OpenWidget(UIBBWidgetSpecification* Specification, bool PopUp) override;

		virtual void AttachWidget(
			UIBBWidgetSpecification* Specification,
			UIBBWidgetComponent* WidgetComponent
		) override;

		virtual void DetachWidget(UIBBWidgetComponent* WidgetComponent) override;

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

		EBBGameMode GetActiveMode();

		UIBBWidgetSpecification* GetWidgetSpecification();

		bool GetPopUp();

		void SetAttachmentWidget(UUserWidget* NewAttachmentWidget);

		void BroadcastContextUpdate(UIBBContextComponent* ContextComponent);

		void BroadcastProgressUpdate(UIBBProgressComponent* ProgressComponent);

		void BroadcastSelectionUpdate(UIBBSelectionComponent* SelectionComponent);

		void BroadcastConsumerUpdate(UIBBWorkComponent* WorkComponent);

	private:
		TSoftObjectPtr<UUserWidget> AttachmentWidget;

		TSoftObjectPtr<UIBBPresentationSubsystem> PresentationSubsystem;

		TSoftObjectPtr<UIBBWidgetManager> WidgetManager;

		TSoftObjectPtr<UIBBWidgetSpecification> WidgetSpecification;

		EBBGameMode ActiveGameMode;

		bool WidgetPopUp;
};