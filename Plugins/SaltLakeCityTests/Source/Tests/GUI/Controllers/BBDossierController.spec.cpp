// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
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

BEGIN_DEFINE_SPEC(
	UBBDossierControllerSpec,
	"SaltLakeCity.GUI.Controllers.Dossier",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld* TestWorld = nullptr;

	UPROPERTY()
	UBBDossierModelStub* Model = nullptr;

	UPROPERTY()
	UBBDossierWidgetStub* View = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub* CommandFactory = nullptr;

	UPROPERTY()
	UBBCloseWidgetCommandStub* CloseCommand = nullptr;

	UPROPERTY()
	UBBSpecificationFactoryStub* SpecificationFactory = nullptr;

	UPROPERTY()
	UBBWidgetFactoryStub* WidgetFactory = nullptr;

	UPROPERTY()
	UBBTitleWidgetStub* TitleWidget = nullptr;

	UPROPERTY()
	TArray<UClass*> ControllerClasses;

	TArray<float> Progresses;

	// SUT
	UPROPERTY()
	UBBDossierController* Controller = nullptr;

	FActorSpawnParameters SpawnParameters;

	template<typename E>
	bool InitializeEntry(E Enum, TMap<E, UBBDossierEntryStub*>& Entries, UObject* Outer)
	{
		UBBDossierEntryStub* NewEntry = NewObject<UBBDossierEntryStub>(Model, UBBDossierEntryStub::StaticClass());

		UTEST_TRUE("New Entry is valid", IsValid(NewEntry))

		Entries.Emplace(Enum, NewEntry);

		Model->SetDossierEntry(Enum, Entries.FindChecked(Enum));

		return true;
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

		Model = NewObject<UBBDossierModelStub>(
			TestWorld,
			UBBDossierModelStub::StaticClass()
		);

		UTEST_TRUE("Model is valid", IsValid(Model))

		View = CreateWidget<UBBDossierWidgetStub>(
			TestWorld,
			UBBDossierWidgetStub::StaticClass()
		);

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		CommandFactory = NewObject<UBBCommandFactoryStub>(
			TestWorld,
			UBBCommandFactoryStub::StaticClass()
		);

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		CloseCommand = NewObject<UBBCloseWidgetCommandStub>(
			CommandFactory,
			UBBCloseWidgetCommandStub::StaticClass()
		);

		UTEST_TRUE("Close Command is valid", IsValid(CloseCommand))

		CommandFactory->AddCloseWidgetCommand(CloseCommand);

		SpecificationFactory = NewObject<UBBSpecificationFactoryStub>(
			TestWorld,
			UBBSpecificationFactoryStub::StaticClass()
		);

		UTEST_TRUE("Specification Factory is valid", IsValid(SpecificationFactory))

		WidgetFactory = NewObject<UBBWidgetFactoryStub>(
			TestWorld,
			UBBWidgetFactoryStub::StaticClass()
		);

		UTEST_TRUE("Widget Factory is valid", IsValid(WidgetFactory))

		TitleWidget = NewObject<UBBTitleWidgetStub>(
			WidgetFactory,
			UBBTitleWidgetStub::StaticClass()
		);

		UTEST_TRUE("Title Widget is valid", IsValid(TitleWidget))

		WidgetFactory->AddWidget(TitleWidget);

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

		Controller = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass*& ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It(
				"Given a new view, expect the controller to initialize the view's title",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetTitle() == TitleWidget)

				Controller->Finalize();

				return true;
			});
			
			It(
				"Given a new view, expect the controller to initialize the view's display name",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Model->SetDisplayName(FText::FromString("Generic Default, Bland"));

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetDisplayName().EqualTo(Model->GetDisplayName()))

				Controller->Finalize();

				return true;
			});

			It(
				"Given a new view, expect the controller to set the view's commands",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				// TEST HERE

				Controller->Finalize();

				return true;
			});
			
			It(
				"Given a new view, expect the controller to initialize the view's attribute entries",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Model->SetDisplayName(FText::FromString("Generic Default, Bland"));

				TMap<EBBAttribute, UBBDossierEntryStub *> Entries;

				#define EBBATTRIBUTE_OPERATION(Value) InitializeEntry(Value, Entries, Model);

					FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

				#undef EBBATTRIBUTE_OPERATION

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TArray<UIBBDossierEntry *> ViewEntries = View->GetAttributeEntries();

				TEST_TRUE(ViewEntries.Num() == Entries.Num())

				for (const TPair<EBBAttribute, UIBBDossierEntry *> & EntryPair : Entries)
				{
					if (ViewEntries.Contains(EntryPair.Value))
					{
						ViewEntries.Remove(EntryPair.Value);
					}
				}

				TEST_TRUE(ViewEntries.Num() == 0)

				Controller->Finalize();

				return true;
			});
			
			It(
				"Given a new view, expect the controller to initialize the view's need entries",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Model->SetDisplayName(FText::FromString("Generic Default, Bland"));

				TMap<EBBNeed, UBBDossierEntryStub *> Entries;

				#define EBBNEED_OPERATION(Value) InitializeEntry(Value, Entries, Model);

					FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

				#undef EBBNEED_OPERATION

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TArray<UIBBDossierEntry *> ViewEntries = View->GetNeedEntries();

				TEST_TRUE(ViewEntries.Num() == Entries.Num())

				for (const TPair<EBBNeed, UIBBDossierEntry *> & EntryPair : Entries)
				{
					if (ViewEntries.Contains(EntryPair.Value))
					{
						ViewEntries.Remove(EntryPair.Value);
					}
				}

				TEST_TRUE(ViewEntries.Num() == 0)

				Controller->Finalize();

				return true;
			});
			
			It(
				"Given a new view, expect the controller to initialize the view's skill entries",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBDossierController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Model->SetDisplayName(FText::FromString("Generic Default, Bland"));

				TMap<EBBSkill, UBBDossierEntryStub *> Entries;

				#define EBBSKILL_OPERATION(Value) InitializeEntry(Value, Entries, Model);

					FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

				#undef EBBSKILL_OPERATION

				Controller->Initialize(View, Model, WidgetFactory, SpecificationFactory, CommandFactory);

				TArray<UIBBDossierEntry *> ViewEntries = View->GetSkillEntries();

				TEST_TRUE(ViewEntries.Num() == Entries.Num())

				for (const TPair<EBBSkill, UIBBDossierEntry *> & EntryPair : Entries)
				{
					if (ViewEntries.Contains(EntryPair.Value))
					{
						ViewEntries.Remove(EntryPair.Value);
					}
				}

				TEST_TRUE(ViewEntries.Num() == 0)

				Controller->Finalize();

				return true;
			});

			It(
				"Given a new view, expect the controller to set the view's title",
				[this, ControllerClass]()
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