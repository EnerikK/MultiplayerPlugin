// Hello :)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPGameMode.generated.h"

class AMPPlayerController;
class UMPGameData;
/**
 * 
 */
UCLASS()
class MULTIPLAYERPLUGINMENU_API AMPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMPGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitGameState() override;
	virtual void GenericPlayerInitialization(AController* NewPlayer) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;
	virtual void FailedToRestartPlayer(AController* NewPlayer) override;
	void RequestPlayerRestartNextFrame(AController* Controller,bool bForceReset = false);
	

protected:

	void HandleGameDataAssignment();
	void OnGameDataAssignment();
	void OnGameDataLoaded();
	bool IsGameDataLoaded() const {return CurrentGameDataAssetId.IsValid();}
	UMPGameData* GetGameData() const;
	

	UFUNCTION()
	void OnGameReady();

	void InitializePlayer();

	UPROPERTY()
	bool bGameReady = false;

	UPROPERTY()
	FPrimaryAssetId CurrentGameDataAssetId;

	UPROPERTY()
	TArray<AMPPlayerController*>  SessionPlayers;
	
};
