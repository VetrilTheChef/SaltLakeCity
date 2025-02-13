// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "BBWidgetFactoryStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBWidgetFactoryStub : public UIBBWidgetFactory
{
	GENERATED_BODY()
	
	public:
		UBBWidgetFactoryStub();

		virtual void Initialize(const UIBBGameInstance * NewGameInstance, const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, AIBBHUD * NewHUD, APlayerController * NewPlayerController) override;

		virtual void Finalize();

		void AddWidget(UIBBWidget * Widget);

		virtual bool NewBuildWidget(UIBBBuildWidget * & Widget) const override;

		virtual bool NewBuildEntryWidget(UIBBBuildEntryWidget * & Widget, const UIBBBuildEntry * Entry) const override;

		virtual bool NewContextWidget(UIBBContextWidget * & Widget) const override;

		virtual bool NewDateTimeWidget(UIBBDateTimeWidget * & Widget) const override;

		virtual bool NewDossierWidget(UIBBDossierWidget * & Widget, AIBBCharacter * Character) const override;

		virtual bool NewDossierEntryWidget(UIBBDossierEntryWidget * & Widget, UIBBDossierEntry * Entry) const override;

		virtual bool NewJobWidget(UIBBJobWidget * & Widget) const override;

		virtual bool NewProgressWidget(UIBBProgressWidget * & Widget, UIBBProgressComponent * Component) const override;

		virtual bool NewSelectionWidget(UIBBSelectionWidget * & Widget) const override;

		virtual bool NewTitleWidget(UIBBTitleWidget * & Widget, UIBBGUIModel * ParentModel) const override;

	protected:
		UPROPERTY()
		const UIBBGameInstance * GameInstance;

		UPROPERTY()
		const AIBBGameState * GameState;

		UPROPERTY()
		AIBBGameMode * GameMode;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		APlayerController * PlayerController;

		UPROPERTY()
		mutable TArray<UIBBWidget *> Widgets;
};