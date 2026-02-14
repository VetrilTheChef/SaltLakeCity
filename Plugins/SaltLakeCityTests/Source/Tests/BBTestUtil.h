// SaltLakeCityTests 5.7

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/AutomationTest.h"
#include "BBTestUtil.generated.h"

/**
 * 
 */

class UBBGameInstanceStub;

#define TEST_MAP TEXT("/SaltLakeCityTests/Maps/TestWorld")

#define TEST_TRUE(expression) \
	TEST_BOOLEAN_(TEXT(#expression), expression, true)

#define TEST_FALSE(expression) \
	TEST_BOOLEAN_(TEXT(#expression), expression, false)

#define TEST_BOOLEAN_(text, expression, expected) \
	TestEqual(text, expression, expected);

UCLASS()

class UBBTestUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category="Test")
		static UWorld * GetEditorWorld();

		UFUNCTION(BlueprintCallable, Category="Test")
		static UWorld * GetPIEWorld();

		UFUNCTION(Category = "Test")
		static UWorld * OpenTestWorld();

		UFUNCTION(Category = "Test")
		static void CloseTestWorld(UWorld * TestWorld);

		template <class T>
		static void GetTestAssets(FString Path, TArray<T *> & Assets)
		{
			Assets.Empty();

			FAssetRegistryModule & ARM = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
			IAssetRegistry & AssetRegistry = ARM.Get();

			AssetRegistry.AddPath(Path);
			AssetRegistry.ScanPathsSynchronous({ Path });

			TArray<FAssetData> AssetDataArray;
			AssetRegistry.GetAssetsByPath(* Path, AssetDataArray, true, false);

			for (FAssetData& AssetData : AssetDataArray)
			{
				T * Asset = LoadObject<T>(nullptr, * AssetData.ToSoftObjectPath().GetAssetPathString());

				if (IsValid(Asset)) Assets.Emplace(Asset);
			}
		}

		template <class T>
		static void GetTestClasses(FString Path, TArray<UClass *> & Classes)
		{
			Classes.Empty();

			FAssetRegistryModule & ARM = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
			IAssetRegistry & AssetRegistry = ARM.Get();

			AssetRegistry.AddPath(Path);
			AssetRegistry.ScanPathsSynchronous({ Path });

			TArray<FAssetData> AssetDataArray;

			AssetRegistry.GetAssetsByPath(* Path, AssetDataArray);

			for (FAssetData & AssetData : AssetDataArray)
			{
				UClass * Class = LoadClass<T>(nullptr, * AssetData.ToSoftObjectPath().GetAssetPathString().Append("_C"));

				if (IsValid(Class)) Classes.Emplace(Class);
			}
		}
};