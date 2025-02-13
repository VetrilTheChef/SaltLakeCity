// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/BBContextRowData.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "BBWidgetFactory.generated.h"

/**
 * 
 */

class UBBControllerFactory;
class UBBModelFactory;
class UBBViewFactory;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBWidgetFactory : public UIBBWidgetFactory
{
	GENERATED_BODY()

	public:
		UBBWidgetFactory();

		virtual void Initialize(const UIBBGameInstance * NewGameInstance, const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, AIBBHUD * NewHUD, APlayerController * NewPlayerController) override;

		virtual void Finalize() override;

		virtual void InjectSpecificationFactory(UIBBSpecificationFactory * NewSpecificationFactory) override;

		virtual bool NewBuildWidget(UIBBBuildWidget * & Widget) const override;

		virtual bool NewBuildEntryWidget(UIBBBuildEntryWidget * & Widget, const UIBBBuildEntry * Entry) const override;

		virtual bool NewContextWidget(UIBBContextWidget * & Widget) const override;

		virtual bool NewDateTimeWidget(UIBBDateTimeWidget * & Widget) const override;

		virtual bool NewDossierWidget(UIBBDossierWidget * & Widget, AIBBCharacter * Character) const override;

		virtual bool NewDossierEntryWidget(UIBBDossierEntryWidget * & Widget, UIBBDossierEntry * Entry) const override;

		virtual bool NewJobWidget(UIBBJobWidget * & Widget) const override;

		virtual bool NewModesWidget(UIBBModesWidget * & Widget) const override;

		virtual bool NewProgressWidget(UIBBProgressWidget * & Widget, UIBBProgressComponent * Component) const override;

		virtual bool NewSelectionWidget(UIBBSelectionWidget * & Widget) const override;

		virtual bool NewTitleWidget(UIBBTitleWidget * & Widget, UIBBGUIModel * ParentModel) const override;

	protected:
		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UBBModelFactory> ModelFactoryClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UBBViewFactory> ViewFactoryClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UBBControllerFactory> ControllerFactoryClass;

		UPROPERTY()
		UBBModelFactory * ModelFactory;

		UPROPERTY()
		UBBViewFactory * ViewFactory;

		UPROPERTY()
		UBBControllerFactory * ControllerFactory;

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
		const UIBBSpecificationFactory * SpecificationFactory;

		void InitializeFactories();

		void InitializeModelFactory();

		void InitializeViewFactory();

		void InitializeControllerFactory();

		void FinalizeFactories();

		void FinalizeModelFactory();

		void FinalizeViewFactory();

		void FinalizeControllerFactory();

		void VerifyFactories() const;
};