// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MovePointManagerSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API UMovePointManagerSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
    TArray<TObjectPtr<AActor>> movePoints;

public:
	TArray<TObjectPtr<AActor>> GetMovePoints() { return movePoints; }
	void AddMovePoint(TObjectPtr<AActor> movePoint) { movePoints.Add(movePoint); }
};
