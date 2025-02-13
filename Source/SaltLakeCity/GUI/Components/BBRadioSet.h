// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Components/Interfaces/IBBRadioSet.h"
#include "BBRadioSet.generated.h"

/**
 * 
 */

class UCheckBox;

USTRUCT(BlueprintType)
struct FBBRadioSetElement
{
	GENERATED_BODY()

	public:
		UPROPERTY()
		UCheckBox * CheckBox = nullptr;

		UPROPERTY()
		UIBBCommand * Command = nullptr;

		FBBRadioSetElement() :
			CheckBox(nullptr),
			Command(nullptr)
		{
		}

		FBBRadioSetElement(UCheckBox * NewCheckBox, UIBBCommand * NewCommand) :
			CheckBox(NewCheckBox),
			Command(NewCommand)
		{
		}

		~FBBRadioSetElement()
		{
			CheckBox = nullptr;
			Command = nullptr;
		}
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBRadioSet : public UIBBRadioSet
{
	GENERATED_BODY()
	
	public:
		UBBRadioSet(const FObjectInitializer & ObjectInitializer);

		virtual void NativeConstruct() override;
		
		virtual void NativeDestruct() override;

		virtual void AddElement(UIBBCommand * NewElementCommand) override;

		virtual void ClearElements() override;

		virtual int GetNumElements() override;

	protected:
		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UCheckBox> ElementClass;

		UPROPERTY()
		TArray<FBBRadioSetElement> Elements;

		UFUNCTION()
		void ChangeElementState(bool bIsChecked);
};