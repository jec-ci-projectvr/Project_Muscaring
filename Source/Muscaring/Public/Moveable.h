// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Moveable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMoveable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MUSCARING_API IMoveable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Moveable")
	void Move(FVector direction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Moveable")
	void SetDirection(FVector direction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Moveable")
	FVector GetDirection();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Moveable")
	void SetSpeed(float speed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Moveable")
	float GetSpeed();
};
