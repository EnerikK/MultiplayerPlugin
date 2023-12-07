// Hello :)


#include "Framework/UI/MPButtonGameWidget.h"
#include "Engine/AssetManager.h"
#include "Framework/Data/MPGameData.h"

void UMPButtonGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMPButtonGameWidget::SetGameData(const FPrimaryAssetId& GameDataAssetId)
{
	if(GameDataAssetId.IsValid())
	{
		if(const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			if(const UMPGameData* GameData = Cast<UMPGameData>(AssetManager->GetPrimaryAssetObject(GameDataAssetId)))
			{
				InitButton();
				UpdateButtonText(GameData->GameMap,GameData->GameName,GameData->GameDesc);
				if(GameData->GameImage.LoadSynchronous())
				{
					/*ButtonTexture = GameData->GameImage.LoadSynchronous();*/
					SetButtonSettings();
				}
			}
		}
	}
	
}

void UMPButtonGameWidget::UpdateButtonText(const FText& GameMapText, const FText& GameNameText,
	const FText& GameDescText)
{
	if(ButtonTextBlock)
	{
		ButtonText = GameMapText;
		SetButtonText(GameMapText);
	}
	if(Name)
	{
		Name->SetText(GameNameText);
		
	}
	if(Desc)
	{
		Desc->SetText(GameDescText);
	}
}

