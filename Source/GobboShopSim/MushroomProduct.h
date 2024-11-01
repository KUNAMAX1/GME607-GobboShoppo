// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Product.h"
#include "MushroomProduct.generated.h"

/**
 * 
 */
UCLASS()
class GOBBOSHOPSIM_API AMushroomProduct : public AProduct
{
	GENERATED_BODY()
	

public:
	AMushroomProduct();


private:

	UPROPERTY(VisibleAnywhere, Category = "Material")
		UMaterial* MushroomMat;

};
