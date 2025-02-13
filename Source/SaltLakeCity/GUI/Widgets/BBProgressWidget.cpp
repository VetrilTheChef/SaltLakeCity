// SaltLakeCity 4.24

#include "BBProgressWidget.h"
#include "Components/ProgressBar.h"

UBBProgressWidget::UBBProgressWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
}

EBBWidget UBBProgressWidget::GetType() const
{
	return EBBWidget::Progress;
}

void UBBProgressWidget::SetProgress(float NewPercent)
{
	verifyf(IsValid(ProgressBar), TEXT("Progress Bar is invalid."));
	
	ProgressBar->SetPercent(NewPercent);
}