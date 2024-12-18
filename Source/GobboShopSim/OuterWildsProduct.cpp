// Fill out your copyright notice in the Description page of Project Settings.


#include "OuterWildsProduct.h"

AOuterWildsProduct::AOuterWildsProduct()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh>OuterWildsMeshCheck(TEXT("/Game/Product/OuterWildsMax/OuterWilds"));

	static ConstructorHelpers::FObjectFinder<UMaterial>OutWildsMatCheck(TEXT("/Game/Product/OuterWildsMax/M_OuterWilds"));

	if (OuterWildsMeshCheck.Succeeded())
	{
		BaseProductMesh->SetStaticMesh(OuterWildsMeshCheck.Object);


	}
	if (OutWildsMatCheck.Succeeded())
	{
		BaseProductMat = OutWildsMatCheck.Object;

		BaseProductMesh->SetMaterial(0, BaseProductMat);
	}



	ProductLabel = EProductList::OUTERWILDS;
	ProductPrice = 14;

	BaseProductMesh->SetRelativeScale3D(FVector(0.8, 0.8, 0.8));
	BaseProductMesh->SetVisibility(true);
}
