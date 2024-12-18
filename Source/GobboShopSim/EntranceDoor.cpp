// Fill out your copyright notice in the Description page of Project Settings.

#include "EntranceDoor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEntranceDoor::AEntranceDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GobboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));

	GobboMat = CreateDefaultSubobject<UMaterial>(TEXT("Door Mat"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorCheck(TEXT("/Game/DungPack/Door/Door"));

	static ConstructorHelpers::FObjectFinder<UMaterial>DoorMatCheck(TEXT("/Game/DungPack/Door/M_Door"));

	if (DoorCheck.Succeeded())
	{
		GobboMesh->SetStaticMesh(DoorCheck.Object);
	}
	if (DoorMatCheck.Succeeded())
	{
		GobboMat = DoorMatCheck.Object;

		GobboMesh->SetMaterial(0, GobboMat);
	}

	if (bGobboSpawner)
	{

		GobboSpawnTimer = 10;
	}

}

// Called when the game starts or when spawned
void AEntranceDoor::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<AActor> WorldShelfObject = AProductShelf::StaticClass();

	UGameplayStatics::GetAllActorsOfClass(this, WorldShelfObject, CurrentShelfActors);

	if (GEngine) GEngine->AddOnScreenDebugMessage(9, 2.f, FColor::Magenta, FString::Printf(TEXT("Door can see %d Shelves"), CurrentShelfLayout.Num()));

	for (AActor* Actor : CurrentShelfActors)
	{
		AProductShelf* ProductShelf = Cast<AProductShelf>(Actor);
		if (ProductShelf)
		{
			CurrentShelfLayout.Add(ProductShelf);
		}
	}

	TSubclassOf<AActor> WorldBarrelObject = AGoldBarrel::StaticClass();

	TArray<AActor*> GoldBarrels;

	UGameplayStatics::GetAllActorsOfClass(this, WorldBarrelObject, GoldBarrels);

	if (GoldBarrels[0])
	{
		GoldBarrel = Cast<AGoldBarrel>(GoldBarrels[0]);
	}

	
	
}

void AEntranceDoor::GobboSpawn()
{
	SpawnLoc = this->GetActorLocation();

	GobboShoppers.Add((AGobbo*)GetWorld()->SpawnActor(AGobbo::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams));

	GobboShoppers.Last()->SetGobboSeenShelves(CurrentShelfLayout);

	GobboShoppers.Last()->SetPayPoint(GoldBarrel);

	GobboShoppers.Last()->PrintGobboSeenShelves();
	
}

// Called every frame
void AEntranceDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGobboSpawner)
	{
		GobboSpawnTimer--;

		if (GobboSpawnTimer < 5)
		{
			GobboSpawn();

			GobboSpawnTimer = GobboSpawnMult * FMath::RandRange(60, 120);

		}

	}

}

