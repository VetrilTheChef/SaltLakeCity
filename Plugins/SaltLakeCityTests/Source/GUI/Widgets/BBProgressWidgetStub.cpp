// SaltLakeCity 5.7

#include "BBProgressWidgetStub.h"
#include "Components/ProgressBar.h"

UBBProgressWidgetStub::UBBProgressWidgetStub(const FObjectInitializer& ObjectInitializer) :
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

void UBBProgressWidgetStub::AddToScreen(int32 ZOrder)
{
}

float UBBProgressWidgetStub::GetProgress()
{
	return Progress;
}

void UBBProgressWidgetStub::SetProgress(float NewPercent)
{
	Progress = NewPercent;
}