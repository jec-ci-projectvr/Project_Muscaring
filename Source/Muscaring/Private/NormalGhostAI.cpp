// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhostAI.h"
#include "UObject/ConstructorHelpers.h"

//コンストラクタ
ANormalGhostAI::ANormalGhostAI(const class FObjectInitializer& ObjectInitializer)
{
	this->BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	this->BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	//作成したbihaviorTreeを読み込む
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Characters/Ghosts/AI/BT_NormalGhost"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	this->TargetKey = "Target";
}
//BeginPlay
void ANormalGhostAI::BeginPlay()
{
	Super::BeginPlay();
}
//AIのpawnを保持
void ANormalGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Pawnを所持したらBehaviorTreeとBlackboardを使用
	if (BehaviorTree != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}
}
//AIのpawnを解除
void ANormalGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	BehaviorTreeComp->StopTree();
}
//プレイヤーのkeyを設定
void ANormalGhostAI::SetPlayerKey(APawn* InPawn)
{
	ensure(this->BlackboardComp);

	//blackboardのTargetというKeyにプレイヤーのpawnを設定
	this->BlackboardComp->SetValueAsObject(this->TargetKey, InPawn);
}
//プレイヤーのkeyを取得
ANormalGhostAI* ANormalGhostAI::GetPlayerKey() const
{
	ensure(this->BlackboardComp);

	//blackboardのTargetというKeyにプレイヤーのpawnを設定
	return Cast<ANormalGhostAI>(this->BlackboardComp->GetValueAsObject(this->TargetKey));
}

