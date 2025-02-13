// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "Actors/Interfaces/IBBProgressable.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "Engine/StaticMeshActor.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "GameplayTags/Classes/GameplayTagAssetInterface.h"
#include "IBBBuilding.generated.h"

/**
 * 
 */

class UMaterialInterface;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBBuilding : public AStaticMeshActor, public IBBBuildable, public IBBContextualizable, public IBBProgressable, public IBBSelectable, public IBBWidgetTarget, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
	public:
		AIBBBuilding() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual float GetPrice() const override PURE_VIRTUAL(AIBBBuilding::GetPrice, return -1.0f; );

		virtual void SetPrice(float NewPrice) override PURE_VIRTUAL(AIBBBuilding::SetPrice, );

		virtual float GetBuildTime() const override PURE_VIRTUAL(AIBBBuilding::GetBuildTime, return -1.0f; );

		virtual void SetBuildTime(float NewBuildTime) override PURE_VIRTUAL(AIBBBuilding::SetBuildTime, );

		virtual float GetProgress() const override PURE_VIRTUAL(AIBBBuilding::GetProgress, return -1.0f; );

		virtual void SetProgress(float NewProgress) override PURE_VIRTUAL(AIBBBuilding::SetProgress, );

		virtual void AddMaterialOverride(UMaterialInterface * NewMaterialOverride) override PURE_VIRTUAL(AIBBBuilding::AddMaterialOverride, );

		virtual void RemoveMaterialOverride() override PURE_VIRTUAL(AIBBBuilding::RemoveMaterialOverride, );

		virtual void StartBuilding() override PURE_VIRTUAL(AIBBBuilding::StartBuilding, );

		virtual void StopBuilding() override PURE_VIRTUAL(AIBBBuilding::StopBuilding, );

		virtual void UpdateContext(bool Contextualized) override PURE_VIRTUAL(AIBBBuilding::UpdateContext, );

		virtual bool IsContextOption(EBBContext ContextOption) const override PURE_VIRTUAL(AIBBBuilding::IsContextOption, return false; );

		virtual UIBBContextComponent * GetContextComponent() const override PURE_VIRTUAL(AIBBBuilding::GetContextComponent, return nullptr; );

		virtual void UpdateSelection(bool Selected) override PURE_VIRTUAL(AIBBBuilding::UpdateSelection, );

		virtual UIBBSelectionComponent * GetSelectionComponent() const override PURE_VIRTUAL(AIBBBuilding::GetSelectionComponent, return nullptr; );
		
		virtual FText GetDisplayName(EBBDisplayName Mode) const override PURE_VIRTUAL(AIBBBuilding::GetDisplayName, return FText::FromString(""); );

		virtual AActor * ToActor() override PURE_VIRTUAL(AIBBBuilding::ToActor(), return nullptr; );

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override PURE_VIRTUAL(AIBBBuilding::ToWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		UFUNCTION(BlueprintCallable, Category = "GameplayTags")
		virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override PURE_VIRTUAL(AIBBBuilding::GetOwnedGameplayTags, );

		UFUNCTION(BlueprintCallable, Category = "GameplayTags")
		virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override PURE_VIRTUAL(AIBBBuilding::HasMatchingGameplayTag, return false; );

		UFUNCTION(BlueprintCallable, Category = "GameplayTags")
		virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override PURE_VIRTUAL(AIBBBuilding::HasAllMatchingGameplayTags, return false; );

		UFUNCTION(BlueprintCallable, Category = "GameplayTags")
		virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override PURE_VIRTUAL(AIBBBuilding::HasAnyMatchingGameplayTags, return false; );

		DECLARE_DERIVED_EVENT(AIBBBuilding, IBBContextualizable::FBBContextUpdate, FBBContextUpdate);

		virtual FBBContextUpdate & OnContextUpdate() final override { return ContextUpdate; }

		DECLARE_DERIVED_EVENT(AIBBBuilding, IBBProgressable::FBBProgressInitiation, FBBProgressInitiation);

		virtual FBBProgressInitiation & OnProgressInitiation() override { return ProgressInitiation; }

		DECLARE_DERIVED_EVENT(AIBBBuilding, IBBProgressable::FBBProgressUpdate, FBBProgressUpdate);

		virtual FBBProgressUpdate & OnProgressUpdate() override { return ProgressUpdate; }

		DECLARE_DERIVED_EVENT(AIBBBuilding, IBBProgressable::FBBProgressCompletion, FBBProgressCompletion);

		virtual FBBProgressCompletion & OnProgressCompletion() override { return ProgressCompletion; }

		DECLARE_DERIVED_EVENT(AIBBBuilding, IBBSelectable::FBBSelectionUpdate, FBBSelectionUpdate);

		virtual FBBSelectionUpdate & OnSelectionUpdate() override { return SelectionUpdate; }

		DECLARE_DERIVED_EVENT(AIBBBuilding, IBBWidgetTarget::FBBWidgetTargetUpdate, FBBWidgetTargetUpdate);

		virtual FBBWidgetTargetUpdate & OnWidgetTargetUpdate() override { return WidgetTargetUpdate; }

	protected:
		FBBContextUpdate ContextUpdate;

		FBBProgressInitiation ProgressInitiation;

		FBBProgressUpdate ProgressUpdate;

		FBBProgressCompletion ProgressCompletion;

		FBBSelectionUpdate SelectionUpdate;

		FBBWidgetTargetUpdate WidgetTargetUpdate;
};