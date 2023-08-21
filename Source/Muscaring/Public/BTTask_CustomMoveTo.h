// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_CustomMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API UBTTask_CustomMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
    UBTTask_CustomMoveTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
