// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBOrderBuildCommand.h"
#include "BBOrderBuildCommandStub.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable)

class UBBOrderBuildCommandStub : public UIBBOrderBuildCommand
{
	GENERATED_BODY()

	public:
		UBBOrderBuildCommandStub();

		virtual AIBBPlayerController * GetController();

		virtual void SetController(AIBBPlayerController * NewController) override;

		UObject * GetOuter();

		virtual void SetOuter(UObject * NewOuter) override;

		TSoftClassPtr<UIBBBuildData> GetBuildDataClass();

		virtual void SetBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass) override;

		virtual const TSoftClassPtr<AIBBTargetingActor> GetTargetingClass() const override;

		virtual void SetTargetingClass(const TSoftClassPtr<AIBBTargetingActor> NewTargetingClass) override;

		virtual const TArray<FBBBuildablePtr> GetBuildableClasses() const override;

		virtual void SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses) override;

		float GetPrice();

		virtual void SetPrice(float NewPrice) override;

		float GetTime();

		virtual void SetTime(float NewTime) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

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

		int Executions;
};