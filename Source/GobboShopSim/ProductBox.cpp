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

	CurrentProductIndex = NO_OF_PRODUCTS - 1;

}

// Called when the game starts or when spawned
void AProductBox::BeginPlay()
{
	Super::BeginPlay();

	SpawnItems();
	
}

void AProductBox::SpawnItems()
{

	for (int i = 0; i < NO_OF_PRODUCTS; i++)
	{
		if (ProductsOnDisplay[i])
		{
			ProductsOnDisplay[i]->BinProduct();
		}
	}


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
void AProductBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SpawnItems();
}

AProduct* AProductBox::GetProduct()
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
		ReturningProduct = nullptr;
		SpawnItems();
	}
	
	return ReturningProduct;
	
}

void AProductBox::SetProduct(AProduct* product)
{

	ProductsOnDisplay[CurrentProductIndex+1] = product;
	ResetProductPositions();
}

void AProductBox::ResetProductPositions()
{
	SpawnLoc = this->GetActorLocation();
	SpawnLoc.Z += 5;
	SpawnLoc.Y -= 70;
	SpawnLoc.X -= 10;


	int SpawnLoopIterator = 0;

	for (int i = 0; i < (NO_OF_PRODUCTS/4); i++)
	{
		for (int j = 0; j < (NO_OF_PRODUCTS/2); j++)
		{
			if (ProductsOnDisplay[SpawnLoopIterator])
			{

				ProductsOnDisplay[SpawnLoopIterator]->SetActorLocation(SpawnLoc);
				ProductsOnDisplay[SpawnLoopIterator]->SetActorRotation(SpawnRot);
				SpawnLoopIterator++;
			}
			
			SpawnLoc.Y += 35;
		}
		SpawnLoc.X += 40;
		SpawnLoc.Y -= 100;

	}

}


