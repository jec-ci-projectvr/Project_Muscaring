// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NormalGhost.h"
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
	virtual ANormalGhost::GhostState SendGhostState(ANormalGhost::GhostState state);
	virtual ARestArea& SendMostNearRestArea(TObjectPtr<ARestArea> restArea);
	virtual bool SendHitInfo(bool hit);
};
