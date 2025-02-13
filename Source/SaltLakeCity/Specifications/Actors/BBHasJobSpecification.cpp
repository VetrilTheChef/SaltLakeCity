// SaltLakeCity 4.27

#include "BBHasJobSpecification.h"
//#include "Actors/Interfaces/BBHasJob.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"

UBBHasJobSpecification::UBBHasJobSpecification() :
	Super()
{
}

bool UBBHasJobSpecification::Evaluate(UObject * Object)
{
	APawn * Pawn = Cast<APawn>(Object);

	if (IsValid(Pawn))
	{
		AController * Controller = Pawn->GetController();

		if (IsValid(Controller))
		{
			//return Controller->Implements<UBBHasJob>();
		}
	}

	return false;
}