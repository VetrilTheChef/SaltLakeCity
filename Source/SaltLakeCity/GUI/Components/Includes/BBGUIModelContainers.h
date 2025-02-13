// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "Runtime/Core/Public/HAL/ThreadingBase.h"
#include "BBGUIModelContainers.generated.h"

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBGUIModelContainer : public UObject
{
	GENERATED_BODY()

	public:
		UIBBGUIModelContainer() : Super() { };

		virtual void Initialize(FTimerManager & NewTimerManager) PURE_VIRTUAL(UIBBGUIModelContainer::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBGUIModelContainer::Finalize, );

		virtual void Add(UIBBGUIModel * NewModel) PURE_VIRTUAL(UIBBGUIModelContainer::Add, );

		virtual int GetNumModels() const PURE_VIRTUAL(UIBBGUIModelContainer::GetNumModels, return -1; );

		virtual UIBBGUIModel * Get(int Index) const PURE_VIRTUAL(UIBBGUIModelContainer::Get, return nullptr; );

		virtual void Update() PURE_VIRTUAL(UIBBGUIModelContainer::Update, );
};

UCLASS(Blueprintable, BlueprintType)

class UBBGUIModelArray : public UIBBGUIModelContainer
{
	GENERATED_BODY()

	public:
		UBBGUIModelArray() : Super()
		{
			Models.Empty();
			TimerManager = nullptr;
		};

		virtual void Initialize(FTimerManager & NewTimerManager) override
		{
			TimerManager = & NewTimerManager;

			TimerManager->SetTimer(TimerHandle, this, & UBBGUIModelArray::Update, 10.0f, true);
		}

		virtual void Finalize() override
		{
			if (TimerManager)
			{
				TimerManager->ClearTimer(TimerHandle);
			}
			TimerManager = nullptr;
		}

		virtual void Add(UIBBGUIModel * NewModel) override
		{
			FScopeLock ScopeLock(& CriticalSection);
			{
				Models.Emplace(NewModel);
			}
		}

		virtual int GetNumModels() const override
		{
			FScopeLock ScopeLock(& CriticalSection);
			{
				return Models.Num();
			}
		}

		virtual UIBBGUIModel * Get(int Index) const override
		{
			FScopeLock ScopeLock(& CriticalSection);
			{
				return Models.IsValidIndex(Index) ? Models[Index] : nullptr;
			}
		}

		virtual void Update() override
		{
			FScopeLock ScopeLock(& CriticalSection);
			{
				// Reversed loop to avoid having to adjust the current index
				// as entries are removed and the array elements shift up
				for (int Index = Models.Num() - 1; Index >= 0; Index--)
				{
					UIBBGUIModel * Model = Models[Index];

					// Don't remove if:
					// - model is valid
					if (IsValid(Model))
					{
						UIBBWidget * Widget = Model->GetWidget();

						// Don't remove if:
						// - widget is valid (regardless)
						// - widget is in viewport
						if (IsValid(Widget) && Widget->IsVisible())
						{
							continue;
						}
					}

					// At this point it's safe to remove the model from the pool

					Models.RemoveAt(Index);
				}
			}
		}

	protected:
		UPROPERTY()
		TArray<UIBBGUIModel *> Models;

		FTimerManager * TimerManager;

		FTimerHandle TimerHandle;

		mutable FCriticalSection CriticalSection;
};

UCLASS(Blueprintable, BlueprintType)

class UBBGUIModelSingle : public UIBBGUIModelContainer
{
	GENERATED_BODY()

	public:
		UBBGUIModelSingle() : Super()
		{
			Model = nullptr;
			TimerManager = nullptr;
		};

		virtual void Initialize(FTimerManager & NewTimerManager) override
		{
			TimerManager = & NewTimerManager;

			TimerManager->SetTimer(TimerHandle, this, & UBBGUIModelSingle::Update, 10.0f, true);
		}

		virtual void Finalize() override
		{
			if (TimerManager)
			{
				TimerManager->ClearTimer(TimerHandle);
			}
		}

		virtual void Add(UIBBGUIModel * NewModel) override
		{
			FScopeLock ScopeLock(& CriticalSection);
			{
				Model = NewModel;
			}
		}

		virtual int GetNumModels() const override
		{
			FScopeLock ScopeLock(& CriticalSection);
			{
				return IsValid(Model);
			}
		}

		virtual UIBBGUIModel * Get(int Index) const override
		{
			FScopeLock ScopeLock(& CriticalSection);
			{
				return (Index == 0) ? Model : nullptr;
			}
		}

		virtual void Update() override
		{
			// Single models should never be removed
		}

	private:
		UPROPERTY()
		UIBBGUIModel * Model;

		FTimerManager * TimerManager;

		FTimerHandle TimerHandle;

		mutable FCriticalSection CriticalSection;
};