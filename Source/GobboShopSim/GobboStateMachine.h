// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gobbo.h"


/**
 * 
 */
class GOBBOSHOPSIM_API GobboStateMachine
{
private:
	AGobbo* GobboShopper;



public:
	GobboStateMachine(AGobbo* _Gobbo);
	~GobboStateMachine();
};
