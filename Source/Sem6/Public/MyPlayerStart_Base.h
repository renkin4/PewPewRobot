// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "MyPlayerStart_Base.generated.h"

class ASpawnPoint_Base;
/**
 * 
 */
UCLASS()
class SEM6_API AMyPlayerStart_Base : public APlayerStart
{
	GENERATED_UCLASS_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "SpawnBase")
	ASpawnPoint_Base* SpawnPointBase;

	bool bIsOwned;

	uint8 TeamNum;

	/*Owner Controller*/
	APlayerController* PController;

public:
	UFUNCTION(BlueprintCallable, Category = "SpawnBase")
	void SetSpawnPointBase(ASpawnPoint_Base * SpawnBaseToSet);

	UFUNCTION(BlueprintPure, Category = "SpawnBase")
	ASpawnPoint_Base* GetSpawnPointBase();

	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeamNum(uint8 SetTeamNum);

	UFUNCTION(BlueprintPure, Category = "Team")
	uint8 GetTeamNum();

	UFUNCTION(BlueprintPure, Category = "Team")
	bool GetbIsOwned();

	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetbIsOwned(bool bSetIsOwned);

	UFUNCTION(BlueprintPure, Category = "Controller")
	APlayerController* GetPController();

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void SetPController(APlayerController* Controller);

	
	
};
