// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Product.h"
#include "FortniteProduct.generated.h"

/**
 * 
 */
UCLASS()
class GOBBOSHOPSIM_API AFortniteProduct : public AProduct
{
	GENERATED_BODY()

public:
	AFortniteProduct();


private:

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class UStaticMeshComponent* FortniteMesh;

	UPROPERTY(VisibleAnywhere, Category = "Material")
		UMaterial* FortniteMat;
	
};
