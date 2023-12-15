// Hello :)


#include "Framework/UI/MPGameSessionButton.h"
#include "CommonTextBlock.h"

void UMPGameSessionButton::SetTextDisplays(const FText& Game, const FText& Map, const FText& Ping,
                                           const FText& PlayerCount, const FText& MaxPlayerCount)
{
	if(ButtonTextBlock)
	{
		SetButtonText(Game);
	}
	if(MapText)
	{
		MapText->SetText(Map);
	}
	if(PingText)
	{
		PingText->SetText(Ping);
	}
	if(PlayerCountText)
	{
		PlayerCountText->SetText(PlayerCount);
	}
	if(MaxPlayerCountText)
	{
		MaxPlayerCountText->SetText(MaxPlayerCount);
	}
	
}
