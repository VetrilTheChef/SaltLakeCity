// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/BBContextComponentStub.h"
#include "Actors/Components/BBProgressComponentStub.h"
#include "Actors/Components/BBSelectionComponentStub.h"
#include "Actors/Components/BBWidgetComponentStub.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameInstances/Subsystems/BBUINotificationSubsystemStub.h"
#include "GUI/BBHUD.h"
#include "GUI/BBWidgetManagerStub.h"
#include "GUI/Widgets/BBWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	ABBHUDSpec,
	"SaltLakeCity.GUI.HUD",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld* TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub* GameInstance = nullptr;

	UPROPERTY()
	UBBPresentationSubsystemStub* PresentationSubsystem = nullptr;

	UPROPERTY()
	UBBWidgetManagerStub* WidgetManager = nullptr;

	UPROPERTY()
	TArray<UClass*> HUDClasses;

	// SUT
	UPROPERTY()
	ABBHUD* HUD = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(ABBHUDSpec)

void ABBHUDSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBHUD>(FString(TEXT("/Game/GUI")), HUDClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		PresentationSubsystem = NewObject<UBBPresentationSubsystemStub>(
			GameInstance,
			UBBPresentationSubsystemStub::StaticClass()
		);

		UTEST_TRUE("Presentation Subsystem is valid", IsValid(PresentationSubsystem))

		WidgetManager = NewObject<UBBWidgetManagerStub>(
			GameInstance,
			UBBWidgetManagerStub::StaticClass()
		);

		UTEST_TRUE("Widget Manager is valid", IsValid(WidgetManager))

		return true;
	});

	AfterEach([this]()
	{
		WidgetManager = nullptr;
		PresentationSubsystem = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass*& HUDClass : HUDClasses)
	{
		Describe("[" + HUDClass->GetName() + "]", [this, HUDClass]()
		{
			It(
				"Given an open widget request, expect the HUD to open it",
				[this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(PresentationSubsystem, WidgetManager);

				UBBWidgetSpecificationStub* WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(
					TestWorld,
					UBBWidgetSpecificationStub::StaticClass()
				);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))
					
				for (int Index = 0; Index < 5; Index++)
				{
					UBBWidgetStub* Widget = NewObject<UBBWidgetStub>(
						WidgetManager,
						UBBWidgetStub::StaticClass()
					);

					UTEST_TRUE("Widget is valid", IsValid(Widget))

					WidgetManager->SetWidget(Widget);

					TEST_FALSE(Widget->IsInViewport())

					HUD->OpenWidget(WidgetSpecification, false);

					TEST_TRUE(Widget->IsInViewport())

					Widget->SetIsInViewport(false);
				}

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It(
				"Given a close widget request, expect the HUD to close it",
				[this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(PresentationSubsystem, WidgetManager);

				UBBWidgetSpecificationStub* WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(
					TestWorld,
					UBBWidgetSpecificationStub::StaticClass()
				);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				for (int Index = 0; Index < 5; Index++)
				{
					UBBWidgetStub* Widget = NewObject<UBBWidgetStub>(
						WidgetManager,
						UBBWidgetStub::StaticClass()
					);

					UTEST_TRUE("Widget is valid", IsValid(Widget))

					Widget->SetIsInViewport(true);

					WidgetManager->SetWidget(Widget);

					TEST_TRUE(Widget->IsInViewport())

					HUD->CloseWidget(WidgetSpecification);

					TEST_TRUE(Widget->IsInViewport() == false)
				}

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It(
				"Given an attach widget request, expect the HUD to attach it",
				[this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(PresentationSubsystem, WidgetManager);

				UBBWidgetSpecificationStub* WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(
					TestWorld,
					UBBWidgetSpecificationStub::StaticClass()
				);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				UBBWidgetComponentStub* WidgetComponent = NewObject<UBBWidgetComponentStub>(
					TestWorld,
					UBBWidgetComponentStub::StaticClass()
				);

				UTEST_TRUE("Widget Component is valid", IsValid(WidgetComponent))

				for (int Index = 0; Index < 5; Index++)
				{
					UBBWidgetStub* Widget = NewObject<UBBWidgetStub>(
						TestWorld,
						UBBWidgetStub::StaticClass()
					);

					TEST_TRUE(WidgetComponent->GetWidget() == nullptr)

					HUD->AttachWidget(WidgetSpecification, WidgetComponent);

					TEST_TRUE(WidgetComponent->GetWidget() == Widget)
				}

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It(
				"Given a detach widget request, expect the HUD to detach it",
				[this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(PresentationSubsystem, WidgetManager);

				UBBWidgetComponentStub* WidgetComponent = NewObject<UBBWidgetComponentStub>(
					TestWorld,
					UBBWidgetComponentStub::StaticClass()
				);

				UTEST_TRUE("Widget Component is valid", IsValid(WidgetComponent))

				for (int Index = 0; Index < 5; Index++)
				{
					UBBWidgetStub* Widget = NewObject<UBBWidgetStub>(
						TestWorld,
						UBBWidgetStub::StaticClass()
					);

					WidgetComponent->SetWidget(Widget);

					UTEST_TRUE("Widget is attached", WidgetComponent->GetWidget() == Widget)

					HUD->DetachWidget(WidgetComponent);

					TEST_TRUE(WidgetComponent->GetWidget() == nullptr)
				}

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It(
				"Given a new contextualizable, expect the HUD to broadcast its context component",
				[this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(PresentationSubsystem, WidgetManager);

				UBBContextModelStub* ContextModel = NewObject<UBBContextModelStub>(
					HUD,
					UBBContextModelStub::StaticClass()
				);

				UTEST_TRUE("Context Model is valid", IsValid(ContextModel))

				ContextModel->Initialize(nullptr, HUD, nullptr);

				UTEST_TRUE("Context Component is null", ContextModel->GetComponent() == nullptr)

				for (int Index = 0; Index < 5; Index++)
				{
					ABBCharacterStub* Character = TestWorld->SpawnActor<ABBCharacterStub>(
						ABBCharacterStub::StaticClass(),
						SpawnParameters
					);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UIBBContextComponent* ContextComponent = NewObject<UIBBContextComponent>(
						Character,
						UBBContextComponentStub::StaticClass()
					);

					UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))

					Character->SetContextComponent(ContextComponent);

					ContextComponent->Initialize(TScriptInterface<IBBContextualizable>(Character));

					GameState->SetContext(TScriptInterface<IBBContextualizable>(Character));

					TEST_TRUE(ContextModel->GetComponent() == ContextComponent)

					ContextComponent->Finalize();
					TestWorld->DestroyActor(Character);
				}

				ContextModel->Finalize();

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It(
				"Given a new selectable, expect the HUD to broadcast its selection component",
				[this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(PresentationSubsystem, WidgetManager);

				UBBSelectionModelStub * SelectionModel = NewObject<UBBSelectionModelStub>(
					HUD,
					UBBSelectionModelStub::StaticClass()
				);

				UTEST_TRUE("Selection Model is valid", IsValid(SelectionModel))

				SelectionModel->Initialize(nullptr, HUD);

				UTEST_TRUE("Selection Component is null", SelectionModel->GetComponent() == nullptr)

				for (int Index = 0; Index < 5; Index++)
				{
					ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(
						ABBCharacterStub::StaticClass(),
						SpawnParameters
					);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UIBBSelectionComponent * SelectionComponent = NewObject<UIBBSelectionComponent>(
						Character,
						UBBSelectionComponentStub::StaticClass()
					);

					UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

					Character->SetSelectionComponent(SelectionComponent);

					SelectionComponent->Initialize(TScriptInterface<IBBSelectable>(Character));

					GameState->SetSelection(TScriptInterface<IBBSelectable>(Character));

					TEST_TRUE(SelectionModel->GetComponent() == SelectionComponent)

					SelectionComponent->Finalize();
					TestWorld->DestroyActor(Character);
				}

				SelectionModel->Finalize();

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});
		});
	}
}