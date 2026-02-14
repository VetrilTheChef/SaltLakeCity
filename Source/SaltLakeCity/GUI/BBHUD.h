// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "BBHUD.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API ABBHUD : public AIBBHUD
{
	GENERATED_BODY()
	
	public:
		ABBHUD();

		virtual void BeginPlay() override;
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(
			UIBBUINotificationSubsystem* NewUINotificationSubsystem,
			UIBBWidgetManager* NewWidgetManager
		) override;

		virtual void Finalize() override;
		
		virtual void DrawMarquee(FVector2D MarqueeStart, FVector2D MarqueeEnd) override;

		virtual void AttachWidget(
			UIBBWidgetSpecification* Specification,
			UIBBWidgetComponent* WidgetComponent
		) override;

		virtual void DetachWidget(UIBBWidgetComponent* WidgetComponent) override;

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "UI | Colors")
		FLinearColor HUDColor;

		UPROPERTY(EditDefaultsOnly, Category = "UI | Tags")
		FGameplayTag CloseRequestTag;

		UPROPERTY(EditDefaultsOnly, Category = "UI | Tags")
		FGameplayTag OpenRequestTag;

		FDelegateHandle OnLandscapeClickedHandle;

		UIBBWidgetManager* GetWidgetManagerChecked() const;

		void SetWidgetManagerChecked(UIBBWidgetManager* NewWidgetManager);

		UIBBUINotificationSubsystem* GetUINotificationSubsystemChecked() const;

		void SetUINotificationSubsystemChecked(UIBBUINotificationSubsystem* NewUINotificationSubsystem);

		void AddWidgetToViewport(UIBBWidget& Widget, int32 ZOrder = -1);

		void Subscribe(UIBBUINotificationSubsystem& NewUINotificationSubsystem);

		void Unsubscribe(UIBBUINotificationSubsystem& SubscribedUINotificationSubsystem);

		void DisplayWidget(const UWorld* World, UIBBWidget* Widget, bool PopUp);

	private:
		TWeakObjectPtr<UIBBUINotificationSubsystem> UINotificationSubsystem;

		TWeakObjectPtr<UIBBWidgetManager> WidgetManager;

		void CloseWidget(const UIBBWidgetSpecification* Specification);

		void OpenWidget(const UIBBWidgetSpecification* Specification, const bool PopUp);
};