// Fill out your copyright notice in the Description page of Project Settings.


#include "FatGhostAI.h"

AFatGhostAI::AFatGhostAI()
	:AGhostAI()
{
	//�쐬����bihaviorTree��ǂݍ���
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Characters/Ghosts/AI/BT_FatGhost"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}
}
void AFatGhostAI::BeginPlay()
{
	Super::BeginPlay();
}
void AFatGhostAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
void AFatGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
void AFatGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	GetBehaviorTreeComp()->StopTree();
}