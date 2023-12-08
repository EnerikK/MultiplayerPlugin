// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MPMenuHostSessionWidget.generated.h"

class UCommonSession_HostSessionRequest;
struct FOnlineResultInformation;
enum class ECommonUserPrivilege;
enum class ECommonUserOnlineContext : uint8;
class UCommonUserInfo;
enum class ECommonSessionOnlineMode : uint8;
class UMPButtonBaseWidget;
class UCommonTextBlock;
class UMPGameDisplayListWidget;

UENUM()
enum ESetting1
{
	Set1,
	Set2,
};
UENUM()
enum ESetting2
{
	Set3,
	Set4,
};

UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPMenuHostSessionWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

protected:

	void InitTextDisplay()const;

	void AttemptOnlineLogin();
	void HostSession();
	UCommonSession_HostSessionRequest* CreateHostingRequest() const;

	UFUNCTION()
	void OnUserOnlineLogin(const UCommonUserInfo* UserInfo,bool bSuccess,FText Error,ECommonUserPrivilege RequestedPrivilege,ECommonUserOnlineContext OnlineContent);

	UFUNCTION()
	void OnSessionCreated(const FOnlineResultInformation& Result);
	
	UFUNCTION()
	void OnLaunchGame();
	
	UFUNCTION()
	void OnBackButton();
	
	UFUNCTION()
	void OnGameListCreated();
	
	UFUNCTION()
	void OnGameSelected(const FPrimaryAssetId& SelectedGameData);
	
	UPROPERTY()
	FPrimaryAssetId GameDataId;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPGameDisplayListWidget* GameList;
	
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* SelectedGameTitleText;
	
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* LaunchButton;
	
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* BackButton;

	/*General Settings*/
	UPROPERTY()
	TEnumAsByte<ESetting1> Setting1;

	UPROPERTY()
	TEnumAsByte<ESetting2> Setting2;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* GameSetting1Text;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* ChangeSetting1Button;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* GameSetting2Text;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* ChangeSetting2Button;
	
	/*Net mode settings*/

	UFUNCTION()
	void OnNetworkModeButtonClicked();
	
	UFUNCTION()
	void OnSetting1Changed();
	
	UFUNCTION()
	void OnSetting2Changed();
	
	UPROPERTY()
	ECommonSessionOnlineMode NetMode;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonTextBlock* NetworkModeText;
	
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* ChangeNetModeButton;

};


