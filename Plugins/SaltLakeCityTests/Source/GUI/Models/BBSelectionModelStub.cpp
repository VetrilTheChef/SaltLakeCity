// SaltLakeCity 4.26

#include "BBSelectionModelStub.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"

UBBSelectionModelStub::UBBSelectionModelStub() :
	Super()
{
	View = nullptr;
	HUD = nullptr;

	SelectionComponent = nullptr;
	WidgetSpecification = nullptr;
}

UIBBWidget * UBBSelectionModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBSelectionModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return WidgetSpecification;
}

void UBBSelectionModelStub::SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecification = NewWidgetSpecification;
}

void UBBSelectionModelStub::Initialize(UIBBSelectionWidget * NewView, AIBBHUD * NewHUD)
{
	View = NewView;
	HUD = NewHUD;

	if (IsValid(HUD))
	{
		HUD->OnSelectionUpdate().AddUObject(this, & UBBSelectionModelStub::UpdateSelection);
	}
}

void UBBSelectionModelStub::Finalize()
{
	if (IsValid(HUD))
	{
		HUD->OnSelectionUpdate().RemoveAll(this);
	}

	HUD = nullptr;
	View = nullptr;
}

const UIBBSelectionComponent * UBBSelectionModelStub::GetComponent() const
{
	return SelectionComponent;
}



void UBBSelectionModelStub::UpdateSelection(UIBBSelectionComponent * NewSelectionComponent)
{
	SelectionComponent = NewSelectionComponent;
}