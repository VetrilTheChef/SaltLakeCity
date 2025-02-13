// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "BBViewFactory.generated.h"

/**
 * 
 */

class APlayerController;
class UBBWidget;
class UIBBBuildWidget;
//class UIBBBuildEntryWidget;
class UIBBContextRowWidget;
class UIBBContextWidget;
class UIBBDateTimeWidget;
class UIBBDossierWidget;
//class UIBBDossierEntryWidget;
class UIBBJobWidget;
class UIBBModesWidget;
class UIBBProgressWidget;
class UIBBSelectionWidget;
class UIBBTitleWidget;
class UTexture2D;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBViewFactory : public UObject
{
	GENERATED_BODY()
	
	public:
		UBBViewFactory();

		void Initialize(APlayerController * NewPlayerController);

		void Finalize();

		bool NewBuildView(UIBBBuildWidget * & View);

		// Should never be needed
		//bool NewBuildEntryView(UIBBBuildEntryWidget * & View);

		bool NewContextView(UIBBContextWidget * & View);

		bool NewContextRowView(UIBBContextRowWidget * & View);

		bool NewDateTimeView(UIBBDateTimeWidget * & View);

		bool NewDossierView(UIBBDossierWidget * & View);

		// Should never be needed
		//bool NewDossierEntryView(UIBBDossierEntryWidget * & View);

		bool NewJobView(UIBBJobWidget * & View);

		bool NewModesView(UIBBModesWidget * & View);

		bool NewProgressView(UIBBProgressWidget * & View);

		bool NewSelectionView(UIBBSelectionWidget * & View);

		bool NewTitleView(UIBBTitleWidget * & View);
	
	protected:
		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBBuildWidget> BuildViewClass;

		//UPROPERTY(EditAnywhere, Category = "Classes")
		//TSoftClassPtr<UIBBBuildEntryWidget> BuildEntryViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBContextWidget> ContextViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBContextRowWidget> ContextRowViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBDateTimeWidget> DateTimeViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBDossierWidget> DossierViewClass;

		//UPROPERTY(EditAnywhere, Category = "Classes")
		//TSoftClassPtr<UIBBDossierEntryWidget> DossierEntryViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBJobWidget> JobViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBModesWidget> ModesViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBProgressWidget> ProgressViewClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBSelectionWidget> SelectionViewClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBTitleWidget> TitleViewClass;

		UPROPERTY()
		APlayerController * PlayerController;
};