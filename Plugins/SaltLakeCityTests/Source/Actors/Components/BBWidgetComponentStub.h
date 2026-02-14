// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "BBWidgetComponentStub.generated.h"

class AIBBHUD;

UCLASS(NotBlueprintable)

class UBBWidgetComponentStub : public UIBBWidgetComponent
{
	GENERATED_BODY()

	public:	
		UBBWidgetComponentStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void SetWidget(UUserWidget* NewWidget) override;
};