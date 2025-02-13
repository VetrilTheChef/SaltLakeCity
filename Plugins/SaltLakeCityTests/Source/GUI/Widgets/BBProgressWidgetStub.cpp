// SaltLakeCity 4.24

#include "BBProgressWidgetStub.h"
#include "Components/ProgressBar.h"

UBBProgressWidgetStub::UBBProgressWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Progress = 0.0f;
}

void UBBProgressWidgetStub::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBProgressWidgetStub::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBBProgressWidgetStub::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

EBBWidget UBBProgressWidgetStub::GetType() const
{
	return EBBWidget::Progress;
}

float UBBProgressWidgetStub::GetProgress()
{
	return Progress;
}

void UBBProgressWidgetStub::SetProgress(float NewPercent)
{
	Progress = NewPercent;
}