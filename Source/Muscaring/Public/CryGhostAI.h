// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GhostAI.h"
#include "CryGhostAI.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ACryGhostAI : public AGhostAI
{
	GENERATED_BODY()
public:
	ACryGhostAI();
private:

	//AIÇÃpawnÇï€éù
	virtual void OnPossess(APawn* InPawn) override;

	//AIÇÃpawnÇâèú
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
};
