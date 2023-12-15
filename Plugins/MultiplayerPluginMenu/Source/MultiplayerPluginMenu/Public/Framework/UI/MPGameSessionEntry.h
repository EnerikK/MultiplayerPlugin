// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "MPGameSessionEntry.generated.h"

class UCommonSession_SearchResult;
class UMPGameSessionButton;
struct FOnlineResultInformation;
/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPGameSessionEntry : public UCommonTabListWidgetBase,public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:

	void OnSessionSelected();
	void OnJoinSessionComplete(const FOnlineResultInformation& Result);

	UFUNCTION()
	void OnGameDataLoaded();

	UPROPERTY()
	UCommonSession_SearchResult* SessionSearchResult;

	UPROPERTY()
	FPrimaryAssetId GameDataId;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPGameSessionButton* SessionButton;

	FDelegateHandle JoinSessionHandle;
	
};
