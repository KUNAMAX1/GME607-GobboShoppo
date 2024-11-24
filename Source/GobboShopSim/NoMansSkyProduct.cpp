// Fill out your copyright notice in the Description page of Project Settings.


#include "NoMansSkyProduct.h"

ANoMansSkyProduct::ANoMansSkyProduct()
{
	PrimaryActorTick.bCanEverTick = false;


	static ConstructorHelpers::FObjectFinder<UStaticMesh>NoMansSkyMeshCheck(TEXT("/Game/Product/NoMansSkyMatt/NoMansSky"));

	static ConstructorHelpers::FObjectFinder<UMaterial>NoMansSkyMatCheck(TEXT("/Game/Product/NoMansSkyMatt/M_NoMansSky"));

	if (NoMansSkyMeshCheck.Succeeded())
	{
		BaseProductMesh->SetStaticMesh(NoMansSkyMeshCheck.Object);


	}
	if (NoMansSkyMatCheck.Succeeded())
	{
		BaseProductMat = NoMansSkyMatCheck.Object;

		BaseProductMesh->SetMaterial(0, BaseProductMat);
	}



	ProductLabel = EProductList::NOMANSSKY;
	ProductPrice = 29;

	BaseProductMesh->SetRelativeScale3D(FVector(4, 4, 4));

	
}
