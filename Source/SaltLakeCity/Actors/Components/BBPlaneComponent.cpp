// SaltLakeCity 4.25

#include "BBPlaneComponent.h"

UBBPlaneComponent::UBBPlaneComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlaneExtent = FVector(32.0f, 32.0f, 0.0f);

	bUseEditorCompositing = true;
}


void UBBPlaneComponent::SetPlaneExtent(FVector NewPlaneExtent, bool bUpdateOverlaps)
{
	PlaneExtent = NewPlaneExtent;
	UpdateBounds();
	MarkRenderStateDirty();
	UpdateBodySetup();

	if (bPhysicsStateCreated)
	{
		BodyInstance.UpdateBodyScale(GetComponentTransform().GetScale3D(), true);

		if (bUpdateOverlaps && IsCollisionEnabled() && GetOwner())
		{
			UpdateOverlaps();
		}
	}
}

template <EShapeBodySetupHelper UpdateBodySetupAction>
bool InvalidateOrUpdatePlaneBodySetup(UBodySetup * & ShapeBodySetup, bool bUseArchetypeBodySetup, FVector PlaneExtent)
{
	check((bUseArchetypeBodySetup && UpdateBodySetupAction == EShapeBodySetupHelper::InvalidateSharingIfStale) ||
		  (!bUseArchetypeBodySetup && UpdateBodySetupAction == EShapeBodySetupHelper::UpdateBodySetup));
	check(ShapeBodySetup->AggGeom.BoxElems.Num() == 1);

	FKBoxElem* se = ShapeBodySetup->AggGeom.BoxElems.GetData();

	if (PlaneExtent.X < KINDA_SMALL_NUMBER)
	{
		PlaneExtent.X = 1.0f;
	}

	if (PlaneExtent.Y < KINDA_SMALL_NUMBER)
	{
		PlaneExtent.Y = 1.0f;
	}

	if (PlaneExtent.Z > KINDA_SMALL_NUMBER)
	{
		PlaneExtent.Z = KINDA_SMALL_NUMBER;
	}

	float XExtent = PlaneExtent.X * 2.f;
	float YExtent = PlaneExtent.Y * 2.f;
	float ZExtent = PlaneExtent.Z * 2.f;

	if (UpdateBodySetupAction == EShapeBodySetupHelper::UpdateBodySetup)
	{
		se->SetTransform(FTransform::Identity);
		se->X = XExtent;
		se->Y = YExtent;
		se->Z = ZExtent;
	}
	else if (se->X != XExtent || se->Y != YExtent || se->Z != ZExtent)
	{
		ShapeBodySetup = nullptr;
		bUseArchetypeBodySetup = false;
	}

	return bUseArchetypeBodySetup;
}

void UBBPlaneComponent::UpdateBodySetup()
{
	if (PrepareSharedBodySetup<UBBPlaneComponent>())
	{
		bUseArchetypeBodySetup = InvalidateOrUpdatePlaneBodySetup<EShapeBodySetupHelper::InvalidateSharingIfStale>(ShapeBodySetup, bUseArchetypeBodySetup, PlaneExtent);
	}

	//CreateShapeBodySetupIfNeeded<FKPlaneElem>();

	if (!bUseArchetypeBodySetup)
	{
		InvalidateOrUpdatePlaneBodySetup<EShapeBodySetupHelper::UpdateBodySetup>(ShapeBodySetup, bUseArchetypeBodySetup, PlaneExtent);
	}
}

bool UBBPlaneComponent::IsZeroExtent() const
{
	return PlaneExtent.IsZero();
}

FBoxSphereBounds UBBPlaneComponent::CalcBounds(const FTransform & LocalToWorld) const
{
	return FBoxSphereBounds(FBox(-PlaneExtent, PlaneExtent)).TransformBy(LocalToWorld);
}



FPrimitiveSceneProxy * UBBPlaneComponent::CreateSceneProxy()
{
	class FPlaneSceneProxy final : public FPrimitiveSceneProxy
	{
		public:
			SIZE_T GetTypeHash() const override
			{
				static size_t UniquePointer;
				return reinterpret_cast<size_t>(&UniquePointer);
			}

			FPlaneSceneProxy(const UBBPlaneComponent * InComponent)
				: FPrimitiveSceneProxy(InComponent)
				, bDrawOnlyIfSelected(InComponent->bDrawOnlyIfSelected)
				, PlaneExtents(InComponent->PlaneExtent)
				, PlaneColor(InComponent->ShapeColor)
				, LineThickness(InComponent->LineThickness)
			{
				bWillEverBeLit = false;
			}

			virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
			{
				QUICK_SCOPE_CYCLE_COUNTER(STAT_PlaneSceneProxy_GetDynamicMeshElements);

				const FMatrix & LocalToWorld = GetLocalToWorld();

				for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
				{
					if (VisibilityMap & (1 << ViewIndex))
					{
						const FSceneView* View = Views[ViewIndex];

						const FLinearColor DrawColor = GetViewSelectionColor(PlaneColor, * View, IsSelected(), IsHovered(), false, IsIndividuallySelected());

						FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
						DrawOrientedWireBox(PDI, LocalToWorld.GetOrigin(), LocalToWorld.GetScaledAxis(EAxis::X), LocalToWorld.GetScaledAxis(EAxis::Y), LocalToWorld.GetScaledAxis(EAxis::Z), PlaneExtents, DrawColor, SDPG_World, LineThickness);
					}
				}
			}

			virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
			{
				const bool bProxyVisible = !bDrawOnlyIfSelected || IsSelected();

				const bool bShowForCollision = View->Family->EngineShowFlags.Collision && IsCollisionEnabled();

				FPrimitiveViewRelevance Result;
				Result.bDrawRelevance = (IsShown(View) && bProxyVisible) || bShowForCollision;
				Result.bDynamicRelevance = true;
				Result.bShadowRelevance = IsShadowCast(View);
				Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
				return Result;
			}

			virtual uint32 GetMemoryFootprint(void) const override
			{
				return(sizeof(*this) + GetAllocatedSize());
			}

			uint32 GetAllocatedSize(void) const
			{
				return(FPrimitiveSceneProxy::GetAllocatedSize());
			}

		private:
			const uint32 bDrawOnlyIfSelected : 1;
			const FVector PlaneExtents;
			const FColor PlaneColor;
			const float LineThickness;
	};

	return new FPlaneSceneProxy(this);
}


FCollisionShape UBBPlaneComponent::GetCollisionShape(float Inflation) const
{
	FVector Extent = GetScaledPlaneExtent() + Inflation;

	if (Inflation < 0.f)
	{
		Extent = Extent.ComponentMax(FVector::ZeroVector);
	}

	return FCollisionShape::MakeBox(Extent);
}
