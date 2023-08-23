// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GhostAI.h"
#include "NaughtyGhostAI.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ANaughtyGhostAI : public AGhostAI
{
	GENERATED_BODY()
public:
	ANaughtyGhostAI();
private:

	//AIのpawnを保持
	virtual void OnPossess(APawn* InPawn) override;

	//AIのpawnを解除
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
};
