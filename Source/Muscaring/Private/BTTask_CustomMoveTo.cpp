// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CustomMoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DestroyedRestArea.h"
#include "BeginMoveToPlayer.h"
#include "Ghost.h"
#include "Kismet/GameplayStatics.h"

UBTTask_CustomMoveTo::UBTTask_CustomMoveTo()
{
	NodeName = TEXT("CustomMoveTo");

}
EBTNodeResult::Type UBTTask_CustomMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IBeginMoveToPlayer::Execute_BeginMoveToPlayer(OwnerComp.GetBlackboardComponent()->GetValueAsObject("SelfActor"));
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::InProgress;
}
void UBTTask_CustomMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);
}

