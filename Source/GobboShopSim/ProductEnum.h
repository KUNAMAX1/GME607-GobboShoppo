#pragma once

#include "CoreMinimal.h"
#include "ProductEnum.generated.h"

UENUM(BlueprintType) 
enum class EProductList : uint8 {
    EMPTY UMETA(DisplayName = "EMPTY"),
    FORTNITE UMETA(DisplayName = "FORTNITE"),
    NOMANSSKY UMETA(DisplayName = "NOMANSSKY"),
    OUTERWILDS UMETA(DisplayName = "OUTERWILDS")
};
