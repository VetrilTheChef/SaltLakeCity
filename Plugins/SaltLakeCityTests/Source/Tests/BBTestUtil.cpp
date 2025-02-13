// SaltLakeCity 4.27

#include "BBTestUtil.h"
#include "Editor/UnrealEdEngine.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/BBGameStateStub.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/BBLevelScriptActorStub.h"
#include "Tests/AutomationCommon.h"

UWorld * UBBTestUtil::GetEditorWorld()
{
	if (GEngine)
	{
		TIndirectArray<FWorldContext> WorldContexts = GEngine->GetWorldContexts();

		for (auto& WorldContext : WorldContexts)
		{
			if (WorldContext.WorldType == EWorldType::Editor)
			{
				return WorldContext.World();
			}
		}
	}

	return nullptr;
}

UWorld * UBBTestUtil::GetPIEWorld()
{
	if (GEngine)
	{
		FWorldContext * WorldContext = GEngine->GetWorldContextFromPIEInstance(0);

		if (WorldContext)
		{
			return WorldContext->World();
		}
	}

	return nullptr;
}

UWorld * UBBTestUtil::OpenTestWorld()
{
	if (AutomationOpenMap(TEST_MAP))
	{
		if (GEngine)
		{
			TIndirectArray<FWorldContext> WorldContexts = GEngine->GetWorldContexts();

			for (auto& WorldContext : WorldContexts)
			{
				if ((WorldContext.WorldType == EWorldType::PIE) || (WorldContext.WorldType == EWorldType::Game))
				{
					UWorld * TestWorld = WorldContext.World();

					UGameInstance * OldGameInstance = TestWorld->GetGameInstance();
					UUnrealEdEngine * Engine = Cast<UUnrealEdEngine>(OldGameInstance->GetOuter());

					UBBGameInstanceStub * NewGameInstance = NewObject<UBBGameInstanceStub>(TestWorld, UBBGameInstanceStub::StaticClass());

					NewGameInstance->Clone(OldGameInstance);
					TestWorld->SetGameInstance(NewGameInstance);

					AGameStateBase * OldGameState = TestWorld->GetGameState();
					ABBGameStateStub * NewGameState = TestWorld->SpawnActor<ABBGameStateStub>(ABBGameStateStub::StaticClass());

					TestWorld->SetGameState(NewGameState);

					return TestWorld;
				}
			}
		}
	}

	return nullptr;
}

void UBBTestUtil::CloseTestWorld(UWorld * TestWorld)
{
	if (IsValid(TestWorld))
	{
		if (GEngine)
		{
			TIndirectArray<FWorldContext> WorldContexts = GEngine->GetWorldContexts();

			for (auto& WorldContext : WorldContexts)
			{
				if ((WorldContext.World() == TestWorld))
				{
					UBBGameInstanceStub * NewGameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();
					UGameInstance * OldGameInstance = WorldContext.OwningGameInstance;

					NewGameInstance->Unclone();
					TestWorld->SetGameInstance(OldGameInstance);
				}
			}

			TestWorld->DestroyWorld(true);
		}
	}
}