// Fill out your copyright notice in the Description page of Project Settings.

#include "BBActor.h"

ABBActor::ABBActor(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABBActor::BeginPlay()
{
	Super::BeginPlay();

}

void ABBActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABBActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	BroadcastEventIfRightClicked(ButtonPressed);
}



void ABBActor::BroadcastEventIfRightClicked(FKey ButtonPressed)
{
	if (ButtonPressed == EKeys::RightMouseButton)
	{
		//RightClickedEvent.Broadcast();
	}
}