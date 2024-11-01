// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductShelf.h"

// Sets default values
AProductShelf::AProductShelf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShelfMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Shelf Mesh"));

	ShelfMat = CreateDefaultSubobject<UMaterial>(TEXT("Base Shelf Mat"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ShelfMeshCheck(TEXT("/Game/ProductShelf/ProductShelf"));

	static ConstructorHelpers::FObjectFinder<UMaterial>ShelfMatCheck(TEXT("/Game/ProductShelf/M_ProductShelf"));

	if (ShelfMeshCheck.Succeeded())
	{
		ShelfMesh->SetStaticMesh(ShelfMeshCheck.Object);
	}
	if (ShelfMatCheck.Succeeded())
	{
		ShelfMat = ShelfMatCheck.Object;

		ShelfMesh->SetMaterial(0, ShelfMat);
	}

	ShelfMesh->SetRelativeScale3D(FVector(2, 4, 1));

	
}

// Called when the game starts or when spawned
void AProductShelf::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnLoc = this->GetActorLocation();
	SpawnLoc.Z += 65;
	SpawnLoc.Y -= 75;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ProductsOnDisplay[i] = (AProduct*)GetWorld()->SpawnActor(AProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
			SpawnLoc.Y += 40;
		}
		SpawnLoc.X += 45;
		SpawnLoc.Y -= 100;
	}
}

// Called every frame
void AProductShelf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

