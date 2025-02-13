// SaltLakeCity 4.26

#include "BBIOC.h"

FCriticalSection UBBIOC::ContainersCriticalSection;

TMap<UWorld *, TSharedPtr<UBBIOC::ITypeContainer>> UBBIOC::Containers;

UBBIOC::UBBIOC() :
	Super()
{
	Instances.Empty();
}

//FCriticalSection UBBIOC::InstancesCriticalSection;

//TMap<FString, TSharedPtr<UBBIOC::ITypeInstance>> UBBIOC::Instances;
