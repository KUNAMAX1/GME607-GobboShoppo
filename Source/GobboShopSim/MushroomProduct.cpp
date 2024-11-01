// Fill out your copyright notice in the Description page of Project Settings.


#include "MushroomProduct.h"

AMushroomProduct::AMushroomProduct()
{

	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterial>MushMatCheck(TEXT("/Game/Product/M_Mushroom"));


	if (MushMatCheck.Succeeded())
	{
		MushroomMat = MushMatCheck.Object;

		BaseProductMesh->SetMaterial(0, MushroomMat);
	}

	ProductLabel = "MUSHROOM";
}
