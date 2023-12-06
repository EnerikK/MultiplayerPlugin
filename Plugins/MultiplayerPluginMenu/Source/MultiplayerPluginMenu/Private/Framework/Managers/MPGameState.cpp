// Hello :)


#include "Framework/Managers/MPGameState.h"
#include <Framework/Data/MPGameData.h>
#include "Net/UnrealNetwork.h"

AMPGameState::AMPGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AMPGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, GameData)
	
}


void AMPGameState::SetGameData(UMPGameData* NewGameData)
{
	if(NewGameData != nullptr)
	{
		GameData = NewGameData;
	}
}

bool AMPGameState::bShouldShowMenu() const
{
	if(GameData != nullptr)
	{
		return GameData->bShowMenu;
	}
	return false;
}

TSoftClassPtr<UCommonActivatableWidget> AMPGameState::GetMenuClass() const
{
	if(GameData != nullptr)
	{
		return GameData->MainMenuClass;
	}
	return nullptr;
}


void AMPGameState::OnRep_GameData()
{
	if(HasAuthority())
	{
		OnGameStateReady.Broadcast();
	}
}
