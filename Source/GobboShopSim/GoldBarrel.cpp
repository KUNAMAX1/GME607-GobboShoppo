// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldBarrel.h"

// Sets default values
AGoldBarrel::AGoldBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Shelf Mesh"));

	BarrelMat = CreateDefaultSubobject<UMaterial>(TEXT("Base Shelf Mat"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>BarrelMeshCheck(TEXT("/Game/DungPack/Barrel/Barrel"));

	static ConstructorHelpers::FObjectFinder<UMaterial>BarrelMatCheck(TEXT("/Game/DungPack/Barrel/M_Barrel"));

	if (BarrelMeshCheck.Succeeded())
	{
		BarrelMesh->SetStaticMesh(BarrelMeshCheck.Object);
	}
	if (BarrelMatCheck.Succeeded())
	{
		BarrelMat = BarrelMatCheck.Object;

		BarrelMesh->SetMaterial(0, BarrelMat);
	}

	TotalGoldEarned = 0;
}

// Called when the game starts or when spawned
void AGoldBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoldBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoldBarrel::AddGoldToBarrel(int AddGold)
{
	TotalGoldEarned += AddGold;

	if (GEngine) GEngine->AddOnScreenDebugMessage(10, 2.f, FColor::Cyan, FString::Printf(TEXT("I have %d in my barrel"), TotalGoldEarned));
}

