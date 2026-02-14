// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "BBNeedTags.generated.h"

/**
*
*/

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Need_Hunger);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Need_Sleep);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Need_Thirst);

UE_DEFINE_GAMEPLAY_TAG(Need_Hunger, "Need.Health");
UE_DEFINE_GAMEPLAY_TAG(Need_Sleep, "Need.Sleep");
UE_DEFINE_GAMEPLAY_TAG(Need_Thirst, "Need.Thirst");