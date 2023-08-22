// Fill out your copyright notice in the Description page of Project Settings.


#include "CryGhostAI.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GhostAI.h"
ACryGhostAI::ACryGhostAI()
	:AGhostAI()
{
	//çÏê¨ÇµÇΩbihaviorTreeÇì«Ç›çûÇﬁ
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Characters/Ghosts/AI/BT_CryGhost"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}
}
void ACryGhostAI::BeginPlay()
{
	Super::BeginPlay();
}
void ACryGhostAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
void ACryGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
void ACryGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	GetBehaviorTreeComp()->StopTree();
}