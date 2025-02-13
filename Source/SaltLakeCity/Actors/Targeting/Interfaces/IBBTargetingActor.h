// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "IBBTargetingActor.generated.h"

class UGameplayAbility;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBTargetingActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
	public:
		AIBBTargetingActor() : Super() { };

		virtual void StartTargeting(UGameplayAbility * Ability) override { Super::StartTargeting(Ability); }

		virtual void Tick(float DeltaTime) override { Super::Tick(DeltaTime); }

		virtual void ConfirmTargetingAndContinue() override { Super::ConfirmTargetingAndContinue(); }

		virtual void ConfirmTargeting() override { Super::ConfirmTargeting(); }

		virtual void CancelTargeting() override { Super::CancelTargeting(); }

		virtual UMaterialInterface * GetPreviewMaterial() const PURE_VIRTUAL(AIBBTargetingActor::GetPreviewMaterial, return nullptr; );

		virtual void AttachActor(AActor * NewActor) PURE_VIRTUAL(AIBBTargetingActor::AttachActor, );

		virtual int GetAttachedActorsNum() PURE_VIRTUAL(AIBBTargetingActor::GetAttachedActorsNum, return -1; );

		virtual void DetachAllActors() PURE_VIRTUAL(AIBBTargetingActor::DetachAllActors, );
};