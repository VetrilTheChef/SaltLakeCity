// SaltLakeCity 4.27

#include "BBWidgetTargetStub.h"

UBBWidgetTargetStub::UBBWidgetTargetStub() :
	Super()
{
	DisplayName = FText::FromString("");
}

FText UBBWidgetTargetStub::GetDisplayName(EBBDisplayName Mode) const
{
	return DisplayName;
}

void UBBWidgetTargetStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}