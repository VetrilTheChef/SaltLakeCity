// SaltLakeCity 5.7

#include "BBWidgetManagerStub.h"

UBBWidgetManagerStub::UBBWidgetManagerStub() :
	Super()
{
	WidgetFactory = nullptr;
	WidgetSpecificationFactory = nullptr;
	ModelPool = nullptr;

	Widget = nullptr;
}

void UBBWidgetManagerStub::Initialize(
	const UIBBGameInstance* GameInstance,
	const AIBBGameState* GameState,
	AIBBGameMode* GameMode,
	AIBBHUD* NewHUD,
	APlayerController* PlayerController
)
{
}

void UBBWidgetManagerStub::Finalize()
{
}

const UIBBWidgetFactory * UBBWidgetManagerStub::GetWidgetFactory() const
{
	return WidgetFactory;
}

void UBBWidgetManagerStub::SetWidgetFactory(UIBBWidgetFactory * NewWidgetFactory)
{
	WidgetFactory = NewWidgetFactory;
}

const UIBBWidgetSpecificationFactory * UBBWidgetManagerStub::GetWidgetSpecificationFactory() const
{
	return WidgetSpecificationFactory;
}

void UBBWidgetManagerStub::SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory)
{
	WidgetSpecificationFactory = NewWidgetSpecificationFactory;
}

UIBBModelPool* UBBWidgetManagerStub::GetModelPool() const
{
	return ModelPool;
}

void UBBWidgetManagerStub::SetModelPool(UIBBModelPool* NewModelPool)
{
	ModelPool = NewModelPool;
}

UIBBWidget* UBBWidgetManagerStub::GetWidget(UIBBWidgetSpecification* Specification)
{
	return Widget;
}

void UBBWidgetManagerStub::SetWidget(UIBBWidget* NewWidget)
{
	Widget = NewWidget;
}
