// SaltLakeCity 5.7

#include "BBUIStatics.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"


FVector2D UBBUIStatics::GetPopUpCoordinates(const UWorld* World, const UIBBWidget* Widget)
{
	verifyf(IsValid(World), TEXT("World is invalid."));
	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	FVector2D Position = UWidgetLayoutLibrary::GetMousePositionOnViewport(World);

	FVector2D WidgetSize = Widget->GetDesiredSize();

	FVector2D ViewportSize;

	UGameViewportClient* GameViewport = World->GetGameViewport();

	verifyf(IsValid(GameViewport), TEXT("Game Viewport is invalid."));

	GameViewport->GetViewportSize(ViewportSize);

	Position.X = FMath::Min(Position.X, ViewportSize.X - WidgetSize.X);

	Position.Y = FMath::Min(Position.Y, ViewportSize.Y - WidgetSize.Y);

	return Position;
}

bool UBBUIStatics::ConvertToPIEViewportSpace(const UWorld* World, FVector2D& Position)
{
	#if WITH_EDITOR

	if (IsValid(World))
	{
		UGameViewportClient * GameViewport = World->GetGameViewport();

		if (IsValid(GameViewport))
		{
			if (GameViewport->bIsPlayInEditorViewport)
			{
				FIntPoint IntPosition = FIntPoint::ZeroValue;
				IntPosition.X = FMath::RoundToInt(Position.X);
				IntPosition.Y = FMath::RoundToInt(Position.Y);

				Position = GameViewport->Viewport->VirtualDesktopPixelToViewport(IntPosition);

				FVector2D ViewportSize = FVector2D::ZeroVector;
				GameViewport->GetViewportSize(ViewportSize);

				Position *= ViewportSize;

				return true;
			}
		}
	}

	#endif

	return false;
}