// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
#include "GUI/BBHUDStub.h"
#include "GUI/Controllers/BBDossierController.h"
#include "GUI/Data/BBDossierEntryStub.h"
#include "GUI/Factories/BBWidgetFactoryStub.h"
#include "GUI/Models/BBDossierModelStub.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
#include "GUI/Widgets/BBDossierWidgetStub.h"
#include "GUI/Widgets/BBTitleWidgetStub.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "Specifications/Factories/BBSpecificationFactoryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBDossierControllerSpec, "SaltLakeCity.GUI.Controllers.Dossier", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD = nullptr;

	UPROPERTY()
	UBBDossierModelStub * Model = nullptr;

	UPROPERTY()
	UBBDossierWidgetStub * View = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBCloseWidgetCommandStub * CloseCommand = nullptr;

	UPROPERTY()
	UBBSpecificationFactoryStub * SpecificationFactory = nullptr;

	UPROPERTY()
	UBBWidgetFactoryStub * WidgetFactory = nullptr;

	UPROPERTY()
	UBBTitleWidgetStub * TitleWidget = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	UPROPERTY()
	TArray<float> Progresses;

	// SUT
	UPROPERTY()
	UBBDossierController * Controller = nullptr;

	FActorSpawnParameters SpawnParameters;

	void TestAttribute(EBBAttribute Attribute, UBBDossierWidgetStub * DossierView, UBBDossierEntryStub * DossierEntry)
	{
		TEST_TRUE(DossierView->GetAttributeEntry(0) == DossierEntry)
	}

	void TestNeed(EBBNeed Need, UBBDossierWidgetStub * DossierView, UBBDossierEntryStub * DossierEntry)
	{
		TEST_TRUE(DossierView->GetAttributeEntry(0) == DossierEntry)
	}

	void TestSkill(EBBSkill Skill, UBBDossierWidgetStub * DossierView, UBBDossierEntryStub * DossierEntry)
	{
		TEST_TRUE(DossierView->GetAttributeEntry(0) == DossierEntry)
	}

END_DEFINE_SPEC(UBBDossierControllerSpec)

void UBBDossierControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDossierController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	struct FBBAttributeUpdate
	{
		public:
			FBBAttributeUpdate(float NewBase, float NewCurrent) :
				Base(NewBase),
				Current(NewCurrent)
			{ }

			~FBBAttributeUpdate()
			{ }

			float Base;

			float Current;
	};

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		HUD = TestWorld->SpawnActor<ABBHUDStub>(ABBHUDStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		Model = NewObject<UBBDossierModelStub>(TestWorld, UBBDossierModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		View = CreateWidget<UBBDossierWidgetStub>(TestWorld, UBBDossierWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		CloseCommand = NewObject<UBBCloseWidgetCommandStub>(CommandFactory, UBBCloseWidgetCommandStub::StaticClass());

		UTEST_TRUE("Close Command is valid", IsValid(CloseCommand))

		CommandFactory->AddCloseWidgetCommand(CloseCommand);

		SpecificationFactory = NewObject<UBBSpecificationFactoryStub>(TestWorld, UBBSpecificationFactoryStub::StaticClass());

		UTEST_TRUE("Specification Factory is valid", IsValid(SpecificationFactory))

		WidgetFactory = NewObject<UBBWidgetFactoryStub>(HUD, UBBWidgetFactoryStub::StaticClass());

		UTEST_TRUE("Widget Factory is valid", IsValid(WidgetFactory))

		TitleWidget = NewObject<UBBTitleWidgetStub>(WidgetFactory, UBBTitleWidgetStub::StaticClass());

		UTEST_TRUE("Title Widget is valid", IsValid(TitleWidget))

		WidgetFactory->AddWidget(TitleWidget);

		HUD->SetWidgetFactory(WidgetFactory);

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;

		CloseCommand = nullptr;
		CommandFactory = nullptr;

		SpecificationFactory = nullptr;

		TitleWidget = nullptr;
		WidgetFactory = nullptr;

		TestWorld->DestroyActor(HUD);

		Controller = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It("Given a new view, expect the controller to initialize the view's title", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetTitle() == TitleWidget)

				Controller->Finalize();

				return true;
			});
			
			It("Given a new view, expect the controller to initialize the view's display name", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Model->SetDisplayName(FText::FromString("Generic Default, Bland"));

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetDisplayName().EqualTo(Model->GetDisplayName()))

				Controller->Finalize();

				return true;
			});

			It("Given a new view, expect the controller to set the view's commands", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				// TEST HERE

				Controller->Finalize();

				return true;
			});
			
			It("Given a new view, expect the controller to initialize the view's attribute entries", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Model->SetDisplayName(FText::FromString("Generic Default, Bland"));

				TMap<EBBAttribute, UBBDossierEntryStub *> Entries;
				Entries.Emplace(EBBAttribute::Health, NewObject<UBBDossierEntryStub>(Model, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBAttribute::Stamina, NewObject<UBBDossierEntryStub>(Model, UBBDossierEntryStub::StaticClass()));

				UTEST_TRUE("Health Entry is valid", IsValid(Entries.FindChecked(EBBAttribute::Health)))
				UTEST_TRUE("Stamina Entry is valid", IsValid(Entries.FindChecked(EBBAttribute::Stamina)))

				Model->SetEntry(EBBAttribute::Health, Entries.FindChecked(EBBAttribute::Health));
				Model->SetEntry(EBBAttribute::Stamina, Entries.FindChecked(EBBAttribute::Stamina));

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				#define EBBATTRIBUTE_OPERATION(Value) TestEntry<EBBAttribute, UIBBAttributeSet, UIBBDossierEntry>(Value, Model, NeedSet);

					FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

				#undef EBBATTRIBUTE_OPERATION

				TEST_TRUE(View->GetAttributeEntry(0) == Entries.FindChecked(EBBAttribute::Health))
				TEST_TRUE(View->GetAttributeEntry(1) == Entries.FindChecked(EBBAttribute::Stamina))

				Controller->Finalize();

				return true;
			});

			It("Given a new view, expect the controller to set the view's title", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetTitle() == TitleWidget)

				Controller->Finalize();

				return true;
			});
		});
	}
}