// Hello :)


#include "Framework/UI/MPMenuHostSessionWidget.h"

#include "CommonGameInstance.h"
#include "CommonSessionSubsystem.h"
#include "CommonTextBlock.h"
#include "CommonUserSubsystem.h"
#include "PrimaryGameLayout.h"
#include "Framework/Data/MPGameData.h"
#include "Framework/UI/MPCommonButtonBase.h"
#include "Framework/UI/MPGameDisplayListWidget.h"
#include "Framework/UI/MPGameDisplayWidget.h"

void UMPMenuHostSessionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	NetMode = ECommonSessionOnlineMode::Online;
	InitTextDisplay();

	if(ChangeNetModeButton)
	{
		ChangeNetModeButton->OnClicked().AddUObject(this,&UMPMenuHostSessionWidget::OnNetworkModeButtonClicked);
	}
	if(ChangeSetting1Button)
	{
		ChangeNetModeButton->OnClicked().AddUObject(this,&UMPMenuHostSessionWidget::OnSetting1Changed);
	}
	if(ChangeSetting1Button)
	{
		ChangeNetModeButton->OnClicked().AddUObject(this,&UMPMenuHostSessionWidget::OnSetting2Changed);
	}
	if(LaunchButton)
	{
		LaunchButton->OnClicked().AddUObject(this,&UMPMenuHostSessionWidget::OnLaunchGame);
	}
	if(BackButton)
	{
		BackButton->OnClicked().AddUObject(this,&UMPMenuHostSessionWidget::OnBackButton);
	}
	if(GameList)
	{
		GameList->OnGameListCreated.AddDynamic(this,&UMPMenuHostSessionWidget::OnGameListCreated);
		GameList->OnGameSelected.AddDynamic(this,&UMPMenuHostSessionWidget::OnGameSelected);
	}
}

void UMPMenuHostSessionWidget::InitTextDisplay() const
{
	if(NetworkModeText)
	{
		NetworkModeText->SetText(UEnum::GetDisplayValueAsText(NetMode));
	}
	if(NetworkModeText)
	{
		NetworkModeText->SetText(UEnum::GetDisplayValueAsText(Setting1));
	}
	if(NetworkModeText)
	{
		NetworkModeText->SetText(UEnum::GetDisplayValueAsText(Setting2));
	}
	
	
}

void UMPMenuHostSessionWidget::AttemptOnlineLogin()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}
	if(const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(GetOwningPlayer()->GetWorld()->GetGameInstance()))
	{
		if(UCommonUserSubsystem* UserSubsystem = GameInstance->GetSubsystem<UCommonUserSubsystem>())
		{
			UserSubsystem->OnUserInitializeComplete.AddDynamic(this,&UMPMenuHostSessionWidget::OnUserOnlineLogin);
			UserSubsystem->TryToLoginForOnlinePlay(0);
		}
	}
}

void UMPMenuHostSessionWidget::HostSession()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}
	if(const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(GetOwningPlayer()->GetWorld()->GetGameInstance()))
	{
		if(UCommonSessionSubsystem* SessionSubSystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
		{
			SessionSubSystem->OnCreateSessionCompleteEvent.AddUObject(this,&UMPMenuHostSessionWidget::OnSessionCreated);
			UCommonSession_HostSessionRequest* Request = CreateHostingRequest();
			SessionSubSystem->HostSession(GetOwningPlayer(),Request);
			
		}
	}
}

UCommonSession_HostSessionRequest* UMPMenuHostSessionWidget::CreateHostingRequest() const
{
	UCommonSession_HostSessionRequest* Request = NewObject<UCommonSession_HostSessionRequest>();
	if(GameDataId.IsValid())
	{
		if(const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			if(const UMPGameData* GameData = Cast<UMPGameData>(AssetManager->GetPrimaryAssetObject(GameDataId)))
			{
				const FString GameDataName = GameDataId.PrimaryAssetName.ToString();
				Request->ModeNameForAdvertisement = GameDataName;
				Request->OnlineMode = ECommonSessionOnlineMode::Online;
				Request->bUseLobbies = true;
				Request->MapID = GameData->MapID;
				Request->ExtraArgs = GameData->ExtraArgs;
				Request->MaxPlayerCount = GameData->MaxPlayerCount;
			}
		}
	}
	return Request;
}

void UMPMenuHostSessionWidget::OnSessionCreated(const FOnlineResultInformation& Result)
{
	if(Result.bWasSuccessful)
	{
		UE_LOG(LogTemp,Log,TEXT("SessionCreated"))
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("Failed to create Session"))
	}
	
}
void UMPMenuHostSessionWidget::OnUserOnlineLogin(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error,
	ECommonUserPrivilege RequestedPrivilege, ECommonUserOnlineContext OnlineContent)
{
	if(bSuccess)
	{
		HostSession();
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Failed to login online"))
	}
}
void UMPMenuHostSessionWidget::OnLaunchGame()
{
	AttemptOnlineLogin();
}


void UMPMenuHostSessionWidget::OnBackButton()
{
	if(const UWorld* WorldContext = GetWorld())
	{
		if(UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext))
		{
			RootLayout->FindAndRemoveWidgetFromLayer(this);
		}
	}
}

void UMPMenuHostSessionWidget::OnGameListCreated()
{
	TArray<UWidget*> DisplayWidgets = GameList->GetGameListWidgetList();
	if(DisplayWidgets.IsValidIndex(0))
	{
		if(const UMPGameDisplayWidget* DisplayWidget = Cast<UMPGameDisplayWidget>(DisplayWidgets[0]))
		{
			const FPrimaryAssetId& DisplayGameData = DisplayWidget->GetGameDataAsset();
			OnGameSelected(DisplayGameData);
		}
	}
}

void UMPMenuHostSessionWidget::OnGameSelected(const FPrimaryAssetId& SelectedGameData)
{
	if(!SelectedGameData.IsValid())
	{
		return;
	}
	GameDataId = SelectedGameData;

	if(const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		if(const UMPGameData* GameData = Cast<UMPGameData>(AssetManager->GetPrimaryAssetObject(SelectedGameData)))
		{
			if(SelectedGameTitleText && GameData)
			{
				SelectedGameTitleText->SetText(GameData->GameName);
			}
		}
	}
}

void UMPMenuHostSessionWidget::OnSetting1Changed()
{
	switch (Setting1)
	{
		case ESetting1::Set1:
			Setting1 = ESetting1::Set2;
			break;
		case ESetting1::Set2:
			Setting1 = ESetting1::Set1;
			break;
		default:;
	}
	if(GameSetting1Text)
	{
		GameSetting1Text->SetText(UEnum::GetDisplayValueAsText(Setting1));
	}
}

void UMPMenuHostSessionWidget::OnSetting2Changed()
{
	switch (Setting2)
	{
	case ESetting2::Set3:
		Setting2 = ESetting2::Set4;
		break;
	case ESetting2::Set4:
		Setting2 = ESetting2::Set3;
		break;
	default:;
	}
	if(GameSetting1Text)
	{
		GameSetting1Text->SetText(UEnum::GetDisplayValueAsText(Setting2));
	}
}

void UMPMenuHostSessionWidget::OnNetworkModeButtonClicked()
{
	switch (NetMode)
	{
		case ECommonSessionOnlineMode::Offline:
			NetMode = ECommonSessionOnlineMode::LAN;
			break;
		case ECommonSessionOnlineMode::LAN:
			NetMode = ECommonSessionOnlineMode::Online;
			break;
		case ECommonSessionOnlineMode::Online:
			NetMode = ECommonSessionOnlineMode::Offline;
			break;
		default:NetMode = ECommonSessionOnlineMode::LAN;
	}

	if(NetworkModeText)
	{
		NetworkModeText->SetText(UEnum::GetDisplayValueAsText(NetMode));
	}
}


