// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IBBRadioSet.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(Abstract, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UIBBRadioSet : public UUserWidget
{
	GENERATED_BODY()
	
	public:
		UIBBRadioSet(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeConstruct() override { Super::NativeConstruct(); };
		
		virtual void NativeDestruct() override { Super::NativeDestruct(); };

		virtual void AddElement(UIBBCommand * NewElementCommand) PURE_VIRTUAL(UIBBRadioSet::AddElement, );

		virtual void ClearElements() PURE_VIRTUAL(UIBBRadioSet::ClearElements, );

		virtual int GetNumElements() PURE_VIRTUAL(UIBBRadioSet::GetNumElements, return -1; );
};