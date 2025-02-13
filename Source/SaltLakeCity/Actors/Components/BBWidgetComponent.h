// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "BBWidgetComponent.generated.h"

class AIBBHUD;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class SALTLAKECITY_API UBBWidgetComponent : public UIBBWidgetComponent
{
	GENERATED_BODY()

	public:	
		UBBWidgetComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void SetWidget(UUserWidget * NewWidget) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Widget Colors")
		FLinearColor SelectedColor;

		UPROPERTY(EditDefaultsOnly, Category = "Widget Colors")
		FLinearColor DeselectedColor;

		UFUNCTION()
		void SelectWidget(UIBBWidgetComponent * SelectedWidgetComponent);
};