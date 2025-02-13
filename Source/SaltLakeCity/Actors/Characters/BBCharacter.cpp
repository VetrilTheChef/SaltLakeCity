// SaltLakeCity 4.27

#include "BBCharacter.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Components/Interfaces/IBBContextComponent.h"
#include "Actors/Components/Interfaces/IBBDecalComponent.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Attributes/Interfaces/IBBAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Controllers/Interfaces/IBBAIController.h"
#include "Engine/World.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GameStates/Interfaces/IBBGameState.h"

ABBCharacter::ABBCharacter() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;

	JumpMaxCount = 0;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = nullptr;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	InitializeCapsuleComponent();
	InitializeSkeletalMeshComponent();

	SetActorEnableCollision(true);

	FirstName = FText::FromString("");
	CodeName = FText::FromString("");
	LastName = FText::FromString("");

	AbilityComponent = nullptr;
	ContextComponent = nullptr;
	DecalComponent = nullptr;
	SelectionComponent = nullptr;
	WorkComponent = nullptr;

	ContextOptions.Empty();

	FocusedCallbacks.Empty();
	UnfocusedCallbacks.Empty();
}

void ABBCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeEventCallbacks();
	InitializeNameFormats();

	UIBBGameInstance * GameInstance = GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	const UIBBComponentFactory * ComponentFactory = GameInstance->GetComponentFactory();

	verifyf(IsValid(ComponentFactory), TEXT("Component Factory is invalid."));

	CreateAbilityComponent(* ComponentFactory);
	CreateContextComponent(* ComponentFactory);
	CreateDecalComponent(*ComponentFactory);
	CreateSelectionComponent(* ComponentFactory);
	CreateWorkComponent(* ComponentFactory);

	OnClicked.AddDynamic(this, & ABBCharacter::OnClick);
}

void ABBCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnClicked.RemoveDynamic(this, & ABBCharacter::OnClick);

	DestroyWorkComponent();
	DestroySelectionComponent();
	DestroyDecalComponent();
	DestroyContextComponent();
	DestroyAbilityComponent();

	FinalizeNameFormats();
	FinalizeEventCallbacks();

	Super::EndPlay(EndPlayReason);
}

void ABBCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(AbilityComponent))
	{
		AbilityComponent->SetAIController(GetController<AIBBAIController>());
	}
}

void ABBCharacter::UnPossessed()
{
	Super::UnPossessed();
}

UAbilitySystemComponent * ABBCharacter::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

void ABBCharacter::UpdateContext(bool Contextualized)
{
	OnContextUpdate().Broadcast(Contextualized);
}

bool ABBCharacter::IsContextOption(EBBContext ContextOption) const
{
	return ContextOptions.Contains(ContextOption);
}

UIBBContextComponent * ABBCharacter::GetContextComponent() const
{
	return ContextComponent;
}

void ABBCharacter::UpdateHighlight(bool Highlighted)
{
	OnHighlightUpdate().Broadcast(Highlighted);
}

UIBBDecalComponent * ABBCharacter::GetDecalComponent() const
{
	return DecalComponent;
}

void ABBCharacter::UpdateSelection(bool Selected)
{
	OnSelectionUpdate().Broadcast(Selected);

	UpdateHighlight(Selected);

	verifyf(IsValid(SelectionComponent), TEXT("Selection Component is invalid."));

	SelectionComponent->SetVisibility(Selected);
}

UIBBSelectionComponent * ABBCharacter::GetSelectionComponent() const
{
	return SelectionComponent;
}

UIBBWorkComponent * ABBCharacter::GetWorkComponent() const
{
	return WorkComponent;
}

FText ABBCharacter::GetDisplayName(EBBDisplayName Mode) const
{
	return (this->* NameFormats.FindChecked(Mode))();
}

void ABBCharacter::SetFirstName(FText NewFirstName)
{
	FirstName = NewFirstName;

	OnWidgetTargetUpdate().Broadcast();
}

void ABBCharacter::SetCodeName(FText NewCodeName)
{
	CodeName = NewCodeName;

	OnWidgetTargetUpdate().Broadcast();
}

void ABBCharacter::SetLastName(FText NewLastName)
{
	LastName = NewLastName;

	OnWidgetTargetUpdate().Broadcast();
}

AActor * ABBCharacter::ToActor()
{
	return this;
}

TScriptInterface<IBBWidgetTarget> ABBCharacter::ToWidgetTarget()
{
	return TScriptInterface<IBBWidgetTarget>(this);
}



void ABBCharacter::InitializeCapsuleComponent()
{
	UCapsuleComponent * Capsule = GetCapsuleComponent();

	verifyf(IsValid(Capsule), TEXT("Capsule Component is invalid."));
	
	//Capsule->SetMobility(EComponentMobility::Movable);
	//Capsule->InitCapsuleSize(1.0, 0.5);
	Capsule->SetCollisionProfileName(TEXT("Pawn"));
	Capsule->SetCollisionResponseToAllChannels(ECR_Block);
	Capsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->SetCollisionObjectType(ECC_Pawn);
}

void ABBCharacter::InitializeSkeletalMeshComponent()
{
	USkeletalMeshComponent * CharacterMesh = GetMesh();

	verifyf(IsValid(CharacterMesh), TEXT("Skeletal Mesh Component is invalid."));
	
	CharacterMesh->bDisableClothSimulation = true;
	CharacterMesh->SetEnableGravity(false);
}

void ABBCharacter::InitializeEventCallbacks()
{
	FocusedCallbacks.Empty();

	TArray<TPair<EventCallback, bool>> & LMBCallbacks = FocusedCallbacks.FindOrAdd(EKeys::LeftMouseButton);

	LMBCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateSelection, true));
	LMBCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateHighlight, true));

	TArray<TPair<EventCallback, bool>> & RMBCallbacks = FocusedCallbacks.FindOrAdd(EKeys::RightMouseButton);

	RMBCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateSelection, true));
	RMBCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateHighlight, true));
	RMBCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateContext, true));;

	UnfocusedCallbacks.Empty();

	UnfocusedCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateSelection, false));
	UnfocusedCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateHighlight, false));
	UnfocusedCallbacks.Emplace(TPair<EventCallback, bool>(& ABBCharacter::UpdateContext, false));
}

void ABBCharacter::InitializeNameFormats()
{
	NameFormats.Empty();

	NameFormats.Emplace(EBBDisplayName::Short, & ABBCharacter::GetShortName);
	NameFormats.Emplace(EBBDisplayName::Long, &ABBCharacter::GetLongName);
	NameFormats.Emplace(EBBDisplayName::Code, &ABBCharacter::GetCodeName);
	NameFormats.Emplace(EBBDisplayName::Full, &ABBCharacter::GetFullName);
}

void ABBCharacter::FinalizeEventCallbacks()
{
	FocusedCallbacks.Empty();
	UnfocusedCallbacks.Empty();
}

void ABBCharacter::FinalizeNameFormats()
{
	NameFormats.Empty();
}

void ABBCharacter::CreateAbilityComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroyAbilityComponent();

	ComponentFactory.NewAIAbilityComponent(AbilityComponent, GetController<AIBBAIController>());
}

void ABBCharacter::CreateContextComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroyContextComponent();

	ComponentFactory.NewContextComponent(ContextComponent, this);
}

void ABBCharacter::CreateDecalComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroyDecalComponent();

	if (ComponentFactory.NewDecalComponent(DecalComponent, this))
	{
		DecalComponent->AddRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
		UCapsuleComponent * Capsule = GetCapsuleComponent();

		verifyf(IsValid(Capsule), TEXT("Capsule Component is invalid."));

		float HalfHeight = 0.0f;
		float Radius = 0.0f;

		Capsule->GetScaledCapsuleSize(Radius, HalfHeight);

		DecalComponent->DecalSize = FVector(2.0 * HalfHeight, 2.0 * Radius, 2.0 * Radius);
	}
}

void ABBCharacter::CreateSelectionComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroySelectionComponent();

	ComponentFactory.NewSelectionComponent(SelectionComponent, TScriptInterface<IBBSelectable>(this));
}

void ABBCharacter::CreateWorkComponent(const UIBBComponentFactory & ComponentFactory)
{
	DestroyWorkComponent();

	ComponentFactory.NewWorkComponent(WorkComponent, TScriptInterface<IBBWorkable>(this), AbilityComponent, EBBJob::None);
}

void ABBCharacter::DestroyAbilityComponent()
{
	if (IsValid(AbilityComponent))
	{
		AbilityComponent->Finalize();

		AbilityComponent->DestroyComponent();
	}

	AbilityComponent = nullptr;
}

void ABBCharacter::DestroyContextComponent()
{
	if (IsValid(ContextComponent))
	{
		ContextComponent->Finalize();

		ContextComponent->DestroyComponent();
	}

	ContextComponent = nullptr;
}

void ABBCharacter::DestroyDecalComponent()
{
	if (IsValid(DecalComponent))
	{
		DecalComponent->Finalize();

		DecalComponent->DestroyComponent();
	}

	DecalComponent = nullptr;
}

void ABBCharacter::DestroySelectionComponent()
{
	if (IsValid(SelectionComponent))
	{
		SelectionComponent->Finalize();

		SelectionComponent->DestroyComponent();
	}

	SelectionComponent = nullptr;
}

void ABBCharacter::DestroyWorkComponent()
{
	if (IsValid(WorkComponent))
	{
		WorkComponent->Finalize();

		WorkComponent->DestroyComponent();
	}

	WorkComponent = nullptr;
}

FText ABBCharacter::GetShortName() const
{
	return FirstName.IsEmptyOrWhitespace() ? FText::FromString("") : FirstName;
}

FText ABBCharacter::GetLongName() const
{
	FString FirstString = GetShortName().ToString();
	FString LastString = LastName.IsEmptyOrWhitespace() ? FString("") : LastName.ToString();
	FString Separator = FirstString.IsEmpty() || LastString.IsEmpty() ? FString("") : FString(" ");

	return FText::FromString(FirstString + Separator + LastString);
}

FText ABBCharacter::GetCodeName() const
{
	if (CodeName.IsEmptyOrWhitespace())
	{
		if (FirstName.IsEmptyOrWhitespace())
		{
			if (LastName.IsEmptyOrWhitespace())
			{
				return FText::FromString("");
			}

			return LastName;
		}

		return FirstName;
	}

	return CodeName;
}

FText ABBCharacter::GetFullName() const
{
	FString FirstString = GetShortName().ToString();
	FString CodeString = CodeName.IsEmptyOrWhitespace() ? FString("") : CodeName.ToString();
	FString LastString = LastName.IsEmptyOrWhitespace() ? FString("") : LastName.ToString();
	FString FirstSeparator;
	FString LastSeparator;
	
	if (CodeString.IsEmpty())
	{
		FirstSeparator = FirstString.IsEmpty() ? FString("") : FString(" ");
		LastSeparator = FString("");
	}
	else
	{
		FirstSeparator = FirstString.IsEmpty() ? FString("\"") : FString(" \"");
		LastSeparator = LastString.IsEmpty() ? FString("\"") : FString("\" ");
	}

	return FText::FromString(FirstString + FirstSeparator + CodeString + LastSeparator + LastString);
}

void ABBCharacter::OnClick(AActor * TouchedActor, FKey ButtonPressed)
{
	if (TouchedActor == this)
	{
		TArray<TPair<EventCallback, bool>> * CallbackPairs = FocusedCallbacks.Find(ButtonPressed);

		if (CallbackPairs)
		{
			for (TPair<EventCallback, bool> & CallbackPair : * CallbackPairs)
			{
				(this->* CallbackPair.Key)(CallbackPair.Value);
			}
		}
	}
	else
	{
		for (TPair<EventCallback, bool> & CallbackPair : UnfocusedCallbacks)
		{
			(this->* CallbackPair.Key)(CallbackPair.Value);
		}
	}
}