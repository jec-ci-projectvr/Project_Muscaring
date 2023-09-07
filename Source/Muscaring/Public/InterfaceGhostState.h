// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enum_GhostState.h"
//#include "NormalGhost.h"
#include "RestArea.h"
#include "InterfaceGhostState.generated.h"
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceGhostState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MUSCARING_API IInterfaceGhostState
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//‰¼ŽÀ‘•
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GhostState")
		void SetGhostState(GhostState state);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GhostState")
		void SetMostNearRestArea(ARestArea* restArea);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GhostState")
		void SetHitInfo(bool hit);
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GhostState")
		void SetSecondNearRestArea(ARestArea* restArea);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GhostState")
		void SetEndRestArea(ARestArea* restArea);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GhostState")
		void SetFakeOut(bool isFakeOut);
};
