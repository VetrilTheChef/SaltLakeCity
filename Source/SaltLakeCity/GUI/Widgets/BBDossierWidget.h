// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "BBDossierWidget.generated.h"

/**
 * 
 */

class AIBBCharacterPreview;
class UIBBRadioBox;
class UImage;
class UListView;
class UTextBlock;
class UVerticalBox;
class UWidgetSwitcher;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDossierWidget : public UIBBDossierWidget
{
	GENERATED_BODY()

	public:
		UBBDossierWidget(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void NativeDestruct() override;

		virtual EBBWidget GetType() const override;

		virtual void CreateCharacterPreview(const AIBBCharacter * TemplateCharacter) override;
		
		virtual void DestroyCharacterPreview() override;

		virtual void SetDisplayName(FText NewDisplayName) override;

		virtual void AddAttributeEntry(UIBBDossierEntry * NewEntry) override;

		virtual void AddNeedEntry(UIBBDossierEntry * NewEntry) override;

		virtual void AddSkillEntry(UIBBDossierEntry * NewEntry) override;

		virtual UIBBTitleWidget * & GetTitle() override;

	protected:
		UPROPERTY(EditAnywhere, Category = "Character Preview")
		TSoftClassPtr<AIBBCharacterPreview> CharacterPreviewClass;

		UPROPERTY(EditAnywhere, Category = "Character Preview", meta = (AllowedClasses = "World"))
		FSoftObjectPath CharacterPreviewMap;

		UPROPERTY(meta = (BindWidget))
		UTextBlock * DisplayNameText;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox * Tab0;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox * Tab1;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox * Tab2;

		UPROPERTY(meta = (BindWidget))
		UIBBRadioBox * Tab3;

		UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher * BodySwitcher;

		UPROPERTY(meta = (BindWidget))
		UVerticalBox * Body0;

		UPROPERTY(meta = (BindWidget))
		UVerticalBox * Body1;

		UPROPERTY(meta = (BindWidget))
		UVerticalBox * Body2;

		UPROPERTY(meta = (BindWidget))
		UVerticalBox * Body3;

		UPROPERTY(meta = (BindWidget))
		UListView * AttributeEntries;

		UPROPERTY(meta = (BindWidget))
		UListView * NeedEntries;

		UPROPERTY(meta = (BindWidget))
		UListView * SkillEntries;

		UPROPERTY(meta = (BindWidget))
		UListView * TraitsList;

		UPROPERTY(meta = (BindWidget))
		UListView * EquipmentList;

		UPROPERTY(meta = (BindWidget))
		UImage * CharacterPreview;

		UPROPERTY()
		AIBBCharacterPreview * Character;

		TArray<UIBBRadioBox *> Tabs;

		TArray<UVerticalBox *> Bodies;

		TMap<UEnum *, UListView *> EntryLists;

		FNumberFormattingOptions NumberFormat;

		void InitializeTabs();

		void FinalizeTabs();

		void InitializeBodies();

		void FinalizeBodies();

		void SetAttributeText(UTextBlock * AttributeTextBlock, float AttributeValue);

		UFUNCTION(BlueprintCallable)
		void ToggleCharacterPreview(bool bVisible);

		UFUNCTION()
		void ChangeRadioState(int Index);
};