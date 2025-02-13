// SaltLakeCity 4.27

#include "BBWidgetComponent.h"
#include "GUI/Interfaces/IBBHUD.h"

UBBWidgetComponent::UBBWidgetComponent() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetDrawAtDesiredSize(false);
	SetRedrawTime(0.1f);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetWindowFocusable(false);

	SelectedColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	DeselectedColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.33f);
}

void UBBWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	SetWindowVisibility(EWindowVisibility::SelfHitTestInvisible);
}

void UBBWidgetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBWidgetComponent::SetWidget(UUserWidget * NewWidget)
{
	verifyf(IsValid(NewWidget), TEXT("Widget is invalid."));
	
	SetDrawSize(NewWidget->GetDesiredSize());

	Super::SetWidget(NewWidget);
}



void UBBWidgetComponent::SelectWidget(UIBBWidgetComponent * SelectedWidgetComponent)
{
	if (SelectedWidgetComponent == this)
	{
		SetTintColorAndOpacity(SelectedColor);
	}
	else
	{
		SetTintColorAndOpacity(DeselectedColor);
	}
}