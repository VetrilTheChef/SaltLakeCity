// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Buildings/Interfaces/IBBBuilding.h"
#include "BBBuildingStub.generated.h"

/**
 * 
 */

class UIBBProgressComponent;

UCLASS(NotBlueprintable)

class ABBBuildingStub : public AIBBBuilding
{
	GENERATED_BODY()
	
	public:
		ABBBuildingStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		UIBBProgressComponent * GetProgressComponent() const;

		void SetProgressComponent(UIBBProgressComponent * NewProgressComponent);

		virtual float GetPrice() const override;

		virtual void SetPrice(float NewPrice) override;

		virtual float GetBuildTime() const override;

		virtual void SetBuildTime(float NewBuildTime) override;

		virtual float GetProgress() const override;

		virtual void SetProgress(float NewProgress) override;

		virtual void AddMaterialOverride(UMaterialInterface * NewMaterialOverride) override;

		virtual void RemoveMaterialOverride() override;

		virtual UMaterialInterface * GetMaterialOverride();

		virtual void StartBuilding() override;

		virtual void StopBuilding() override;

		virtual void UpdateContext(bool Contextualized) override;

		virtual bool IsContextOption(EBBContext Context) const override;

		virtual void SetContextOptions(TSet<EBBContext> NewValidContextOptions);

		virtual void UpdateSelection(bool Selected) override;

		virtual UIBBSelectionComponent * GetSelectionComponent() const override;

		void SetSelectionComponent(UIBBSelectionComponent * NewSelectionComponent);

		virtual FText GetDisplayName(EBBDisplayName Mode) const override;

		virtual void SetDisplayName(FText NewDisplayName);

		virtual AActor * ToActor() override;

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

		virtual void GetOwnedGameplayTags(FGameplayTagContainer & TagContainer) const override;

		void SetOwnedGameplayTags(FGameplayTagContainer & TagContainer);

		virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;

		virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer & TagContainer) const override;

		virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer & TagContainer) const override;

	protected:
		UPROPERTY()
		UIBBProgressComponent * ProgressComponent;

		UPROPERTY()
		UIBBSelectionComponent * SelectionComponent;

		UPROPERTY()
		UMaterialInterface * MaterialOverride;

		TSet<EBBContext> ContextOptions;

		FGameplayTagContainer GameplayTags;

		FText DisplayName;

		float Price;

		float BuildTime;

		float Progress;
};