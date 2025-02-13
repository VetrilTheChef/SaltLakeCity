// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "BBCharacterStub.generated.h"

/**
*
*/

class UIBBAIAbilityComponent;
class UIBBDecalComponent;

UCLASS(NotBlueprintable)

class ABBCharacterStub : public AIBBCharacter
{
	GENERATED_BODY()

	public:
		ABBCharacterStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void PossessedBy(AController * NewController) override;

		virtual void UnPossessed() override;

		virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

		void SetAbilitySystemComponent(UAbilitySystemComponent * NewAbilityComponent);

		virtual void UpdateContext(bool Contextualized) override;

		virtual bool IsContextOption(EBBContext Context) const override;

		virtual void SetContextOptions(TSet<EBBContext> NewValidContextOptions);

		virtual UIBBContextComponent * GetContextComponent() const override;

		void SetContextComponent(UIBBContextComponent * NewContextComponent);

		virtual void UpdateHighlight(bool Highlighted) override;

		UIBBDecalComponent * GetDecalComponent() const;

		void SetDecalComponent(UIBBDecalComponent * NewDecalComponent);

		virtual void UpdateSelection(bool Selected) override;

		virtual UIBBSelectionComponent * GetSelectionComponent() const override;

		void SetSelectionComponent(UIBBSelectionComponent * NewSelectionComponent);

		virtual UIBBWorkComponent * GetWorkComponent() const override;

		void SetWorkComponent(UIBBWorkComponent * NewWorkComponent);

		virtual FText GetDisplayName(EBBDisplayName Mode) const override;

		virtual void SetFirstName(FText NewFirstName) override;

		virtual void SetCodeName(FText NewCodeName) override;

		virtual void SetLastName(FText NewLastName) override;

		void SetDisplayName(FText NewDisplayName);

		virtual AActor * ToActor() override;

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

		void LeftClick();

		void RightClick();

	protected:
		UPROPERTY()
		UAbilitySystemComponent * AbilityComponent;

		UPROPERTY()
		UIBBContextComponent * ContextComponent;

		UPROPERTY()
		UIBBDecalComponent * DecalComponent;

		UPROPERTY()
		UIBBSelectionComponent * SelectionComponent;

		UPROPERTY()
		UIBBWorkComponent * WorkComponent;

		UPROPERTY()
		UIBBAbilityTask * Task;

		TSet<EBBContext> ContextOptions;

		FText DisplayName;
};