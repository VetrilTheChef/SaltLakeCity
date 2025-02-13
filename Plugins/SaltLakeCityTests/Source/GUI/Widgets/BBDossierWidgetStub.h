// SaltLakeCity 4.26

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
		UBBDossierWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void NativeDestruct() override;

		virtual EBBWidget GetType() const override;

		virtual void CreateCharacterPreview(const AIBBCharacter * TemplateCharacter) override;

		virtual void DestroyCharacterPreview() override;

		FText GetDisplayName();

		virtual void SetDisplayName(FText NewDisplayName) override;

		int GetNumAttributeEntries();

		UIBBDossierEntry * GetAttributeEntry(int Index);

		virtual void AddAttributeEntry(UIBBDossierEntry * NewEntry) override;

		int GetNumNeedEntries();

		UIBBDossierEntry * GetNeedEntry(int Index);

		virtual void AddNeedEntry(UIBBDossierEntry * NewEntry) override;

		int GetNumSkillEntries();

		UIBBDossierEntry * GetSkillEntry(int Index);

		virtual void AddSkillEntry(UIBBDossierEntry * NewEntry) override;

		virtual UIBBTitleWidget * & GetTitle() override;

	protected:
		UPROPERTY()
		TArray<UIBBDossierEntry *> AttributeEntries;

		UPROPERTY()
		TArray<UIBBDossierEntry *> NeedEntries;

		UPROPERTY()
		TArray<UIBBDossierEntry *> SkillEntries;

		FText DisplayName;
};