// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MPButtonGameWidget.h"
#include "MPGameDisplayWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSelectDisplayDelegate, const FPrimaryAssetId&, SelectedGameData);

UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPGameDisplayWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	void SetGameData(const FPrimaryAssetId& Data);
	FPrimaryAssetId GetGameDataAsset() const {return GameDataId;}

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonGameWidget* GameButtonWidget;
	
	FOnGameSelectDisplayDelegate OnGameDisplaySelected;

protected:

	UFUNCTION()
	void OnGameSelection();

	UPROPERTY()
	FPrimaryAssetId GameDataId;
	
};
