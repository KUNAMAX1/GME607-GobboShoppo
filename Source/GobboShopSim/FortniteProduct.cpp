// Fill out your copyright notice in the Description page of Project Settings.


#include "FortniteProduct.h"

AFortniteProduct::AFortniteProduct()
{
	PrimaryActorTick.bCanEverTick = false;

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>FortniteMeshCheck(TEXT("/Game/Product/FortniteIan/Fortnite"));

	static ConstructorHelpers::FObjectFinder<UMaterial>FortniteMatCheck(TEXT("/Game/Product/FortniteIan/M_Fortnite"));

	if (FortniteMeshCheck.Succeeded())
	{
		BaseProductMesh->SetStaticMesh(FortniteMeshCheck.Object);

		
	}
	if (FortniteMatCheck.Succeeded())
	{
		BaseProductMat = FortniteMatCheck.Object;

		BaseProductMesh->SetMaterial(0, BaseProductMat);
	}

	

	ProductLabel = EProductList::FORTNITE;
	ProductPrice = 39;
	
	BaseProductMesh->SetRelativeScale3D(FVector(4, 4, 4));
}
