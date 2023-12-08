// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MPGameDisplayListWidget.generated.h"

class UVerticalBox;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameListCreatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSelectedDelegate,const FPrimaryAssetId& , SelectedGameData);

UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPGameDisplayListWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	TArray<UWidget*> GetGameListWidgetList()const;

	FOnGameListCreatedDelegate OnGameListCreated;
	FOnGameSelectedDelegate OnGameSelected;

protected:
	void LoadGameList();
	void OnGameDataLoaded(TArray<FPrimaryAssetId> GameDataAssets);
	void OnGameListCreation();
	
	UFUNCTION()
	void OnGameDisplaySelection(const FPrimaryAssetId& SelectedGameData);
	
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UVerticalBox* GameList;

	UPROPERTY()
	UCommonUserWidget* GameDisplayWidgetClass;
};
