// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Targeting/Interfaces/IBBTargetingActor.h"
#include "BBTargetingActorStub.generated.h"

UCLASS(NotBlueprintable)

class ABBTargetingActorStub : public AIBBTargetingActor
{
	GENERATED_BODY()
	
	public:
		ABBTargetingActorStub();

		virtual void PostInitProperties() override;

		virtual void StartTargeting(UGameplayAbility * Ability) override;

		virtual void Tick(float DeltaTime) override;

		void SetBuildable(bool NewBuildable);

		virtual void ConfirmTargetingAndContinue() override;

		virtual void ConfirmTargeting() override;

		virtual void CancelTargeting() override;

		virtual UMaterialInterface * GetPreviewMaterial() const override;

		virtual void AttachActor(AActor * NewActor) override;

		virtual int GetAttachedActorsNum() override;

		virtual void DetachAllActors() override;

	protected:
		UPROPERTY()
		TArray<AActor *> Actors;

		UPROPERTY()
		FGameplayAbilityTargetData_SingleTargetHit TargetData;

		UPROPERTY()
		TSoftClassPtr<UMaterialInterface> PreviewMaterialClass;

		UPROPERTY()
		UMaterialInterface * PreviewMaterial;

		bool Buildable;
};