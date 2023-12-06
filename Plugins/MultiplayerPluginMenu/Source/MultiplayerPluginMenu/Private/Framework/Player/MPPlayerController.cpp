// Hello :)


#include "Framework/Player/MPPlayerController.h"

#include "PrimaryGameLayout.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/Managers/MPGameState.h"

AMPPlayerController::AMPPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AMPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(IsLocalController())
	{
		if(const UWorld* WorldContext = GetWorld())
		{
			if(const AMPGameState* GameState = Cast<AMPGameState>(WorldContext->GetGameState()))
			{
				ShowMenu(GameState->GetMenuClass());
			}
		}
	}
}

void AMPPlayerController::ShowMenu(const TSoftClassPtr<UCommonActivatableWidget>& MenuClass)
{
	if(MenuClass == nullptr)
	{
		return;
	}
	if(const UWorld* WorldContext = GetWorld())
	{
		if(UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext))
		{
			RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(UILayerTags::TAG_UI_LAYER_MENU,true,MenuClass
				,[this](EAsyncWidgetLayerState State,UCommonActivatableWidget* Screen)
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
