// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhostAI.h"
#include "GhostAI.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


//コンストラクタ
ANormalGhostAI::ANormalGhostAI()
	:AGhostAI()
{
	//作成したbihaviorTreeを読み込む
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Characters/Ghosts/AI/BT_NormalGhost"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}
}
//BeginPlay
void ANormalGhostAI::BeginPlay()
{
	Super::BeginPlay();

}
//Tick
void ANormalGhostAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
//AIのpawnを保持
void ANormalGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
//AIのpawnを解除
void ANormalGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	GetBehaviorTreeComp()->StopTree();
}

