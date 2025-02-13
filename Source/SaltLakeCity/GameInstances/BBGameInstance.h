// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "BBGameInstance.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBGameInstance : public UIBBGameInstance
{
	GENERATED_BODY()

	public:
		UBBGameInstance();

		virtual void Init() override;

		virtual void Shutdown() override;

		virtual void Initialize(UWorld * NewWorld, AIBBGameMode * NewGameMode, AIBBGameState * NewGameState, AIBBHUD * NewHUD, AIBBPlayerController * NewPlayerController);

		virtual void Finalize(UWorld * OldWorld) override;

		virtual AIBBGameMode * GetGameMode() const override;

		virtual AIBBGameState * GetGameState() const override;

		virtual AIBBHUD * GetHUD() const override;

		virtual AIBBPlayerController * GetPlayerController() const override;
		
		virtual const UIBBCommandFactory * GetCommandFactory() const override;

		virtual const UIBBComponentFactory * GetComponentFactory() const override;

		virtual const UIBBSpecificationFactory * GetSpecificationFactory() const override;

	protected:
		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBCommandFactory> CommandFactoryClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBComponentFactory> ComponentFactoryClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBSpecificationFactory> SpecificationFactoryClass;

		UPROPERTY()
		AIBBGameMode * GameMode;

		UPROPERTY()
		AIBBGameState * GameState;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		AIBBPlayerController * PlayerController;

		UPROPERTY()
		UIBBCommandFactory * CommandFactory;

		UPROPERTY()
		UIBBComponentFactory * ComponentFactory;

		UPROPERTY()
		UIBBSpecificationFactory * SpecificationFactory;

		void CreateInstances();

		void DestroyInstances();

		void CreateCommandFactory();

		void CreateComponentFactory();

		void CreateSpecificationFactory();

		void DestroyCommandFactory();

		void DestroyComponentFactory();

		void DestroySpecificationFactory();
};