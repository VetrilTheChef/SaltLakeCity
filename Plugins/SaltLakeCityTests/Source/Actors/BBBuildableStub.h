// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "BBBuildableStub.generated.h"

UCLASS(NotBlueprintable)

class UBBBuildableStub : public UObject, public IBBBuildable
{
	GENERATED_BODY()

	public:
		UBBBuildableStub();

		virtual float GetPrice() const override;

		virtual void SetPrice(float NewPrice) override;

		virtual float GetBuildTime() const override;

		virtual void SetBuildTime(float NewBuildTime) override;

		virtual void AddMaterialOverride(UMaterialInterface * NewMaterialOverride) override;

		virtual void RemoveMaterialOverride() override;

		virtual void StartBuilding() override;

		virtual void StopBuilding() override;

		virtual AActor * ToActor() override;

		void SetActor(AActor * NewBuildableActor);

	protected:
		UPROPERTY()
		UMaterialInterface * MaterialOverride;

		UPROPERTY()
		AActor * BuildableActor;

		float Price;

		float BuildTime;

		bool IsBuilding;
};