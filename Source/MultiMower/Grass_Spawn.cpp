// Fill out your copyright notice in the Description page of Project Settings.


#include "Grass_Spawn.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AGrass_Spawn::AGrass_Spawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setup members
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void AGrass_Spawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}
}

void AGrass_Spawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//remove all timers associated with this object
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}


bool AGrass_Spawn::SpawnActor()
{
	bool SpawnedActor = false;
	if (ActorClassToBeSpawned)
	{
		// Calculating box
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		// compute random position in box
		FVector SpawnLocation = BoxBounds.Origin;
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();

		// compute random rotation
		FRotator SpawnRotation = FRotator::MakeFromEuler(FVector(
			(0),(0),FMath::RandRange(0.0f, 360.0f)
		));

		//Spawn actor
		SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClassToBeSpawned, SpawnLocation, SpawnRotation) != nullptr;
	}
	return SpawnedActor;
}

void AGrass_Spawn::EnableActorSpawning(bool Enable)
{
	//update internal state
	ShouldSpawn = Enable;

	//Check which time should be used
	if (Enable)
	{
		ScheduleActorSpawn();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}



void AGrass_Spawn::ScheduleActorSpawn()
{
	//time to spawn
	float DeltaToNextSpawn = 0.00000001f;

	//Schedule spawning
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AGrass_Spawn::SpawnActorScheduled, DeltaToNextSpawn, false);
}

void AGrass_Spawn::SpawnActorScheduled()
{
	if (SpawnGolden == false) 
	{
		for (int i = 0; i < 500; i++)
		{
			//Spawn and reschedule if needed
			if (SpawnActor())
			{
				if (ShouldSpawn)
				{
					ScheduleActorSpawn();
				}
			}
			else
			{
				//log error
			}
		}
	}
	else if (SpawnGolden == true)
	{
		//Spawn and reschedule if needed
		if (SpawnActor())
		{
			if (ShouldSpawn)
			{
				ScheduleActorSpawn();
			}
		}
		else
		{
			//log error
		}
	}

}

