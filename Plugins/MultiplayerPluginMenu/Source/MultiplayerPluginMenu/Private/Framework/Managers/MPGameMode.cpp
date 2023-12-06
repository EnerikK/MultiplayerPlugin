// Hello :)


#include "Framework/Managers/MPGameMode.h"

#include "Engine/AssetManager.h"
#include "Framework/Data/MPGameData.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/Managers/MPGameState.h"
#include "Framework/Player/MPPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMPGameMode::AMPGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bGameReady = false;
}

void AMPGameMode::InitGameState()
{
	Super::InitGameState();

	SessionPlayers.Empty();
	
	if(AMPGameState* AGameState = Cast<AMPGameState>(GameState))
	{
		AGameState->OnGameStateReady.AddDynamic(this,&AMPGameMode::OnGameReady);
		
	}

	//wait for the next frame to give time to initialize startup settings ,game state etc
	GetWorld()->GetTimerManager().SetTimerForNextTick(this,&ThisClass::HandleGameDataAssignment);
	
		
}

void AMPGameMode::GenericPlayerInitialization(AController* NewPlayer)
{
	Super::GenericPlayerInitialization(NewPlayer);

	if(AMPPlayerController* Player = Cast<AMPPlayerController>(NewPlayer))
	{
		SessionPlayers.AddUnique(Player);
		
	}
	
}

void AMPGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if(IsGameDataLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
	
}

bool AMPGameMode::PlayerCanRestart_Implementation(APlayerController* Player)
{
	if(bGameReady)
	{
		return Super::PlayerCanRestart_Implementation(Player);
	}
	return false;
	
}

void AMPGameMode::FailedToRestartPlayer(AController* NewPlayer)
{
	if(bGameReady)
	{
		if(APlayerController* NewPC = Cast<APlayerController>(NewPlayer))
		{
			if (PlayerCanRestart(NewPC))
			{
				RequestPlayerRestartNextFrame(NewPlayer,false);
				
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("FailedToRestartPlayer(%s) and player can restart returned false,so we are not  going to try again."),*GetPathNameSafe(NewPlayer));
			}
		}
	}
	else
	{
		RequestPlayerRestartNextFrame(NewPlayer,false);
	}
	
}

void AMPGameMode::RequestPlayerRestartNextFrame(AController* Controller, bool bForceReset)
{
	if(bForceReset && (Controller != nullptr))
	{
		Controller->Reset();
	}
	if(APlayerController* PC = Cast<APlayerController>(Controller))
	{
		GetWorldTimerManager().SetTimerForNextTick(PC,&APlayerController::ServerRestartPlayer_Implementation);
	}
}

void AMPGameMode::HandleGameDataAssignment()
{
	//Check options string from multiplayer hosting
	if(!CurrentGameDataAssetId.IsValid() && UGameplayStatics::HasOption(OptionsString,MP_MP_SETTINGS_GAMEMODE))
	{
		const FString GameDataFromOption = UGameplayStatics::ParseOption(OptionsString,MP_MP_SETTINGS_GAMEMODE);
		CurrentGameDataAssetId = FPrimaryAssetId(FPrimaryAssetType(UMPGameData::StaticClass()->GetFName()),FName(*GameDataFromOption));
	}

	//fallback to default grid
	if(!CurrentGameDataAssetId.IsValid())
	{
		CurrentGameDataAssetId = FPrimaryAssetId(FPrimaryAssetType(MP_DATA_ASSET_TYPE_GAMEDATA),MP_DATA_ASSET_TYPE_GAMEDATA_DEFAULT);
	}
	
	if(CurrentGameDataAssetId.IsValid())
	{
		OnGameDataAssignment();
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("[AMPGameMode::HandleGameDataAssignment] Failed to identify game data!" ))
	}
}

void AMPGameMode::OnGameDataAssignment()
{
	if(UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		if(CurrentGameDataAssetId.IsValid())
		{
			TArray<FName> Bundles;
			Bundles.Add(MP_DATA_ASSET_BUNDLE_GAME);
			const FStreamableDelegate GroupDataDelegate = FStreamableDelegate::CreateUObject(this,&AMPGameMode::OnGameDataLoaded);
			AssetManager->LoadPrimaryAsset(CurrentGameDataAssetId,Bundles,GroupDataDelegate);
		}
		
	}
	
}

void AMPGameMode::OnGameDataLoaded()
{
	if(GameState && CurrentGameDataAssetId.IsValid())
	{
		if(AMPGameState* AGameState = Cast<AMPGameState>(GameState))
		{
			if(UMPGameData* GameData = GetGameData())
			{
				AGameState->SetGameData(GameData);
				
			}
		}
	}
}

UMPGameData* AMPGameMode::GetGameData() const
{
	if(CurrentGameDataAssetId.IsValid())
	{
		if(const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			return Cast<UMPGameData>(AssetManager->GetPrimaryAssetObject(CurrentGameDataAssetId));
		}
	}
	return nullptr;
}

void AMPGameMode::OnGameReady()
{
	bGameReady = true;
	InitializePlayer();
	
}

void AMPGameMode::InitializePlayer()
{
	//init player data

	for(int i = 0; i < SessionPlayers.Num(); i++)
	{
		if((SessionPlayers[i] != nullptr) && (SessionPlayers[i]->GetPawn() == nullptr))
		{
			if(const UMPGameData* GameData = GetGameData())
			{
				if(PlayerCanRestart(SessionPlayers[i]))
				{
					RestartPlayer(SessionPlayers[i]);
				}
			}
		}
	}
	
	
}
