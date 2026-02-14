// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "IBBHUD.generated.h"

/**
 * 
 */

Expose_TNameOf(AIBBHUD)

class IBBWidgetTarget;
class UIBBContextComponent;
class UIBBUINotificationSubsystem;
class UIBBProgressComponent;
class UIBBSelectionComponent;
class UIBBWidgetComponent;
class UIBBWidgetManager;
class UIBBWidgetSpecification;
class UIBBWorkComponent;

USTRUCT(BlueprintType)
struct FUIRequestPayload
{
	GENERATED_BODY()

	public:
		FUIRequestPayload() {}

		FUIRequestPayload(
			FGameplayTag NewWidgetID,
			UIBBWidgetSpecification* NewSpecification,
			bool bNewPopUp,
			FInstancedStruct&& NewInitializationData
		) :
			WidgetID(NewWidgetID),
			Specification(NewSpecification),
			bPopUp(bNewPopUp),
			InitializationData(NewInitializationData)
		{
		}

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayTag WidgetID;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UIBBWidgetSpecification* Specification;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPopUp;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FInstancedStruct InitializationData;
};

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBHUD : public AHUD
{
	GENERATED_BODY()
	
	public:
		AIBBHUD() : Super() { };

		virtual void BeginPlay() override
		{ Super::BeginPlay();  };
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override
		{ Super::EndPlay(EndPlayReason); };

		virtual void Initialize(
			UIBBUINotificationSubsystem* NewUINotificationSubsystem,
			UIBBWidgetManager* NewWidgetManager
		)
			PURE_VIRTUAL(AIBBHUD::Initialize, );

		virtual void Finalize()
			PURE_VIRTUAL(AIBBHUD::Finalize, );

		virtual void DrawMarquee(FVector2D MarqueeStart, FVector2D MarqueeEnd)
			PURE_VIRTUAL(AIBBHUD::DrawMarquee, );

		virtual void AttachWidget(UIBBWidgetSpecification* Specification, UIBBWidgetComponent* WidgetComponent)
			PURE_VIRTUAL(AIBBHUD::AttachWidget, );

		virtual void DetachWidget(UIBBWidgetComponent* WidgetComponent)
			PURE_VIRTUAL(AIBBHUD::DetachWidget, );

		DECLARE_EVENT_OneParam(AIBBHUD, FBBContextUpdate, UIBBContextComponent*);

		FBBContextUpdate & OnContextUpdate() { return UpdateContext; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBProgressUpdate, UIBBProgressComponent*);

		FBBProgressUpdate & OnProgressUpdate() { return UpdateProgress; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBSelectionUpdate, UIBBSelectionComponent*);

		FBBSelectionUpdate & OnSelectionUpdate() { return UpdateSelection; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBWidgetTargetUpdate, TScriptInterface<IBBWidgetTarget> &&);

		FBBWidgetTargetUpdate & OnWidgetTargetUpdate() { return UpdateWidgetTarget; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBConsumerUpdate, UIBBWorkComponent*);

		FBBConsumerUpdate & OnConsumerUpdate() { return ConsumerUpdate; };

		UFUNCTION()
		virtual void UpdateActiveMode(EBBGameMode NewActiveMode)
			PURE_VIRTUAL(AIBBHUD::UpdateActiveMode, );

	protected:
		UFUNCTION(BlueprintNativeEvent, Category = "UI | Requests")
		void OnCloseRequest(const FUIRequestPayload& Payload);
		//virtual void OnCloseRequest_Implementation(const FUIRequestPayload& Payload);

		UFUNCTION(BlueprintNativeEvent, Category = "UI | Requests")
		void OnOpenRequest(const FUIRequestPayload& Payload);
		//virtual void OnOpenRequest_Implementation(const FUIRequestPayload& Payload);

		FBBContextUpdate UpdateContext;

		FBBProgressUpdate UpdateProgress;

		FBBSelectionUpdate UpdateSelection;

		FBBWidgetTargetUpdate UpdateWidgetTarget;

		FBBConsumerUpdate ConsumerUpdate;
};