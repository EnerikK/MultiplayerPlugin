// Hello :)


#include "Framework/UI/MPGameSessionEntry.h"

#include "CommonGameInstance.h"
#include "CommonSessionSubsystem.h"
#include "Engine/AssetManager.h"
#include "Framework/Data/MPGameData.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/UI/MPGameSessionButton.h"


void UMPGameSessionEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(SessionButton)
	{
		SessionButton->OnClicked().AddUObject(this,&UMPGameSessionEntry::OnSessionSelected);
	}
}

void UMPGameSessionEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{

	SessionSearchResult = Cast<UCommonSession_SearchResult>(ListItemObject);
	if(SessionSearchResult != nullptr)
	{
		FString GameDataName;
		bool bDataFound;
		SessionSearchResult->GetStringSetting(MP_MP_SETTINGS_GAMEMODE,GameDataName,bDataFound);
		if(bDataFound)
		{
			const FPrimaryAssetType Type(UMPGameData::StaticClass()->GetFName());
			GameDataId = FPrimaryAssetId(Type,FName(*GameDataName));

			if(GameDataId.IsValid())
			{
				if(UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
				{
					const TArray<FName> Bundles;
					const FStreamableDelegate DataLoadedDelegate = FStreamableDelegate::CreateUObject(this,&UMPGameSessionEntry::OnGameDataLoaded);
					AssetManager->LoadPrimaryAsset(GameDataId,Bundles,DataLoadedDelegate);
					
				}
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("[UMPGameSessionEntry::NativeOnListItemObjectSet] GameDataAssetId is not valid "));
			}
			
		}
	}
	
}

void UMPGameSessionEntry::OnSessionSelected()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}
	if(const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(GetOwningPlayer()->GetWorld()->GetGameInstance()))
	{
		if(UCommonSessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
		{
			JoinSessionHandle = SessionSubsystem->OnJoinSessionCompleteEvent.AddUObject(this,&UMPGameSessionEntry::OnJoinSessionComplete);
			SessionSubsystem->JoinSession(GetOwningPlayer(),SessionSearchResult);
		}
	}
}

void UMPGameSessionEntry::OnJoinSessionComplete(const FOnlineResultInformation& Result)
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		
	}
	if(Result.bWasSuccessful)
	{
		if(const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(GetOwningPlayer()->GetWorld()->GetGameInstance()))
		{
			if(UCommonSessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
			{
				SessionSubsystem->OnJoinSessionCompleteEvent.Remove(JoinSessionHandle);
			}
		}
	}
}

void UMPGameSessionEntry::OnGameDataLoaded()
{
	if(GameDataId.IsValid())
	{
		if(const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			if(const UMPGameData* GameData = Cast<UMPGameData>(AssetManager->GetPrimaryAssetObject(GameDataId)))
			{
				if(SessionButton)
				{
					SessionButton->SetTextDisplays(
					GameData->GameName,
					GameData->GameMap,
					FText::AsNumber(SessionSearchResult->GetPingInMs()),
					FText::AsNumber(SessionSearchResult->GetMaxPublicConnections() - SessionSearchResult->GetNumOpenPublicConnections()),
					FText::AsNumber(SessionSearchResult->GetMaxPublicConnections())
						);
				}
			}
		}
	}
}


