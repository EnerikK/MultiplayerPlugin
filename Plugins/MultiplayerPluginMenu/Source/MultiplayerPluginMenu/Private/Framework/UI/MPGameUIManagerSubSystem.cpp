﻿// Hello :)


#include "Framework/UI/MPGameUIManagerSubSystem.h"
#include "CommonLocalPlayer.h"
#include "GameUIPolicy.h"
#include "PrimaryGameLayout.h"
#include "GameFramework/HUD.h"

UMPGameUIManagerSubSystem::UMPGameUIManagerSubSystem()
{
}

void UMPGameUIManagerSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this,&UMPGameUIManagerSubSystem::Tick),0.0f);
}

void UMPGameUIManagerSubSystem::Deinitialize()
{
	Super::Deinitialize();

	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UMPGameUIManagerSubSystem::Tick(float DeltaTime)
{
	SyncRootLayoutVisibilityToShowHUD();
	return true;
}

void UMPGameUIManagerSubSystem::SyncRootLayoutVisibilityToShowHUD()
{
	if(const UGameUIPolicy* Policy = GetCurrentUIPolicy())
	{
		for(const ULocalPlayer* LocalPlayer : GetGameInstance()->GetLocalPlayers())
		{
			bool bShouldShowUI = true;
			if(const APlayerController * PC = LocalPlayer->GetPlayerController(GetWorld()))
			{
				const AHUD* HUD = PC->GetHUD();
				if(HUD && !HUD->bShowHUD)
				{
					bShouldShowUI = false;
				}
			}
			if(UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
			{
				const ESlateVisibility DesiredVisibility = bShouldShowUI ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
				if(DesiredVisibility != RootLayout->GetVisibility())
				{
					RootLayout->SetVisibility(DesiredVisibility);
				}
			}
		}
	}
}
