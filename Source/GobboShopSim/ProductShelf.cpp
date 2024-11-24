// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductShelf.h"

// Sets default values
AProductShelf::AProductShelf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShelfMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Shelf Mesh"));

	ShelfMat = CreateDefaultSubobject<UMaterial>(TEXT("Base Shelf Mat"));



	static ConstructorHelpers::FObjectFinder<UStaticMesh>ShelfMeshCheck(TEXT("/Game/DungPack/Table/Table"));

	static ConstructorHelpers::FObjectFinder<UMaterial>ShelfMatCheck(TEXT("/Game/DungPack/Table/M_Table"));



	if (ShelfMeshCheck.Succeeded())
	{
		ShelfMesh->SetStaticMesh(ShelfMeshCheck.Object);
	}
	if (ShelfMatCheck.Succeeded())
	{
		ShelfMat = ShelfMatCheck.Object;

		ShelfMesh->SetMaterial(0, ShelfMat);
	}

	CurrentProduct = EProductList::EMPTY;

	CurrentProductIndex = NO_OF_PRODUCTS - 1;


}

// Called when the game starts or when spawned
void AProductShelf::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < NO_OF_PRODUCTS; i++)
	{
		switch (CurrentProduct)
		{
		case EProductList::EMPTY:
			ProductsOnDisplay[i] = (AProduct*)GetWorld()->SpawnActor(AProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
			break;

		case EProductList::FORTNITE:
			ProductsOnDisplay[i] = (AFortniteProduct*)GetWorld()->SpawnActor(AFortniteProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
			break;
		case EProductList::NOMANSSKY:
			ProductsOnDisplay[i] = (ANoMansSkyProduct*)GetWorld()->SpawnActor(ANoMansSkyProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
			break;

		case EProductList::OUTERWILDS:
			ProductsOnDisplay[i] = (AOuterWildsProduct*)GetWorld()->SpawnActor(AOuterWildsProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
			break;


		}

	}
	ResetProductPositions();
}

// Called every frame
void AProductShelf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AProduct* AProductShelf::GetProduct()
{
	AProduct* ReturningProduct;

	if (CurrentProductIndex >= 0 && CurrentProductIndex < NO_OF_PRODUCTS)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Product Index no. %d"), CurrentProductIndex));

		ReturningProduct = ProductsOnDisplay[CurrentProductIndex];

		CurrentProductIndex--;

	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Index out of Array"));
		CurrentProductIndex = NO_OF_PRODUCTS - 1;
		ReturningProduct = nullptr;
	}

	return ReturningProduct;
}

void AProductShelf::SetProduct(AProduct* product)
{
	ProductsOnDisplay[CurrentProductIndex + 1] = product;
	ResetProductPositions();
}

void AProductShelf::ResetProductPositions()
{
	SpawnLoc = this->GetActorLocation();
	SpawnLoc.Z += 100;
	SpawnLoc.Y -= 75;



	int SpawnLoopIterator = 0;

	for (int i = 0; i < (NO_OF_PRODUCTS / 4); i++)
	{
		for (int j = 0; j < (NO_OF_PRODUCTS / 2); j++)
		{
			if (ProductsOnDisplay[SpawnLoopIterator])
			{
				ProductsOnDisplay[SpawnLoopIterator]->SetActorLocation(SpawnLoc);
				ProductsOnDisplay[SpawnLoopIterator]->SetActorRotation(SpawnRot);
				SpawnLoopIterator++;
			}

			SpawnLoc.Y += 40;
		}
		SpawnLoc.X += 45;
		SpawnLoc.Y -= 100;

	}

}

void AProductShelf::ProductTaken(int ProductIndex)
{
	ProductsOnDisplay[ProductIndex]->Destroy();

	ProductsOnDisplay[ProductIndex] = (AProduct*)GetWorld()->SpawnActor(AProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
	ResetProductPositions();
}

