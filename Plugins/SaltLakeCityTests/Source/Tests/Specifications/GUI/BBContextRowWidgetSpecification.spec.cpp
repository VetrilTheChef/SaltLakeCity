// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Specifications/GUI/BBContextRowWidgetSpecification.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBContextRowWidgetSpecificationSpec, "SaltLakeCity.Specifications.GUI.ContextRowWidgetSpecification", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> WidgetSpecificationClasses;

	// SUT
	UPROPERTY()
	UBBContextRowWidgetSpecification * WidgetSpecification = nullptr;

END_DEFINE_SPEC(UBBContextRowWidgetSpecificationSpec)

void UBBContextRowWidgetSpecificationSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBContextRowWidgetSpecification>(FString(TEXT("/Game/Specifications/GUI")), WidgetSpecificationClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		return true;
	});

	AfterEach([this]()
	{
		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & WidgetSpecificationClass : WidgetSpecificationClasses)
	{
		Describe("[" + WidgetSpecificationClass->GetName() + "]", [this, WidgetSpecificationClass]()
		{
			It("Given , expect .", [this, WidgetSpecificationClass]()
			{
				WidgetSpecification = NewObject<UBBContextRowWidgetSpecification>(TestWorld, WidgetSpecificationClass);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				return true;
			});
		});
	}
}