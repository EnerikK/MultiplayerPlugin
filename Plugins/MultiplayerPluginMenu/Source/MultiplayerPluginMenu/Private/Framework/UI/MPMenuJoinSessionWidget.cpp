// Hello :)


#include "Framework/UI/MPMenuJoinSessionWidget.h"
#include "CommonBorder.h"
#include "CommonGameInstance.h"
#include "CommonSessionSubsystem.h"
#include "PrimaryGameLayout.h"
#include "Framework/UI/MPCommonButtonBase.h"

void UMPMenuJoinSessionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(RefreshButton)
	{
		RefreshButton->OnClicked().AddUObject(this,&UMPMenuJoinSessionWidget::OnRefreshList);
		
	}
	if(BackButton)
	{
		BackButton->OnClicked().AddUObject(this,&UMPMenuJoinSessionWidget::OnBackMenu);
	}
}

void UMPMenuJoinSessionWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	StartSearch();
}

UWidget* UMPMenuJoinSessionWidget::NativeGetDesiredFocusTarget() const
{
	if(ListView)
	{
		return ListView;
	}
	
	return Super::NativeGetDesiredFocusTarget();
}

void UMPMenuJoinSessionWidget::StartSearch()
{
	UE_LOG(LogTemp,Warning,TEXT("[UMPMenuJoinSessionWidget::StartSearch] StartSearch"));
	
	if(bSearchInProgress || !GetOwningPlayer() || !GetOwningPlayer()->GetWorld() || !ListView)
	{
		UE_LOG(LogTemp,Warning,TEXT("[UMPMenuJoinSessionWidget::StartSearch] Search Failed"));
		return;
	}
	bSearchInProgress = true;
	NoSessionsDisplay->SetVisibility(ESlateVisibility::Collapsed);
	ListView->ClearListItems();
	SetSpinnerDisplay(true);

	if(const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(GetOwningPlayer()->GetWorld()->GetGameInstance()))
	{
		if(UCommonSessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
		{
			if(UCommonSession_SearchSessionRequest* SessionSearchRequest  = SessionSubsystem->CreateOnlineSearchSessionRequest())
			{
				SessionSearchRequest->OnSearchFinished.AddUObject(this,&UMPMenuJoinSessionWidget::OnSessionSearchComplete,SessionSearchRequest);
				SessionSubsystem->FindSessions(GetOwningPlayer(),SessionSearchRequest);
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("[UMPMenuJoinSessionWidget::StartSearch] Failed to create session"));
			}
		}
	}
}

void UMPMenuJoinSessionWidget::SetSpinnerDisplay(const bool bSpinnerState) const
{
	if(SpinnerDisplay)
	{
		SpinnerDisplay->SetVisibility(bSpinnerState ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		
	}
}


void UMPMenuJoinSessionWidget::OnRefreshList()
{
	if(!bSearchInProgress)
	{
		StartSearch();
	}
}

void UMPMenuJoinSessionWidget::OnSessionSearchComplete(bool bSucceeded, const FText& ErrorMessage,
	UCommonSession_SearchSessionRequest* SessionSearchSessionRequest)
{
	if(bSucceeded && SessionSearchSessionRequest)
	{
		if(SessionSearchSessionRequest->Results.Num()>0)
		{
			ListView->SetListItems(SessionSearchSessionRequest->Results);
			ListView->SetUserFocus(GetOwningPlayer());
			NoSessionsDisplay->SetVisibility(ESlateVisibility::Collapsed);
			
		}
		else
		{
			NoSessionsDisplay->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		NoSessionsDisplay->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp,Error,TEXT("[UMPMenuJoinSessionWidget::OnSessionSearchComplete] Failed Search Session"));

	}
}

void UMPMenuJoinSessionWidget::OnBackMenu()
{
	if(const UWorld* WorldContext = GetWorld())
	{
		if(UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext))
		{
			RootLayout->FindAndRemoveWidgetFromLayer(this);
		}
	}
}
