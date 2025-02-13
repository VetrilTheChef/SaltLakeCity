// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBActor.generated.h"

/**
*
*/

UCLASS()

class SALTLAKECITY_API ABBActor : public AActor
{
	GENERATED_BODY()

	public:
		ABBActor(const FObjectInitializer & ObjectInitializer);

		virtual void Tick(float DeltaTime) override;

		virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	protected:
		virtual void BeginPlay() override;

		void BroadcastEventIfRightClicked(FKey ButtonPressed);
};