// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBOrderBuildCommand.h"
#include "BBOrderBuildCommand.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBOrderBuildCommand : public UIBBOrderBuildCommand
{
	GENERATED_BODY()

	public:
		UBBOrderBuildCommand();

		virtual void SetController(AIBBPlayerController * NewController) override;

		virtual void SetOuter(UObject * NewOuter) override;

		virtual void SetBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass) override;

		virtual const TSoftClassPtr<AIBBTargetingActor> GetTargetingClass() const override;

		virtual void SetTargetingClass(const TSoftClassPtr<AIBBTargetingActor> NewTargetingClass) override;
		
		virtual const TArray<FBBBuildablePtr> GetBuildableClasses() const override;

		virtual void SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses) override;

		virtual void SetPrice(float NewPrice) override;

		virtual void SetTime(float NewTime) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBPlayerController * Controller;

		UPROPERTY()
		UObject * Outer;

		UPROPERTY()
		TSoftClassPtr<UIBBBuildData> BuildDataClass;

		UPROPERTY()
		TSoftClassPtr<AIBBTargetingActor> TargetingClass;

		UPROPERTY()
		TArray<FBBBuildablePtr> BuildableClasses;

		float Price;

		float Time;
};