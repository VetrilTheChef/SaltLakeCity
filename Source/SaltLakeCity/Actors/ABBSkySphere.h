// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABBSkySphere.generated.h"

class UStaticMesh;

UCLASS()
class SALTLAKECITY_API AABBSkySphere : public AActor
{
	GENERATED_BODY()
	
	public:
		AABBSkySphere();

		virtual void Tick(float DeltaTime) override;

	protected:
		virtual void BeginPlay() override;

	private:
		UPROPERTY(EditDefaultsOnly, Category = "Mesh", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMesh* SkyMesh;

		void SetMaterialParameters();
};
