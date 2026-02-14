// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IBBGameInstance.generated.h"

/**
*
*/

class AIBBGameMode;
class AIBBGameState;
class AIBBHUD;
class AIBBPlayerController;
class UIBBCommandFactory;
class UIBBComponentFactory;
class UIBBSpecificationFactory;
class UIBBWidgetManager;
class UWorld;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:
		UIBBGameInstance() : Super() { };

		virtual void Init() override { Super::Init(); };

		virtual void Shutdown() override { Super::Shutdown(); };

		virtual void Initialize(
			UWorld* NewWorld,
			AIBBGameMode* NewGameMode,
			AIBBGameState* NewGameState,
			AIBBHUD* NewHUD,
			AIBBPlayerController* NewPlayerController
		) PURE_VIRTUAL(UIBBGameInstance::Initialize, );

		virtual void Finalize(UWorld* OldWorld)
			PURE_VIRTUAL(UIBBGameInstance::Finalize, );

		virtual AIBBGameMode* GetGameMode() const
			PURE_VIRTUAL(UIBBGameInstance::GetGameMode, return nullptr; );

		virtual AIBBGameState* GetGameState() const
			PURE_VIRTUAL(UIBBGameInstance::GetGameState, return nullptr; );

		virtual AIBBHUD* GetHUD() const
			PURE_VIRTUAL(UIBBGameInstance::GetHUD, return nullptr; );

		virtual AIBBPlayerController* GetPlayerController() const
			PURE_VIRTUAL(UIBBGameInstance::GetPlayerController, return nullptr; );

		virtual UIBBWidgetManager* GetWidgetManager() const
			PURE_VIRTUAL(UIBBGameInstance::GetWidgetManager, return nullptr; );

		virtual const UIBBCommandFactory* GetCommandFactory() const
			PURE_VIRTUAL(UIBBGameInstance::GetCommandFactory, return nullptr; );

		virtual const UIBBComponentFactory* GetComponentFactory() const
			PURE_VIRTUAL(UIBBGameInstance::GetComponentFactory, return nullptr; );

		virtual const UIBBSpecificationFactory* GetSpecificationFactory() const
			PURE_VIRTUAL(UIBBGameInstance::GetSpecificationFactory, return nullptr; );
};

Expose_TNameOf(UIBBGameInstance);