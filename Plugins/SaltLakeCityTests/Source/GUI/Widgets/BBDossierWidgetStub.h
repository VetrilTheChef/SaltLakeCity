// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "BBDossierWidgetStub.generated.h"

/**
 * 
 */

class UIBBTitleWidget;

UCLASS(NotBlueprintable)

class UBBDossierWidgetStub : public UIBBDossierWidget
{
	GENERATED_BODY()

	public:
		UBBDossierWidgetStub(const FObjectInitializer& ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void NativeDestruct() override;

		virtual EBBWidget GetType() const override;

		void AddToScreen(int32 ZOrder = 0) override;

		virtual void CreateCharacterPreview(const AIBBCharacter * TemplateCharacter) override;

		virtual void DestroyCharacterPreview() override;

		FText GetDisplayName();

		virtual void SetDisplayName(FText NewDisplayName) override;

		TArray<UIBBDossierEntry*> GetAttributeEntries() const;

		virtual void AddAttributeEntry(UIBBDossierEntry* NewEntry) override;

		TArray<UIBBDossierEntry*> GetNeedEntries() const;

		virtual void AddNeedEntry(UIBBDossierEntry* NewEntry) override;

		TArray<UIBBDossierEntry*> GetSkillEntries() const;

		virtual void AddSkillEntry(UIBBDossierEntry* NewEntry) override;

		virtual UIBBTitleWidget*& GetTitle() override;

	protected:
		UPROPERTY()
		TArray<UIBBDossierEntry*> AttributeEntries;

		UPROPERTY()
		TArray<UIBBDossierEntry*> NeedEntries;

		UPROPERTY()
		TArray<UIBBDossierEntry*> SkillEntries;

		FText DisplayName;
};