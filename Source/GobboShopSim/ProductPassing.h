// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Product.h"
#include "ProductPassing.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProductPassing : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GOBBOSHOPSIM_API IProductPassing
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetProduct(AProduct* product) = 0;
	virtual AProduct* GetProduct() = 0;
};
