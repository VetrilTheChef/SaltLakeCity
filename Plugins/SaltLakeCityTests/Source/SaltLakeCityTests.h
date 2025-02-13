// SaltLakeCityTests 4.24

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FSaltLakeCityTestsModule : public IModuleInterface
{
	public:
		virtual void StartupModule() override;

		virtual void ShutdownModule() override;
};