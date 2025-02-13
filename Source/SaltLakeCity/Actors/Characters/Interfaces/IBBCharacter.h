// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "Actors/Interfaces/IBBHighlightable.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "IBBCharacter.generated.h"

/**
*
*/

class UAbilitySystemComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBCharacter : public ACharacter, public IAbilitySystemInterface, public IBBContextualizable, public IBBHighlightable, public IBBSelectable, public IBBWorkable, public IBBWidgetTarget
{
	GENERATED_BODY()

	public:
		AIBBCharacter() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void PossessedBy(AController * NewController) override { Super::PossessedBy(NewController); };

		virtual void UnPossessed() override { Super::UnPossessed(); };

		virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override PURE_VIRTUAL(AIBBCharacter::GetAbilitySystemComponent, return nullptr; );

		virtual float GetNeed(EBBNeed Need) const PURE_VIRTUAL(AIBBCharacter::GetNeed, return -1.0f; );

		virtual void SetNeed(EBBNeed Need, float NewValue) PURE_VIRTUAL(AIBBCharacter::SetNeed, );

		virtual float GetSkill(EBBSkill Skill) const PURE_VIRTUAL(AIBBCharacter::GetSkill, return -1.0f; );

		virtual void SetSkill(EBBSkill Skill, float NewValue) PURE_VIRTUAL(AIBBCharacter::SetSkill, );

		virtual void UpdateContext(bool Contextualized) override PURE_VIRTUAL(AIBBCharacter::UpdateContext, );

		virtual bool IsContextOption(EBBContext ContextOption) const override PURE_VIRTUAL(AIBBCharacter::IsContextOption, return false; );
		
		virtual UIBBContextComponent * GetContextComponent() const override PURE_VIRTUAL(AIBBCharacter::GetContextComponent, return nullptr; );

		virtual void UpdateHighlight(bool Highlighted) override PURE_VIRTUAL(AIBBCharacter::UpdateHighlight, );
		
		virtual UIBBDecalComponent * GetDecalComponent() const override PURE_VIRTUAL(AIBBCharacter::GetDecalComponent, return nullptr; );

		virtual void UpdateSelection(bool Selected) override PURE_VIRTUAL(AIBBCharacter::UpdateSelection, );
		
		virtual UIBBSelectionComponent * GetSelectionComponent() const override PURE_VIRTUAL(AIBBCharacter::GetSelectionComponent, return nullptr; );

		virtual UIBBWorkComponent * GetWorkComponent() const override PURE_VIRTUAL(AIBBCharacter::GetWorkComponent, return nullptr; );

		virtual FText GetDisplayName(EBBDisplayName Mode) const override PURE_VIRTUAL(AIBBCharacter::GetDisplayName, return FText::FromString(""); );

		virtual void SetFirstName(FText NewFirstName) PURE_VIRTUAL(AIBBCharacter::SetFirstName, );

		virtual void SetCodeName(FText NewCodeName) PURE_VIRTUAL(AIBBCharacter::SetCodeName, );

		virtual void SetLastName(FText NewLastName) PURE_VIRTUAL(AIBBCharacter::SetLastName, );

		virtual AActor * ToActor() override PURE_VIRTUAL(AIBBCharacter::ToActor(), return nullptr; );

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override PURE_VIRTUAL(AIBBCharacter::ToWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		DECLARE_DERIVED_EVENT(AIBBCharacter, IBBContextualizable::FBBContextUpdate, FBBContextUpdate);

		virtual FBBContextUpdate & OnContextUpdate() override { return ContextUpdate; }

		DECLARE_DERIVED_EVENT(AIBBCharacter, IBBHighlightable::FBBHighlightUpdate, FBBHighlightUpdate);

		virtual FBBHighlightUpdate & OnHighlightUpdate() override { return HighlightUpdate; }

		DECLARE_DERIVED_EVENT(AIBBCharacter, IBBSelectable::FBBSelectionUpdate, FBBSelectionUpdate);

		virtual FBBSelectionUpdate & OnSelectionUpdate() override { return SelectionUpdate; }

		DECLARE_DERIVED_EVENT(AIBBCharacter, IBBWidgetTarget::FBBWidgetTargetUpdate, FBBWidgetTargetUpdate);

		virtual FBBWidgetTargetUpdate & OnWidgetTargetUpdate() final override { return WidgetTargetUpdate; };

	protected:
		FBBContextUpdate ContextUpdate;

		FBBHighlightUpdate HighlightUpdate;

		FBBSelectionUpdate SelectionUpdate;

		FBBWidgetTargetUpdate WidgetTargetUpdate;
};