// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Buildings/Interfaces/IBBBuilding.h"
#include "BBBuilding.generated.h"

/**
 * 
 */

class UBBBuildingData;
class UIBBComponentFactory;
class UIBBContextComponent;
class UIBBProgressComponent;
class UIBBSelectionComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API ABBBuilding : public AIBBBuilding
{
	GENERATED_BODY()
	
	public:
		ABBBuilding();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual float GetPrice() const override;

		virtual void SetPrice(float NewPrice) override;

		virtual float GetBuildTime() const override;

		virtual void SetBuildTime(float NewBuildTime) override;

		virtual float GetProgress() const override;

		virtual void SetProgress(float NewProgress) override;

		virtual void AddMaterialOverride(UMaterialInterface * NewMaterialOverride) override;

		virtual void RemoveMaterialOverride() override;

		virtual void StartBuilding() override;

		virtual void StopBuilding() override;

		virtual void UpdateContext(bool Contextualized) override;

		virtual bool IsContextOption(EBBContext ContextOption) const override;

		virtual UIBBContextComponent * GetContextComponent() const override;

		virtual void UpdateSelection(bool Selected) override;

		virtual UIBBSelectionComponent * GetSelectionComponent() const override;

		virtual FText GetDisplayName(EBBDisplayName Mode) const override;

		virtual AActor * ToActor() override;

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

		virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

		virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;

		virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

		virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	protected:
		UPROPERTY(Category = "Default | Context", EditAnywhere, BlueprintReadWrite)
		TSet<EBBContext> ContextOptions;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Asset")
		TSoftClassPtr<UBBBuildingData> Data;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
		FGameplayTagContainer GameplayTags;

		UPROPERTY()
		UIBBContextComponent * ContextComponent;

		UPROPERTY()
		UIBBProgressComponent * ProgressComponent;

		UPROPERTY()
		UIBBSelectionComponent * SelectionComponent;

		FText DisplayName;

		float Price;

		float BuildTime;

		float Progress;

		void CreateContextComponent(const UIBBComponentFactory & ComponentFactory);

		void CreateProgressComponent(const UIBBComponentFactory & ComponentFactory);

		void CreateSelectionComponent(const UIBBComponentFactory & ComponentFactory);

		void DestroyContextComponent();

		void DestroyProgressComponent();

		void DestroySelectionComponent();
};