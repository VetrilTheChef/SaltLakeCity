// SaltLakeCity 4.27

#include "BBSkillEntryModelStub.h"
#include "GUI/Widgets/Interfaces/IBBSkillEntryWidget.h"

UBBSkillEntryModelStub::UBBSkillEntryModelStub() :
	Super()
{
	View = nullptr;

	EntryName = FText::FromString("");
	EntryIcon = TSoftObjectPtr<UTexture2D>();
	EntryValue = -1.0f;
	EntryMaxValue = -1.0f;
}

UIBBWidget * UBBSkillEntryModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBSkillEntryModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return nullptr;
}

void UBBSkillEntryModelStub::Initialize(UIBBSkillEntryWidget * NewView, const UIBBSkillEntry * NewEntry)
{
	Finalize();

	View = NewView;
}

void UBBSkillEntryModelStub::Finalize()
{
	View = nullptr;

	EntryName = FText::FromString("");
	EntryIcon = TSoftObjectPtr<UTexture2D>();
	EntryValue = -1.0f;
	EntryMaxValue = -1.0f;
}

const FText UBBSkillEntryModelStub::GetEntryName() const
{
	return EntryName;
}

void UBBSkillEntryModelStub::SetEntryName(const FText NewName)
{
	EntryName = NewName;
}

const TSoftObjectPtr<UTexture2D> UBBSkillEntryModelStub::GetEntryIcon() const
{
	return EntryIcon;
}

void UBBSkillEntryModelStub::SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon)
{
	EntryIcon = NewIcon;
}

const float UBBSkillEntryModelStub::GetEntryValue() const
{
	return EntryValue;
}

void UBBSkillEntryModelStub::SetEntryValue(const float NewValue)
{
	EntryValue = NewValue;
}

const float UBBSkillEntryModelStub::GetEntryMaxValue() const
{
	return EntryMaxValue;
}

void UBBSkillEntryModelStub::SetEntryMaxValue(const float NewMaxValue)
{
	EntryMaxValue = NewMaxValue;
}