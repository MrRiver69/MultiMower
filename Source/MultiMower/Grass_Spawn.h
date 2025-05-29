// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "Grass_Spawn.generated.h"

UCLASS()
class MULTIMOWER_API AGrass_Spawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrass_Spawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when actor stops playing
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	UFUNCTION(BlueprintCallable)
	bool SpawnActor();

	//Change if actors are spawned
	UFUNCTION(BlueprintCallable)
	void EnableActorSpawning(bool Enable);

private:
	UFUNCTION()
	void SpawnActorScheduled();

	//Schedule actor spawn
	void ScheduleActorSpawn();

public:
	// Actor class spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	// Time between spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 0.0001f;

	// Random +/- offset spawn time
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 0.00005f;

	//actor should spawn
	UPROPERTY(EditAnywhere)
	bool ShouldSpawn = true;

	//should spawn golden grass
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpawnGolden = true;

private:
	// Actor spawn area box
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;



	//timing aid
	FTimerHandle SpawnTimerHandle;

};
