// Copyright Carter Wooton

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UAbilityInfo;
class UCharacterClassInfo;
class UMVVM_LoadSlot;
class USaveGame;
class ULoadScreenSaveGame;
class ULootTiers;

/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Loot Tiers")
	TObjectPtr<ULootTiers> LootTiers;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);
	static void DeleteSaveSlot(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);
	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex);
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	ULoadScreenSaveGame* RetrieveInGameSaveData();
	void SaveInGameProgressData(ULoadScreenSaveGame* SaveObject);
	void SaveWorldState(UWorld* World, const FString& DestinationMapAssetName = FString(""));
	void LoadWorldState(UWorld* World);
	void PlayerDied(ACharacter* DeadCharacter);

	/* Maps */
	UPROPERTY(EditDefaultsOnly)
	FString StartingMapName;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> StartingMap;
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> GameMaps;
	FString GetMapNameFromMapAssetName(const FString& MapAssetName) const;
	void TravelToMap(UMVVM_LoadSlot* Slot);

	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

protected:
	virtual void BeginPlay() override;
};
