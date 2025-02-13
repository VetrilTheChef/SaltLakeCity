#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Tests/BBTestUtil.h"

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FBBDestroyActorLatentCommand, UWorld *, World, AActor *, Actor);

bool FBBDestroyActorLatentCommand::Update()
{
	if (IsValid(World))
	{
		World->DestroyActor(Actor);
	}

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FBBCloseTestWorldLatentCommand, UWorld *, TestWorld);

bool FBBCloseTestWorldLatentCommand::Update()
{
	UBBTestUtil::CloseTestWorld(TestWorld);

	return true;
}