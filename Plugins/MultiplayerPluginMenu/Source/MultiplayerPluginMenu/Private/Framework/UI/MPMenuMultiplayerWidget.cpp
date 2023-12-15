// Hello :)


#include "Framework/UI/MPMenuMultiplayerWidget.h"
#include "PrimaryGameLayout.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/UI/MPCommonButtonBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Framework/UI/MPMenuHostSessionWidget.h"
#include "Framework/UI/MPMenuJoinSessionWidget.h"


void UMPMenuMultiplayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(HostButton)
	{
		HostButton->OnClicked().AddUObject(this,&UMPMenuMultiplayerWidget::OnHostButtonClicked);
	}
	if(JoinButton)
	{
		JoinButton->OnClicked().AddUObject(this,&UMPMenuMultiplayerWidget::OnJoinButtonClicked);
	}
	if(ExitButton)
	{
		ExitButton->OnClicked().AddUObject(this,&UMPMenuMultiplayerWidget::OnExiButtonClicked);
	}
	
	
}

UWidget* UMPMenuMultiplayerWidget::NativeGetDesiredFocusTarget() const
{
	if(HostButton)
	{
		return HostButton;
	}

	
	return Super::NativeGetDesiredFocusTarget();
}

void UMPMenuMultiplayerWidget::OnHostButtonClicked()
{
	if(HostWidgetClass == nullptr)
	{
		return;
	}
	if(const UWorld* WorldContext = GetWorld())
	{
		if(UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext))
		{
			RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(UILayerTags::TAG_UI_LAYER_MENU,
				true,
				HostWidgetClass,
				[this](EAsyncWidgetLayerState State,UCommonActivatableWidget*Screen)
				{
					switch (State)
					{
					case EAsyncWidgetLayerState::AfterPush:
						return;
					case EAsyncWidgetLayerState::Canceled:
						return;
					}
				});
		}
	}
}

void UMPMenuMultiplayerWidget::OnJoinButtonClicked()
{
	if(JoinWidgetClass == nullptr)
	{
		return;
	}
	if(const UWorld* WorldContext = GetWorld())
	{
		if(UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext))
		{
			RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(UILayerTags::TAG_UI_LAYER_MENU,
				true,
				JoinWidgetClass,
				[this](EAsyncWidgetLayerState State,UCommonActivatableWidget*Screen)
				{
					switch (State)
					{
					case EAsyncWidgetLayerState::AfterPush:
						return;
					case EAsyncWidgetLayerState::Canceled:
						return;
					}
				});
		}
	}
}

void UMPMenuMultiplayerWidget::OnExiButtonClicked()
{
	if(GetOwningPlayer())
	{
		if(const UWorld* WorldContext = GetWorld())
		{
        		UKismetSystemLibrary::QuitGame(WorldContext,GetOwningPlayer(),EQuitPreference::Quit,false);
		}
	}
}
