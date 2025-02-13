// Fill out your copyright notice in the Description page of Project Settings.

#include "ABBSkySphere.h"
#include "Engine/StaticMesh.h"

AABBSkySphere::AABBSkySphere()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AABBSkySphere::BeginPlay()
{
	Super::BeginPlay();
}

void AABBSkySphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABBSkySphere::SetMaterialParameters()
{
}