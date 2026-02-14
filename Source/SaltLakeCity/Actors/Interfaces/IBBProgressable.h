// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBBProgressable.generated.h"

class IBBProgressable;
class IBBWidgetTarget;
class UIBBProgressComponent;

UINTERFACE(MinimalAPI)

class UBBProgressable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class SALTLAKECITY_API IBBProgressable
{
	GENERATED_BODY()

	public:
		virtual float GetProgress() const PURE_VIRTUAL(IBBProgressable::GetProgress, return -1.0f; );

		virtual void SetProgress(float NewProgress) PURE_VIRTUAL(IBBProgressable::SetProgress, );

		virtual UIBBProgressComponent * GetProgressComponent() const PURE_VIRTUAL(IBBProgressable::GetProgressComponent, return nullptr; );

		virtual AActor * ToActor() PURE_VIRTUAL(IBBProgressable::ToActor, return nullptr; );

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() PURE_VIRTUAL(IBBProgressable::ToWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		DECLARE_EVENT(IBBProgressable, FBBProgressInitiation);

		virtual FBBProgressInitiation & OnProgressInitiation() = 0;

		DECLARE_EVENT_OneParam(IBBProgressable, FBBProgressUpdate, float);

		virtual FBBProgressUpdate & OnProgressUpdate() = 0;

		DECLARE_EVENT(IBBProgressable, FBBProgressCompletion);

		virtual FBBProgressCompletion & OnProgressCompletion() = 0;
};

USTRUCT(Blueprintable, BlueprintType)

struct FBBProgressablePtr
{
	GENERATED_BODY()

	public:
		FBBProgressablePtr() :
			Class(nullptr)
		{
		};

		FBBProgressablePtr(UClass * From) :
			Class(From)
		{
		};

		FBBProgressablePtr(const FBBProgressablePtr & Other) :
			Class(Other.Class)
		{
		};

		FORCEINLINE UClass * Get() const
		{
			UClass * Out = Class.LoadSynchronous();

			if (!Out || !Out->ImplementsInterface(UBBProgressable::StaticClass()))
			{
				Out = nullptr;
			}

			return Out;
		};

		FORCEINLINE void operator=(const UClass * From)
		{
			Class = From;
		}

		FORCEINLINE FBBProgressablePtr & operator=(const FBBProgressablePtr & Other)
		{
			Class = Other.Class;
			return * this;
		}

		FORCEINLINE friend bool operator==(const FBBProgressablePtr & Lhs, const FBBProgressablePtr & Rhs)
		{
			return Lhs.Class == Rhs.Class;
		}

		FORCEINLINE friend bool operator!=(const FBBProgressablePtr & Lhs, const FBBProgressablePtr & Rhs)
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
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", MustImplement = "/Script/SaltLakeCity.BBProgressable"))
		TSoftClassPtr<UObject> Class;
};