// SaltLakeCity 4.26

#include "BBBuildEntryModel.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"
#include "Specifications/GUI/Interfaces/IBBBuildEntryWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBBuildEntryModel::UBBBuildEntryModel() :
	Super()
{
	TargetingClass = TSoftClassPtr<AIBBTargetingActor>();
	View = nullptr;
	Entry = nullptr;
}

UIBBWidget * UBBBuildEntryModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBBuildEntryModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBWidgetSpecification * BuildEntryWidgetSpecification = nullptr;

	//WidgetSpecificationFactory->NewBuildEntryWidgetSpecification(BuildEntryWidgetSpecification, this, Entry);

	return BuildEntryWidgetSpecification;
}

void UBBBuildEntryModel::Initialize(UIBBBuildEntryWidget * NewView, const UIBBBuildEntry * NewEntry)
{
	InitializeEntry(NewEntry);
	InitializeView(NewView, * Entry);
}

void UBBBuildEntryModel::Finalize()
{
	FinalizeView();
	FinalizeEntry();
}

const FText UBBBuildEntryModel::GetEntryName() const
{
	return IsValid(Entry) ? Entry->GetEntryName() : FText::FromString("");
}

const TSoftObjectPtr<UTexture2D> UBBBuildEntryModel::GetEntryIcon() const
{
	return IsValid(Entry) ? Entry->GetEntryIcon() : TSoftObjectPtr<UTexture2D>();
}

const float UBBBuildEntryModel::GetEntryPrice() const
{
	return IsValid(Entry) ? Entry->GetEntryPrice() : -1.0f;
}

const float UBBBuildEntryModel::GetEntryTime() const
{
	return IsValid(Entry) ? Entry->GetEntryTime() : -1.0f;
}

const TSoftClassPtr<UIBBBuildData> UBBBuildEntryModel::GetEntryBuildDataClass() const
{
	return IsValid(Entry) ? Entry->GetEntryBuildDataClass() : TSoftClassPtr<UIBBBuildData>();
}

const TSoftClassPtr<AIBBTargetingActor> UBBBuildEntryModel::GetEntryTargetingClass() const
{
	return TargetingClass;
}

const TArray<FBBBuildablePtr> UBBBuildEntryModel::GetEntryBuildableClasses() const
{
	return IsValid(Entry) ? Entry->GetEntryBuildables() : TArray<FBBBuildablePtr>();
}



void UBBBuildEntryModel::InitializeEntry(const UIBBBuildEntry * NewEntry)
{
	FinalizeEntry();

	verifyf(IsValid(NewEntry), TEXT("New Build Entry is invalid."));

	Entry = NewEntry;
}

void UBBBuildEntryModel::FinalizeEntry()
{
	if (IsValid(Entry))
	{
	}

	Entry = nullptr;
}

void UBBBuildEntryModel::InitializeView(UIBBBuildEntryWidget * NewView, const UIBBBuildEntry & BuildEntry)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Build Entry View is invalid."));

	View = NewView;

	View->SetEntryName(GetEntryName());
	View->SetIcon(GetEntryIcon().LoadSynchronous());
	View->SetPrice(GetEntryPrice());
	View->SetTime(GetEntryTime());
}

void UBBBuildEntryModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}