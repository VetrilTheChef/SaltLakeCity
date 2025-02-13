// SaltLakeCity 4.24

#include "BBViewFactory.h"
#include "GameFramework/PlayerController.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
//#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
//#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"

UBBViewFactory::UBBViewFactory() :
	Super()
{
	PlayerController = nullptr;
}

void UBBViewFactory::Initialize(APlayerController * NewPlayerController)
{
	PlayerController = NewPlayerController;
}

void UBBViewFactory::Finalize()
{
	PlayerController = nullptr;
}

bool UBBViewFactory::NewBuildView(UIBBBuildWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!BuildViewClass.IsNull(), TEXT("Build View Class is null."));

	View = CreateWidget<UIBBBuildWidget>(PlayerController, BuildViewClass.LoadSynchronous());

	return IsValid(View);
}

// Should never be needed
/*bool UBBViewFactory::NewBuildEntryView(UIBBBuildEntryWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!BuildEntryViewClass.IsNull(), TEXT("Build Entry View Class is null."));

	View = CreateWidget<UIBBBuildEntryWidget>(PlayerController, BuildEntryViewClass.LoadSynchronous());

	return IsValid(View);
}*/

bool UBBViewFactory::NewContextView(UIBBContextWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!ContextViewClass.IsNull(), TEXT("Context View Class is null."));

	View = CreateWidget<UIBBContextWidget>(PlayerController, ContextViewClass.LoadSynchronous());

	return IsValid(View);
}

bool UBBViewFactory::NewContextRowView(UIBBContextRowWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!ContextRowViewClass.IsNull(), TEXT("Context Row View Class is null."));

	View = CreateWidget<UIBBContextRowWidget>(PlayerController, ContextRowViewClass.LoadSynchronous());

	return IsValid(View);
}

bool UBBViewFactory::NewDateTimeView(UIBBDateTimeWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!DateTimeViewClass.IsNull(), TEXT("Date Time View Class is null."));
		
	View = CreateWidget<UIBBDateTimeWidget>(PlayerController, DateTimeViewClass.LoadSynchronous());

	return IsValid(View);
}

bool UBBViewFactory::NewDossierView(UIBBDossierWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!DossierViewClass.IsNull(), TEXT("Dossier View Class is null."));

	View = CreateWidget<UIBBDossierWidget>(PlayerController, DossierViewClass.LoadSynchronous());

	return IsValid(View);
}

// Should never be needed
/*bool UBBViewFactory::NewDossierEntryView(UIBBDossierEntryWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!DossierEntryViewClass.IsNull(), TEXT("Dossier Entry View Class is null."));

	View = CreateWidget<UIBBDossierEntryWidget>(PlayerController, DossierEntryViewClass.LoadSynchronous());

	return IsValid(View);
}*/

bool UBBViewFactory::NewJobView(UIBBJobWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!JobViewClass.IsNull(), TEXT("Job View Class is null."));

	View = CreateWidget<UIBBJobWidget>(PlayerController, JobViewClass.LoadSynchronous());

	return IsValid(View);
}

bool UBBViewFactory::NewModesView(UIBBModesWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!ModesViewClass.IsNull(), TEXT("Job View Class is null."));

	View = CreateWidget<UIBBModesWidget>(PlayerController, ModesViewClass.LoadSynchronous());

	return IsValid(View);
}

bool UBBViewFactory::NewProgressView(UIBBProgressWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!ProgressViewClass.IsNull(), TEXT("Progress View Class is null."));

	View = CreateWidget<UIBBProgressWidget>(PlayerController, ProgressViewClass.LoadSynchronous());

	return IsValid(View);
}

bool UBBViewFactory::NewSelectionView(UIBBSelectionWidget * & View)
{
	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!SelectionViewClass.IsNull(), TEXT("Selection View Class is null."));

	View = CreateWidget<UIBBSelectionWidget>(PlayerController, SelectionViewClass.LoadSynchronous());

	return IsValid(View);
}

bool UBBViewFactory::NewTitleView(UIBBTitleWidget * & View)
{
	if (IsValid(View)) return true;

	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));
	verifyf(!TitleViewClass.IsNull(), TEXT("Title View Class is null."));

	View = CreateWidget<UIBBTitleWidget>(PlayerController, TitleViewClass.LoadSynchronous());

	return IsValid(View);
}