// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/ShapeComponent.h"
#include "BBPlaneComponent.generated.h"

class FPrimitiveSceneProxy;

UCLASS(ClassGroup = "Collision", hidecategories = (Object, LOD, Lighting, TextureStreaming), editinlinenew, meta = (DisplayName = "Plane Collision", BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBPlaneComponent : public UShapeComponent
{
	GENERATED_BODY()

	public:
		UBBPlaneComponent(const FObjectInitializer & ObjectInitializer);

		UFUNCTION(BlueprintCallable, Category = "Components|Plane")
		void SetPlaneExtent(FVector InPlaneExtent, bool bUpdateOverlaps = true);

		UFUNCTION(BlueprintCallable, Category = "Components|Plane")
		FVector GetScaledPlaneExtent() const;

		UFUNCTION(BlueprintCallable, Category = "Components|Plane")
		FVector GetUnscaledPlaneExtent() const;

		virtual bool IsZeroExtent() const override;

		virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

		virtual struct FCollisionShape GetCollisionShape(float Inflation = 0.0f) const override;

		virtual FBoxSphereBounds CalcBounds(const FTransform & LocalToWorld) const override;
		
		virtual void UpdateBodySetup() override;

		FORCEINLINE void InitPlaneExtent(const FVector & InPlaneExtent) { PlaneExtent = InPlaneExtent; }

	protected:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, export, Category = Shape)
		FVector PlaneExtent;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, export, Category = Shape)
		float LineThickness;
};

FORCEINLINE FVector UBBPlaneComponent::GetScaledPlaneExtent() const
{
	return PlaneExtent * GetComponentTransform().GetScale3D();
}

FORCEINLINE FVector UBBPlaneComponent::GetUnscaledPlaneExtent() const
{
	return PlaneExtent;
}