// Fill out your copyright notice in the Description page of Project Settings.


#include "Product.h"

// Sets default values
AProduct::AProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	

	BaseProductMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Shelf Mesh"));

	BaseProductMat = CreateDefaultSubobject<UMaterial>(TEXT("Base Shelf Mat"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ProdMeshCheck(TEXT("/Game/Product/BaseProduct"));

	static ConstructorHelpers::FObjectFinder<UMaterial>ProdMatCheck(TEXT("/Game/Product/M_BaseProduct"));

	if (ProdMeshCheck.Succeeded())
	{
		BaseProductMesh->SetStaticMesh(ProdMeshCheck.Object);
	}
	if (ProdMatCheck.Succeeded())
	{
		BaseProductMat = ProdMatCheck.Object;

		BaseProductMesh->SetMaterial(0, BaseProductMat);
	}

	ProductLabel = EProductList::EMPTY;
	ProductPrice = 0;

	BaseProductMesh->SetRelativeScale3D(FVector(4, 4, 4));
	BaseProductMesh->SetVisibility(false);

	BaseProductMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//BaseProductMesh->SetSimulatePhysics(true);

}

FString AProduct::GetLabel()
{
	FString DebugMessageLabel;

	switch (ProductLabel)
	{
	case EProductList::EMPTY:
		DebugMessageLabel = "EMPTY";
		break;

	case EProductList::FORTNITE:
		DebugMessageLabel = "FORTNITE";
		break;

	case EProductList::NOMANSSKY:
		DebugMessageLabel = "NOMANSKY";
		break;

	case EProductList::OUTERWILDS:
		DebugMessageLabel = "OUTERWILDS";
		break;
	default:
		DebugMessageLabel = "Read Enum Display Error";
		break;

	}

	return DebugMessageLabel;
}

EProductList AProduct::GetEnum()
{
	return ProductLabel;
}

// Called when the game starts or when spawned
void AProduct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProduct::BinProduct()
{
	Destroy();
}

int AProduct::GetProductPrice()
{
	return ProductPrice;
}

