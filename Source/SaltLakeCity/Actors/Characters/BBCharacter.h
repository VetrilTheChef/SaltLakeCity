// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "BBCharacter.generated.h"

/**
*
*/

class UIBBAIAbilityComponent;;
class UIBBContextComponent;
class UIBBComponentFactory;
class UIBBDecalComponent;
class UIBBSelectionComponent;
class UIBBWorkComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API ABBCharacter : public AIBBCharacter
{
	GENERATED_BODY()

	public:
		ABBCharacter();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void PossessedBy(AController * NewController) override;

		virtual void UnPossessed() override;

		virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

		virtual void UpdateContext(bool Contextualized) override;

		virtual bool IsContextOption(EBBContext Context) const override;

		virtual UIBBContextComponent * GetContextComponent() const override;

		virtual void UpdateHighlight(bool Highlighted) override;

		virtual UIBBDecalComponent * GetDecalComponent() const override;

		virtual void UpdateSelection(bool Selected) override;

		virtual UIBBSelectionComponent * GetSelectionComponent() const override;

		virtual UIBBWorkComponent * GetWorkComponent() const override;

		virtual FText GetDisplayName(EBBDisplayName Mode) const;

		virtual void SetFirstName(FText NewFirstName) override;

		virtual void SetCodeName(FText NewCodeName) override;

		virtual void SetLastName(FText NewLastName) override;

		virtual AActor * ToActor() override;

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() override;

	protected:
		UPROPERTY(Category = "Default | Context", EditAnywhere, BlueprintReadWrite)
		TSet<EBBContext> ContextOptions;

		UPROPERTY(Category = "Default | Attributes", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> NeedsDataTable;

		UPROPERTY(Category = "Default | Attributes", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> SkillsDataTable;

		UPROPERTY()
		UIBBAIAbilityComponent * AbilityComponent;

		UPROPERTY()
		UIBBContextComponent * ContextComponent;

		UPROPERTY()
		UIBBDecalComponent * DecalComponent;

		UPROPERTY()
		UIBBSelectionComponent * SelectionComponent;

		UPROPERTY()
		UIBBWorkComponent * WorkComponent;

		typedef void (ABBCharacter::* EventCallback)(bool);

		TMap<FKey, TArray<TPair<EventCallback, bool>>> FocusedCallbacks;

		TArray<TPair<EventCallback, bool>> UnfocusedCallbacks;

		typedef FText (ABBCharacter::* NameFormat)() const;

		TMap<EBBDisplayName, NameFormat> NameFormats;

		FText FirstName;

		FText CodeName;

		FText LastName;

		void InitializeCapsuleComponent();

		void InitializeSkeletalMeshComponent();

		void InitializeEventCallbacks();

		void InitializeNameFormats();

		void FinalizeEventCallbacks();

		void FinalizeNameFormats();

		void CreateAbilityComponent(const UIBBComponentFactory & ComponentFactory);

		void CreateContextComponent(const UIBBComponentFactory & ComponentFactory);

		void CreateDecalComponent(const UIBBComponentFactory & ComponentFactory);

		void CreateSelectionComponent(const UIBBComponentFactory & ComponentFactory);

		void CreateWorkComponent(const UIBBComponentFactory & ComponentFactory);

		void DestroyAbilityComponent();

		void DestroyContextComponent();

		void DestroyDecalComponent();

		void DestroySelectionComponent();

		void DestroyWorkComponent();

		FText GetShortName() const;

		FText GetLongName() const;

		FText GetCodeName() const;

		FText GetFullName() const;

		UFUNCTION()
		void OnClick(AActor * TouchedActor, FKey ButtonPressed);
};