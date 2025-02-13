// SaltLakeCity 4.27

#include "BBBuildEntryModelStub.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"

UBBBuildEntryModelStub::UBBBuildEntryModelStub() :
	Super()
{
	View = nullptr;

	EntryName = FText::FromString("");
	EntryIcon = TSoftObjectPtr<UTexture2D>();
	EntryPrice = -1.0f;
	EntryTime = -1.0f;
	TargetingClass = TSoftClassPtr<AIBBTargetingActor>();
	BuildDataClass = TSoftClassPtr<UIBBBuildData>();
	BuildableClasses = TArray<FBBBuildablePtr>();
}

UIBBWidget * UBBBuildEntryModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBBuildEntryModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return nullptr;
}

void UBBBuildEntryModelStub::Initialize(UIBBBuildEntryWidget * NewView, const UIBBBuildEntry * NewEntry)
{
	Finalize();

	View = NewView;
}

void UBBBuildEntryModelStub::Finalize()
{
	View = nullptr;

	EntryName = FText::FromString("");
	EntryIcon = TSoftObjectPtr<UTexture2D>();
	EntryPrice = -1.0f;
	EntryTime = -1.0f;
	BuildDataClass = TSoftClassPtr<UIBBBuildData>();
}

const FText UBBBuildEntryModelStub::GetEntryName() const
{
	return EntryName;
}

void UBBBuildEntryModelStub::SetEntryName(const FText NewName)
{
	EntryName = NewName;
}

const TSoftObjectPtr<UTexture2D> UBBBuildEntryModelStub::GetEntryIcon() const
{
	return EntryIcon;
}

void UBBBuildEntryModelStub::SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon)
{
	EntryIcon = NewIcon;
}

const float UBBBuildEntryModelStub::GetEntryPrice() const
{
	return EntryPrice;
}

void UBBBuildEntryModelStub::SetEntryPrice(const float NewPrice)
{
	EntryPrice = NewPrice;
}

const float UBBBuildEntryModelStub::GetEntryTime() const
{
	return EntryTime;
}

void UBBBuildEntryModelStub::SetEntryTime(const float NewTime)
{
	EntryTime = NewTime;
}

const TSoftClassPtr<UIBBBuildData> UBBBuildEntryModelStub::GetEntryBuildDataClass() const
{
	return BuildDataClass;
}

void UBBBuildEntryModelStub::SetEntryBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass)
{
	BuildDataClass = NewBuildDataClass;
}

const TSoftClassPtr<AIBBTargetingActor> UBBBuildEntryModelStub::GetEntryTargetingClass() const
{
	return TargetingClass;
}

void UBBBuildEntryModelStub::SetEntryTargetingClass(const TSoftClassPtr<AIBBTargetingActor> NewTargetingClass)
{
	TargetingClass = NewTargetingClass;
}

const TArray<FBBBuildablePtr> UBBBuildEntryModelStub::GetEntryBuildableClasses() const
{
	return BuildableClasses;
}

void UBBBuildEntryModelStub::SetEntryBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses)
{
	BuildableClasses = NewBuildableClasses;
}