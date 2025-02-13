// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
// Keep the includes in this order
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "BBDossierModel.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDossierModel : public UIBBDossierModel
{
	GENERATED_BODY()

	public:
		UBBDossierModel();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;
		
		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual UDataTable * GetAttributesDataTable() const override;

		virtual UDataTable * GetNeedsDataTable() const override;

		virtual UDataTable * GetSkillsDataTable() const override;

		virtual void Initialize(UIBBDossierWidget * NewView, AIBBCharacter * NewCharacter) override;

		virtual void Finalize() override;
		
		virtual const AIBBCharacter * GetCharacter() const override;

		virtual FText GetDisplayName() const override;

		UIBBDossierEntry * GetDossierEntry(EBBAttribute Attribute) const override;

		UIBBDossierEntry * GetDossierEntry(EBBNeed Need) const override;

		UIBBDossierEntry * GetDossierEntry(EBBSkill Skill) const override;
		 
	protected:
		UPROPERTY(Category = "Data Table", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> AttributesDataTable;

		UPROPERTY(Category = "Data Table", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> NeedsDataTable;

		UPROPERTY(Category = "Data Table", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> SkillsDataTable;

		UPROPERTY(Category = "Classes", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UIBBDossierEntry> DossierEntryClass;

		UPROPERTY()
		UIBBDossierWidget * View;

		UPROPERTY()
		AIBBCharacter * Character;

		UPROPERTY()
		TMap<EBBAttribute, UIBBDossierEntry *> AttributeEntries;
		using AttributeMap = TMap<EBBAttribute, UIBBDossierEntry *>;

		UPROPERTY()
		TMap<EBBNeed, UIBBDossierEntry *> NeedEntries;
		using NeedMap = TMap<EBBNeed, UIBBDossierEntry *>;

		UPROPERTY()
		TMap<EBBSkill, UIBBDossierEntry *> SkillEntries;
		using SkillMap = TMap<EBBSkill, UIBBDossierEntry *>;

		TMap<FString, EBBAttribute> AttributeDataToEnum;

		TMap<FString, EBBNeed> NeedDataToEnum;

		TMap<FString, EBBSkill> SkillDataToEnum;

		void InitializeView(UIBBDossierWidget * NewView);

		void InitializeCharacter(AIBBCharacter * NewCharacter);

		void InitializeEntries(UAbilitySystemComponent & AbilityComponent);

		void FinalizeView();

		void FinalizeCharacter();

		void FinalizeEntries(UAbilitySystemComponent * AbilityComponent);

		template <class T>
		const T * GetAttributeSet(AIBBCharacter * SetCharacter) const
		{
			verifyf(IsValid(SetCharacter), TEXT("Character is invalid."));

			UIBBAIAbilityComponent * AbilityComponent = Cast<UIBBAIAbilityComponent>(SetCharacter->GetAbilitySystemComponent());

			verifyf(IsValid(AbilityComponent), TEXT("Ability Component is invalid."));

			return AbilityComponent->GetSet<T>();
		}

		template <class T, typename R, typename M>
		void InitializeEntries(T * Set, UDataTable * DataTable, M & EntryMap)
		{
			verifyf(IsValid(Set), TEXT("Set is invalid."));
			verifyf(IsValid(DataTable), TEXT("Data Table is invalid."));
			verifyf(!DossierEntryClass.IsNull(), TEXT("Attribute Entry Class is null."));

			for (const TPair<FName, uint8 *> & Iterator : DataTable->GetRowMap())
			{
				R * TableRow = (R *)Iterator.Value;

				if (TableRow)
				{
					UIBBDossierEntry * Entry = NewObject<UIBBDossierEntry>(this, DossierEntryClass.LoadSynchronous());

					verifyf(IsValid(Entry), TEXT("New Entry is invalid."));

					Entry->Initialize(TableRow->Name, TableRow->Icon, & Set->OnValueUpdate(TableRow->Enumerator), & Set->OnMaxValueUpdate(TableRow->Enumerator));

					EntryMap.FindOrAdd(TableRow->Enumerator, Entry);
				}
			}
		}

		UFUNCTION()
		void UpdateWidgetTarget();
};
