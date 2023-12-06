// Hello :)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MPGameState.generated.h"

class UCommonActivatableWidget;
class UMPGameData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateReadyDelegate);
UCLASS()
class MULTIPLAYERPLUGINMENU_API AMPGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AMPGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void SetGameData(UMPGameData* NewGameData);
	bool bShouldShowMenu()const;
	TSoftClassPtr<UCommonActivatableWidget> GetMenuClass() const;
	 

	FOnGameStateReadyDelegate OnGameStateReady;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_GameData();

	UPROPERTY(ReplicatedUsing = OnRep_GameData)
	UMPGameData* GameData;
	
};
