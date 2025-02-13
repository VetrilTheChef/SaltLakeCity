// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "Commands/Controllers/Interfaces/IBBPlayerControllerCommand.h"
#include "IBBOrderBuildCommand.generated.h"

/**
 * 
 */

class AIBBTargetingActor;
class UIBBBuildData;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBOrderBuildCommand : public UIBBPlayerControllerCommand
{
	GENERATED_BODY()

	public:
		UIBBOrderBuildCommand() : Super() { };

		virtual void SetController(AIBBPlayerController * NewPlayerController) override PURE_VIRTUAL(UIBBOrderBuildCommand::SetController, );

		virtual void SetOuter(UObject * NewOuter) PURE_VIRTUAL(UIBBOrderBuildCommand::SetOuter, );

		virtual void SetBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass) PURE_VIRTUAL(UIBBOrderBuildCommand::SetBuildDataClass, );
		
		virtual const TSoftClassPtr<AIBBTargetingActor> GetTargetingClass() const PURE_VIRTUAL(UIBBOrderBuildCommand::SetTargetingClass, return TSoftClassPtr<AIBBTargetingActor>(); );

		virtual void SetTargetingClass(const TSoftClassPtr<AIBBTargetingActor> NewTargetingClass) PURE_VIRTUAL(UIBBOrderBuildCommand::SetTargetingClass, );
		
		virtual const TArray<FBBBuildablePtr> GetBuildableClasses() const PURE_VIRTUAL(UIBBOrderBuildCommand::GetBuildableClasses, return TArray<FBBBuildablePtr>(); );

		virtual void SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses) PURE_VIRTUAL(UIBBOrderBuildCommand::SetBuildableClasses, );

		virtual void SetPrice(float NewPrice) PURE_VIRTUAL(UIBBOrderBuildCommand::SetPrice, );

		virtual void SetTime(float NewTime) PURE_VIRTUAL(UIBBOrderBuildCommand::SetTime, );

		virtual void Execute() override PURE_VIRTUAL(UIBBOrderBuildCommand::Execute, );
};