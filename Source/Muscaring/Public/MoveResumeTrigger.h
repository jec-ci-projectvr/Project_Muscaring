// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoveResumeTrigger.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMoveResumeTrigger : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MUSCARING_API IMoveResumeTrigger
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MoveResumeTrigger")
	bool IsResumeTrigger();
};

