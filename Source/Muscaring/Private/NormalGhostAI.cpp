// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhostAI.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

//コンストラクタ
ANormalGhostAI::ANormalGhostAI(const class FObjectInitializer& ObjectInitializer)
{
	//AIControllerを作成
	this->BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	this->BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	//作成したbihaviorTreeを読み込む
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Characters/Ghosts/AI/BT_NormalGhost"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
	TargetKey = "Target";
	SelfActorKey = "SelfActor";
    GhostStateKey = "GhostState";
	RestAreaKey = "RestArea";
	HitKey = "Hit";
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
	//Pawnを所持したらBehaviorTreeとBlackboardを使用
	if (BehaviorTree != nullptr)
	{
		//BehaviorTreeComp->StartTree(*BehaviorTree);
		RunBehaviorTree(BehaviorTree);
		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
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

void ANormalGhostAI::SetGhostState_Implementation(GhostState state)
{
	ensure(this->BlackboardComp);
	BlackboardComp->SetValueAsEnum(GhostStateKey,(uint8)state);
}
void ANormalGhostAI::SetMostNearRestArea_Implementation(ARestArea* restArea)
{
	ensure(this->BlackboardComp);
	BlackboardComp->SetValueAsObject(RestAreaKey, restArea);
}
void ANormalGhostAI::SetHitInfo_Implementation(bool hit)
{
	ensure(this->BlackboardComp);
	BlackboardComp->SetValueAsBool(HitKey, true);
}

