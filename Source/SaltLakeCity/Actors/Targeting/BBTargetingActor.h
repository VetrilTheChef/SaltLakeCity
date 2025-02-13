// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Targeting/Interfaces/IBBTargetingActor.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "BBTargetingActor.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API ABBTargetingActor : public AIBBTargetingActor
{
	GENERATED_BODY()
	
	public:
		ABBTargetingActor();

		virtual void StartTargeting(UGameplayAbility * Ability) override;

		virtual void Tick(float DeltaTime) override;

		virtual void ConfirmTargetingAndContinue() override;

		virtual void ConfirmTargeting() override;

		virtual void CancelTargeting() override;

		virtual UMaterialInterface * GetPreviewMaterial() const override;

		virtual void AttachActor(AActor * NewActor) override;

		virtual int GetAttachedActorsNum() override;

		virtual void DetachAllActors() override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Preview Material", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSoftObjectPtr<UMaterialInterface> PreviewMaterialAsset;

		UPROPERTY(EditDefaultsOnly, Category = "Preview Material", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSoftObjectPtr<UMaterialParameterCollection> PreviewMaterialParametersAsset;

		UPROPERTY(EditDefaultsOnly, Category = "Preview Material", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName ColorParameterName;

		UPROPERTY(EditDefaultsOnly, Category = "Preview Material", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FColor EnabledColor;

		UPROPERTY(EditDefaultsOnly, Category = "Preview Material", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FColor DisabledColor;

		UPROPERTY()
		UMaterialInterface * PreviewMaterial;

		UPROPERTY()
		UMaterialParameterCollectionInstance * PreviewMaterialParameters;

		UPROPERTY()
		TArray<AActor *> Actors;

		UPROPERTY()
		FGameplayAbilityTargetData_SingleTargetHit TargetData;

		FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

		FDetachmentTransformRules DetachRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);

		bool Buildable;

		void SubscribeToGameMode();

		void UnsubscribeFromGameMode();

		void UpdateMaterialOverride(bool Enabled);

		UFUNCTION()
		void UpdateActiveGameMode(EBBGameMode NewActiveGameMode);
};