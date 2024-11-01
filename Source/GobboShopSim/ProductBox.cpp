// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductBox.h"

// Sets default values
AProductBox::AProductBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Box Mesh"));

	BoxMat = CreateDefaultSubobject<UMaterial>(TEXT("Base Box Mat"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>BoxMeshCheck(TEXT("/Game/ProductBox/ProductBox"));

	static ConstructorHelpers::FObjectFinder<UMaterial>BoxMatCheck(TEXT("/Game/ProductBox/M_ProductBox"));

	if (BoxMeshCheck.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxMeshCheck.Object);
	}
	if (BoxMeshCheck.Succeeded())
	{
		BoxMat = BoxMatCheck.Object;

		BoxMesh->SetMaterial(0, BoxMat);
	}

	BoxMesh->SetRelativeScale3D(FVector(2, 2, 0.1));

	CurrentProduct = EProductList::EMPTY;

	CurrentTotal = 7;

}

// Called when the game starts or when spawned
void AProductBox::BeginPlay()
{
	Super::BeginPlay();

	SpawnItems();
	
}

void AProductBox::SpawnItems()
{
	SpawnLoc = this->GetActorLocation();
	SpawnLoc.Z += 25;
	//SpawnLoc.Y -= 50;

	for (int i = 0; i < 8; i++)
	{
		if (ProductsOnDisplay[i])
		{
			ProductsOnDisplay[i]->BinProduct();
		}
	}


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			switch (CurrentProduct)
			{
			case EProductList::EMPTY:
				ProductsOnDisplay[i] = (AProduct*)GetWorld()->SpawnActor(AProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
				break;

			case EProductList::FROGSPAWN:
				ProductsOnDisplay[i] = (AFrogspawnProduct*)GetWorld()->SpawnActor(AFrogspawnProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
				break;

			case EProductList::MUSHROOM:
				ProductsOnDisplay[i] = (AMushroomProduct*)GetWorld()->SpawnActor(AMushroomProduct::StaticClass(), &SpawnLoc, &SpawnRot, SpawnParams);
				break;
			}




			SpawnLoc.Y += 20;
		}
		SpawnLoc.X += 25;
		SpawnLoc.Y -= 100;
	}
}

// Called every frame
void AProductBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnItems();
}

AProduct* AProductBox::GetProduct()
{
	//CurrentTotal--;
	return ProductsOnDisplay[0];
}

void AProductBox::SetProduct(AProduct* product)
{
	//CurrentTotal++;
	ProductsOnDisplay[0] = product;
}
