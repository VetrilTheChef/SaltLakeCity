// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBBBuildable.generated.h"

UINTERFACE(MinimalAPI)

class UBBBuildable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class SALTLAKECITY_API IBBBuildable
{
	GENERATED_BODY()

	public:
		virtual float GetPrice() const PURE_VIRTUAL(IBBBuildable::GetPrice, return -1.0f; );

		virtual void SetPrice(float NewPrice) PURE_VIRTUAL(IBBBuildable::SetPrice, );

		virtual float GetBuildTime() const PURE_VIRTUAL(IBBBuildable::GetBuildTime, return -1.0f; );

		virtual void SetBuildTime(float NewBuildTime) PURE_VIRTUAL(IBBBuildable::SetBuildTime, );

		virtual void AddMaterialOverride(UMaterialInterface * NewMaterialOverride) PURE_VIRTUAL(IBBBuildable::AddMaterialOverride, );

		virtual void RemoveMaterialOverride() PURE_VIRTUAL(IBBBuildable::RemoveMaterialOverride, );

		virtual void StartBuilding() PURE_VIRTUAL(IBBBuildable::StartBuilding, );

		virtual void StopBuilding() PURE_VIRTUAL(IBBBuildable::StopBuilding, );

		virtual AActor * ToActor() PURE_VIRTUAL(IBBBuildable::ToActor(), return nullptr; );
};

USTRUCT(Blueprintable, BlueprintType)

struct FBBBuildablePtr
{
	GENERATED_BODY()

	public:
		FBBBuildablePtr() :
			Class(nullptr)
		{
		};

		FBBBuildablePtr(UClass * From) :
			Class(From)
		{
		};

		FBBBuildablePtr(const FBBBuildablePtr & Other) :
			Class(Other.Class)
		{
		};

		FORCEINLINE UClass * Get() const
		{
			UClass * Out = Class.LoadSynchronous();

			if (!Out || !Out->ImplementsInterface(UBBBuildable::StaticClass()))
			{
				Out = nullptr;
			}

			return Out;
		};

		FORCEINLINE void operator=(const UClass * From)
		{
			Class = From;
		}

		FORCEINLINE FBBBuildablePtr & operator=(const FBBBuildablePtr & Other)
		{
			Class = Other.Class;
			return * this;
		}

		FORCEINLINE friend bool operator==(const FBBBuildablePtr & Lhs, const FBBBuildablePtr & Rhs)
		{
			return Lhs.Class == Rhs.Class;
		}

		FORCEINLINE friend bool operator!=(const FBBBuildablePtr & Lhs, const FBBBuildablePtr & Rhs)
		{
			return Lhs.Class != Rhs.Class;
		}

		FORCEINLINE UClass & operator*() const
		{
			return * Get();
		}


		FORCEINLINE UClass * operator->() const
		{
			return Get();
		}

		FORCEINLINE bool IsValid() const
		{
			return Get() != nullptr;
		}

		FORCEINLINE explicit operator bool() const
		{
			return IsValid();
		}

	protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", MustImplement = "Buildable"))
		TSoftClassPtr<UObject> Class;
};