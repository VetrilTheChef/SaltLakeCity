// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Previews/Interfaces/IBBCharacterPreview.h"
#include "Camera/CameraTypes.h"
#include "BBCharacterPreview.generated.h"

/**
*
*/

class USceneCaptureComponent2D;
class USpringArmComponent;
class UTextureRenderTarget2D;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API ABBCharacterPreview : public AIBBCharacterPreview
{
	GENERATED_BODY()

	public:
		ABBCharacterPreview();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void CreatePreview(const AIBBCharacter * TemplateCharacter) override;

		virtual void ShowActors(TArray<AActor *> Actors) override;

		virtual UTexture * GetPreview() override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Render Target")
		FLinearColor ClearColor;

		UPROPERTY(EditDefaultsOnly, Category = "Render Target")
		bool AutoGenerateMips;

		UPROPERTY(EditDefaultsOnly, Category = "Render Target", meta = (ClampMin = "256", ClampMax = "2048"))
		uint32 Width;

		UPROPERTY(EditDefaultsOnly, Category = "Render Target", meta = (ClampMin = "256", ClampMax = "2048"))
		uint32 Height;

		UPROPERTY(EditDefaultsOnly)
		USpringArmComponent * PreviewSpringArm;

		UPROPERTY(EditDefaultsOnly)
		USceneCaptureComponent2D * PreviewSceneCapture;

		UPROPERTY()
		UTextureRenderTarget2D * PreviewRenderTarget;
};