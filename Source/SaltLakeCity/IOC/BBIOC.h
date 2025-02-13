// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Controllers/Interfaces/IBBAIController.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "Misc/TypeContainer.h"
#include "Specifications/Factories/Interfaces/IBBSpecificationFactory.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"
#include "BBIOC.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable, BlueprintType)

class SALTLAKECITY_API UBBIOC : public UObject
{
	GENERATED_BODY()

	class ITypeContainer
	{
		public:
			virtual ~ITypeContainer() { }

			virtual void * Get() = 0;
	};

	template <class T>
	class TTypeContainer : public ITypeContainer
	{
	public:
		TTypeContainer(T * NewContainer) :
			Container(NewContainer) { }

		virtual ~TTypeContainer() override { }

		virtual void * Get() override
		{
			return Container;
		}

	private:
		T * Container;
	};

	class ITypeInstance
	{
		public:
			virtual ~ITypeInstance() { }

			virtual void * Get() = 0;
	};

	template <class T>
	class TTypeInstance : public ITypeInstance
	{
		public:
			TTypeInstance(T * NewInstance) :
				Instance(NewInstance) { }

			virtual ~TTypeInstance() override { }

			virtual void * Get() override
			{
				return Instance;
			}

		private:
			T * Instance;
	};

	public:
		UBBIOC();

		static UBBIOC * Create(UWorld * World)
		{
			FScopeLock Lock(& ContainersCriticalSection);
			{
				if (!Containers.Contains(World))
				{
					Containers.Add(World, MakeShareable(new TTypeContainer<UBBIOC>(NewObject<UBBIOC>(World, UBBIOC::StaticClass()))));
				}

				const TSharedPtr<ITypeContainer> & TypeContainer = Containers.FindRef(World);

				return static_cast<UBBIOC *>(TypeContainer->Get());
			}
		}

		static UBBIOC * FromWorld(UWorld * World)
		{
			FScopeLock Lock(& ContainersCriticalSection);
			{
				const TSharedPtr<ITypeContainer> & TypeContainer = Containers.FindRef(World);

				if (TypeContainer.IsValid())
				{
					return static_cast<UBBIOC *>(TypeContainer->Get());
				}

				return nullptr;
			}
		}

		static void Destroy(UWorld * World)
		{
			FScopeLock Lock(& ContainersCriticalSection);
			{
				if (Containers.Contains(World))
				{
					Containers.Remove(World);
				}
			}
		}

		template <class R, class T>
		void Register(T * NewInstance)
		{
			static_assert(TPointerIsConvertibleFromTo<R, UObject>::Value, "R must implement UObject.");
			static_assert(TPointerIsConvertibleFromTo<T, R>::Value, "T must implement R.");

			FScopeLock Lock(& InstancesCriticalSection);
			{
				Instances.Add(TNameOf<R>::GetName(), MakeShareable(new TTypeInstance<R>(NewInstance)));
			}
		}

		template <class R>
		void Unregister()
		{
			FScopeLock Lock(& InstancesCriticalSection);
			{
				if (Instances.Contains(TNameOf<R>::GetName()))
				{
					Instances.Remove(TNameOf<R>::GetName());
				}
			}
		}

		template <class R>
		R * Get()
		{
			FScopeLock Lock(& InstancesCriticalSection);
			{
				const TSharedPtr<ITypeInstance> & TypeInstance = Instances.FindRef(TNameOf<R>::GetName());

				if (TypeInstance.IsValid())
				{
					return static_cast<R *>(TypeInstance->Get());
				}

				return nullptr;
			}
		}

	private:
		static FCriticalSection ContainersCriticalSection;

		static TMap<UWorld *, TSharedPtr<ITypeContainer>> Containers;

		FCriticalSection InstancesCriticalSection;

		TMap<FString, TSharedPtr<ITypeInstance>> Instances;
};