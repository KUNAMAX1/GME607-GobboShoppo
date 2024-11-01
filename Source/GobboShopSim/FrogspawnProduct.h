// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Product.h"
#include "FrogspawnProduct.generated.h"

/**
 * 
 */
UCLASS()
class GOBBOSHOPSIM_API AFrogspawnProduct : public AProduct
{
	GENERATED_BODY()
public:
	AFrogspawnProduct();

private:

	UPROPERTY(VisibleAnywhere, Category = "Material")
		UMaterial* FrogspawnMat;
	
};
