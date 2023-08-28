// Fill out your copyright notice in the Description page of Project Settings.


#include "NaughtyGhostAI.h"

ANaughtyGhostAI::ANaughtyGhostAI()
	:AGhostAI()
{
	//ì¬‚µ‚½bihaviorTree‚ğ“Ç‚İ‚Ş
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Characters/Ghosts/AI/BT_NaughtyGhost"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}
}
void ANaughtyGhostAI::BeginPlay()
{
	Super::BeginPlay();
}
void ANaughtyGhostAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
void ANaughtyGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
void ANaughtyGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	GetBehaviorTreeComp()->StopTree();
}