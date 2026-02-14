// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBAttributeEnum.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBDossierWidget.generated.h"

/**
 * 
 */

class AIBBCharacter;
class UIBBDossierEntry;
class UIBBGameInstance;
class UIBBTitleWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierWidget : public UIBBWidget
{
	GENERATED_BODY()

	public:
		UIBBDossierWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeOnInitialized() override
			{ Super::NativeOnInitialized(); };

		virtual void NativeDestruct() override
			{ Super::NativeDestruct(); };

		virtual EBBWidget GetType() const
			PURE_VIRTUAL(UIBBDossierWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBDossierWidget::AddToScreen, );

		virtual void CreateCharacterPreview(const AIBBCharacter* TemplateCharacter)
			PURE_VIRTUAL(UIBBDossierWidget::CreateCharacterPreview, );

		virtual void DestroyCharacterPreview()
			PURE_VIRTUAL(UIBBDossierWidget::DestroyCharacterPreview, );

		virtual void SetDisplayName(FText NewDisplayName)
			PURE_VIRTUAL(UIBBDossierWidget::SetDisplayName, );

		virtual void AddAttributeEntry(UIBBDossierEntry* NewEntry)
			PURE_VIRTUAL(UIBBDossierWidget::AddAttributeEntry, );

		virtual void AddNeedEntry(UIBBDossierEntry* NewEntry)
			PURE_VIRTUAL(UIBBDossierWidget::AddNeedEntry, );

		virtual void AddSkillEntry(UIBBDossierEntry* NewEntry)
			PURE_VIRTUAL(UIBBDossierWidget::AddSkillEntry, );

		virtual UIBBTitleWidget*& GetTitle()
			PURE_VIRTUAL(UIBBDossierWidget::GetTitle, return Title; );

	protected:
		UPROPERTY(meta = (BindWidget))
		UIBBTitleWidget* Title;
};