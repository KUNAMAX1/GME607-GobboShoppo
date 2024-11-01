// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogspawnProduct.h"

AFrogspawnProduct::AFrogspawnProduct()
{

	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterial>FrogMatCheck(TEXT("/Game/Product/M_FrogSpawn"));

	
	if (FrogMatCheck.Succeeded())
	{
		FrogspawnMat = FrogMatCheck.Object;

		BaseProductMesh->SetMaterial(0, FrogspawnMat);
	}

	ProductLabel = "FROGSPAWN";
}
