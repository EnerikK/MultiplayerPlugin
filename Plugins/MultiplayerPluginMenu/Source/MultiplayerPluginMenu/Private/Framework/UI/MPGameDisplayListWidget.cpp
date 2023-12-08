// Hello :)


#include "Framework/UI/MPGameDisplayListWidget.h"
#include "Components/VerticalBox.h"
#include "Engine/AssetManager.h"
#include "Framework/Data/MPGameData.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/UI/MPGameDisplayWidget.h"

void UMPGameDisplayListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LoadGameList();
}

TArray<UWidget*> UMPGameDisplayListWidget::GetGameListWidgetList() const
{
	if(GameList)
	{
		return GameList->GetAllChildren();
	}
	return TArray<UWidget*>();
}


void UMPGameDisplayListWidget::LoadGameList()
{
	if(GameList)
	{
		GameList->ClearChildren();
		if(UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			TArray<FPrimaryAssetId> GameDataAssets;
			const FPrimaryAssetType GroupAssetType(MP_DATA_ASSET_TYPE_GAMEDATA);
			AssetManager->GetPrimaryAssetIdList(GroupAssetType,GameDataAssets);
			if(GameDataAssets.Num()>0)
			{
				const TArray<FName> Bundles;
				const FStreamableDelegate GroupDataLoadedDelegate = FStreamableDelegate::CreateUObject(this,&UMPGameDisplayListWidget::OnGameDataLoaded,GameDataAssets);
				AssetManager->LoadPrimaryAssets(GameDataAssets,Bundles,GroupDataLoadedDelegate);
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("Failed to get gamedataassets Assets"));
			}
		}
	}
}

void UMPGameDisplayListWidget::OnGameDataLoaded(TArray<FPrimaryAssetId> GameDataAssets)
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}
	if(const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		for(int i = 0; i < GameDataAssets.Num(); i++)
		{
			if(const UMPGameData* GameData = Cast<UMPGameData>(AssetManager->GetPrimaryAssetObject(GameDataAssets[i])))
			{
				if(GameData->bIncludedGameList)
				{
					if(GameData->GameDisplayWidgetClass.IsValid())
					{
						if(UMPGameDisplayWidget* GameDisplay = CreateWidget<UMPGameDisplayWidget>(
							GetOwningPlayer()->GetWorld(),
							GameData->GameDisplayWidgetClass.LoadSynchronous()))
						{
							GameDisplay->SetGameData(GameDataAssets[i]);
							GameList->AddChildToVerticalBox(GameDisplay);
						}
					}
				}
			}
		}
	}
	OnGameListCreation();
}

void UMPGameDisplayListWidget::OnGameListCreation()
{
	OnGameListCreated.Broadcast();
	TArray<UWidget*> DisplayWidgets = GetGameListWidgetList();
	for(int i = 0; i < DisplayWidgets.Num(); i++)
	{
		if(UMPGameDisplayWidget* DisplayWidget = Cast<UMPGameDisplayWidget>(DisplayWidgets[i]))
		{
			DisplayWidget->OnGameDisplaySelected.AddDynamic(this,*UMPGameDisplayListWidget::OnGameDisplaySelection);
			
		}
	}
	
}

void UMPGameDisplayListWidget::OnGameDisplaySelection(const FPrimaryAssetId& SelectedGameData)
{
	OnGameSelected.Broadcast(SelectedGameData);
}
