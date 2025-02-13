// SaltLakeCity 4.25

#include "BBGUIModelStub.h"

UBBGUIModelStub::UBBGUIModelStub() :
	Super()
{
	View = nullptr;
	WidgetSpecification = nullptr;
}

UIBBWidget * UBBGUIModelStub::GetWidget() const
{
	return View;
}

void UBBGUIModelStub::SetWidget(UIBBWidget * NewWidget)
{
	View = NewWidget;
}

UIBBWidgetSpecification * UBBGUIModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return WidgetSpecification;
}

void UBBGUIModelStub::SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecification = NewWidgetSpecification;
}