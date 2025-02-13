// SaltLakeCity 4.25

#include "BBModesModelStub.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"

UBBModesModelStub::UBBModesModelStub() :
	Super()
{
	View = nullptr;
	GameMode = nullptr;
	WidgetSpecification = nullptr;
}

UIBBWidget * UBBModesModelStub::GetWidget() const
{
	return View;
}

void UBBModesModelStub::SetWidget(UIBBModesWidget * NewWidget)
{
	View = NewWidget;
}

UIBBWidgetSpecification * UBBModesModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return WidgetSpecification;
}

void UBBModesModelStub::SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecification = NewWidgetSpecification;
}

void UBBModesModelStub::Initialize(UIBBModesWidget * NewView, AIBBGameMode * NewGameMode)
{
	View = NewView;
	GameMode = NewGameMode;
}

void UBBModesModelStub::Finalize()
{
	View = nullptr;
	GameMode = nullptr;
}

void UBBModesModelStub::UpdateActiveGameMode(EBBGameMode NewGameMode)
{
	OnModeUpdate.Broadcast(NewGameMode);
}
