// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonListView.h"
#include "MPMenuJoinSessionWidget.generated.h"

class UCommonBorder;
class UMPButtonBaseWidget;
class UCommonSession_SearchSessionRequest;
/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERPLUGINMENU_API UMPMenuJoinSessionWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

protected:

	void StartSearch();
	void SetSpinnerDisplay(const bool bSpinnerState)const;

	UFUNCTION()
	void OnRefreshList();

	UFUNCTION()
	void OnSessionSearchComplete(bool bSucceeded,const FText& ErrorMessage,UCommonSession_SearchSessionRequest* SessionSearchSessionRequest);

	UFUNCTION()
	void OnBackMenu();

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonListView* ListView;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* RefreshButton;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UMPButtonBaseWidget* BackButton;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonBorder* NoSessionsDisplay;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UCommonBorder* SpinnerDisplay;

	UPROPERTY()
	bool bSearchInProgress = false;

};
