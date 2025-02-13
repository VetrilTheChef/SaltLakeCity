// SaltLakeCity 4.25

#include "BBModelIterator.h"

UBBModelIterator::UBBModelIterator()
{
	ModelContainer = nullptr;
	Index = 0;
}

void UBBModelIterator::SetModelContainer(UIBBGUIModelContainer * NewModelContainer)
{
	ModelContainer = NewModelContainer;
}

bool UBBModelIterator::HasNext() const
{
	return (IsValid(ModelContainer) &&
			(Index < ModelContainer->GetNumModels()));
}

UIBBGUIModel * UBBModelIterator::Next() const
{
	if (IsValid(ModelContainer))
	{
		return ModelContainer->Get(Index++);
	}

	return nullptr;
}