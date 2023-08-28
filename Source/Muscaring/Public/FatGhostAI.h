// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GhostAI.h"
#include "FatGhostAI.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API AFatGhostAI : public AGhostAI
{
	GENERATED_BODY()
public:
	AFatGhostAI();
private:

	//AI��pawn��ێ�
	virtual void OnPossess(APawn* InPawn) override;

	//AI��pawn������
	virtual void OnUnPossess() override;

	//BeginPlay
	virtual void BeginPlay() override;

	//Tick
	virtual void Tick(float DeltaSeconds) override;
};
