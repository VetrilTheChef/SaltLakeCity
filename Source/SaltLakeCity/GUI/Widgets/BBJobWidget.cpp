// SaltLakeCity 5.7

#include "BBJobWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Components/BBButton.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "Engine/World.h"

UBBJobWidget::UBBJobWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	Jobs.Empty();
}

void UBBJobWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeComboBox();
}

void UBBJobWidget::BeginDestroy()
{
	DestroyTitle();

	Super::BeginDestroy();
}

EBBWidget UBBJobWidget::GetType() const
{
	return EBBWidget::Job;
}

void UBBJobWidget::AddToScreen(int32 ZOrder)
{
	AddToViewport(ZOrder);
}

void UBBJobWidget::SetDisplayName(FText NewDisplayName)
{
	verifyf(IsValid(NameText), TEXT("Name Text is invalid."));

	NameText->SetText(NewDisplayName);
}

void UBBJobWidget::AddJob(EBBJob Job, FText NewJobName, FText NewJobTooltip)
{
	Jobs.Add(Job, NewJobName.ToString());

	JobComboBox->AddOption(NewJobName.ToString());
}

void UBBJobWidget::ClearJobs()
{
	Jobs.Empty();
	JobComboBox->ClearOptions();
}

void UBBJobWidget::SetJob(EBBJob Job)
{
	JobComboBox->SetSelectedOption(Jobs.FindChecked(Job));
}

UIBBTitleWidget*& UBBJobWidget::GetTitle()
{
	return Title;
}

void UBBJobWidget::SetAcceptCommand(UIBBCommand* NewAcceptCommand)
{
	verifyf(IsValid(AcceptButton), TEXT("Accept Button is invalid."));

	AcceptButton->SetCommand(NewAcceptCommand);
}

void UBBJobWidget::SetCancelCommand(UIBBCommand* NewCancelCommand)
{
	verifyf(IsValid(CancelButton), TEXT("Cancel Button is invalid."));

	CancelButton->SetCommand(NewCancelCommand);
}



void UBBJobWidget::InitializeComboBox()
{
	verifyf(IsValid(JobComboBox), TEXT("Job Combo Box is invalid."));
	
	JobComboBox->ClearOptions();
	JobComboBox->OnSelectionChanged.AddDynamic(this, & UBBJobWidget::OnJobSelected);
}

void UBBJobWidget::DestroyTitle()
{
	if (IsValid(Title))
	{
		Title->MarkAsGarbage();
	}

	Title = nullptr;
}

void UBBJobWidget::OnJobSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	const EBBJob * Job = Jobs.FindKey(SelectedItem);

	verifyf(Job, TEXT("Selected Job type is invalid."));

	OnJobUpdate().Broadcast(* Job);
}