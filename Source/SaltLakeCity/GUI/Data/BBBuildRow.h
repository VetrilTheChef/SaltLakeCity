// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "BBBuildRow.generated.h"

/**
 * 
 */

class AIBBBuilding;

USTRUCT(BlueprintType)

struct FBBBuildingEntry
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Price;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Time;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBBBuildablePtr Class;
};

USTRUCT(BlueprintType)

struct FBBBuildRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBBBuildCategory Category;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> Icon;

		UPROPERTY()
		float Price;

		UPROPERTY()
		float Time;

		virtual TArray<FBBBuildablePtr> GetBuildables()
		{
			TArray<FBBBuildablePtr> Out;

			for (FBBBuildingEntry & Buildable : Buildables)
			{
				Out.Emplace(Buildable.Class);
			}

			return Out;
		};

		virtual void OnDataTableChanged(const UDataTable * InDataTable, const FName InRowName) override
		{
			Super::OnDataTableChanged(InDataTable, InRowName);

			FString Context = TEXT("Context_");
			Context.Append(Name.ToString());

			if (InDataTable->FindRow<FBBBuildRow>(InRowName, Context) == this)
			{
				Price = 0.0f;
				Time = 0.0f;

				for (FBBBuildingEntry & Buildable : Buildables)
				{
					Price += Buildable.Price;
					Time += Buildable.Time;
				}
			}
		};

	protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBBBuildingEntry> Buildables;
};