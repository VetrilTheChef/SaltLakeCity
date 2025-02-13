// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "BBManagedConsumerStruct.generated.h"

/**
*
*/

USTRUCT(BlueprintType)

struct FBBManagedConsumer
{
	GENERATED_BODY()

	public:
		FBBManagedConsumer() : 
			Consumer(nullptr),
			Coefficient(10.0f)
		{
		}

		FBBManagedConsumer(UIBBWorkComponent * NewConsumer) :
			Consumer(NewConsumer),
			Coefficient(10.0f)

		{
		}

		~FBBManagedConsumer()
		{
		}

		UPROPERTY()
		UIBBWorkComponent * Consumer;

		float Coefficient = 10.0;

		friend FORCEINLINE uint32 GetTypeHash(const FBBManagedConsumer & ManagedConsumer)
		{
			return GetTypeHash(ManagedConsumer.Consumer);
		}

		bool operator==(const FBBManagedConsumer & Other) const
		{
			return Consumer == Other.Consumer;
		}

		FORCEINLINE bool operator<(FBBManagedConsumer const & Other) const
		{
			return Coefficient < Other.Coefficient;
		}

		FORCEINLINE bool operator>(FBBManagedConsumer const & Other) const
		{
			return Coefficient > Other.Coefficient;
		}
};