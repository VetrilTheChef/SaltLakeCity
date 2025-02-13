// SaltLakeCity 4.27

#include "BBTitleModelStub.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBTitleModelStub::UBBTitleModelStub() :
	Super()
{
	View = nullptr;
	WidgetSpecification = nullptr;
	ParentModel = nullptr;
	ParentWidget = nullptr;
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
	ParentWidgetSpecification = nullptr;
	HUD = nullptr;
}

TScriptInterface<IBBWidgetTarget> UBBTitleModelStub::GetWidgetTarget() const
{
	return WidgetTarget;
}

void UBBTitleModelStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

UIBBWidget * UBBTitleModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBTitleModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return WidgetSpecification;
}

void UBBTitleModelStub::SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecification = NewWidgetSpecification;
}

void UBBTitleModelStub::Initialize(UIBBTitleWidget * NewView, UIBBGUIModel * NewParentModel, AIBBHUD * NewHUD)
{
	Finalize();

	View = NewView;
	ParentModel = NewParentModel;
	ParentWidgetSpecification = nullptr;
	HUD = NewHUD;

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(ParentWidget));
}

void UBBTitleModelStub::Finalize()
{
	View = nullptr;
	ParentModel = nullptr;
	HUD = nullptr;
}

FVector2D UBBTitleModelStub::GetPosition()
{
	return Position;
}

void UBBTitleModelStub::SetPosition(FVector2D NewPosition)
{
	Position = NewPosition;
}

UIBBWidget * UBBTitleModelStub::GetParentWidget() const
{
	return ParentWidget;
}

void UBBTitleModelStub::SetParentWidget(UIBBWidget * NewParentWidget)
{
	ParentWidget = NewParentWidget;

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(ParentWidget));
}

UIBBWidgetSpecification * UBBTitleModelStub::GetParentWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return ParentWidgetSpecification;
}

void UBBTitleModelStub::SetParentWidgetSpecification(UIBBWidgetSpecification * NewParentWidgetSpecification)
{
	ParentWidgetSpecification = NewParentWidgetSpecification;
}