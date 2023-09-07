// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostAI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


//コンストラクタ
AGhostAI::AGhostAI()
	:targetKey_("Target"), selfActorKey_("SelfActor"), ghostStateKey_("GhostState"),mostNearRestAreaKey_("RestArea")
	,secondNearRestAreaKey_("SecondRestArea"),endRestAreaKey_("EndRestArea") ,hitKey_("Hit"),FakeOutKey_("FakeOut")
{
	//AIControllerを作成
	this->behaviorTreeComp_ = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	this->blackboardComp_ = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	
}
void AGhostAI::BeginPlay()
{
	Super::BeginPlay();
	PlayerActionEvent = Cast<UPlayerActionEvent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass(UPlayerActionEvent::StaticClass()));
}
//Tick
void AGhostAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
//AIのpawnを保持
void AGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Pawnを所持したらBehaviorTreeとBlackboardを使用
	if (behaviorTree_ != nullptr)
	{
		//BehaviorTreeComp->StartTree(*BehaviorTree);
		RunBehaviorTree(behaviorTree_);
		blackboardComp_->InitializeBlackboard(*(behaviorTree_->BlackboardAsset));
	}
}
//AIのpawnを解除
void AGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	behaviorTreeComp_->StopTree();
}
//プレイヤーのkeyを設定
void AGhostAI::SetPlayerKey(APawn* InPawn)
{
	ensure(this->blackboardComp_);

	//blackboardのTargetというKeyにプレイヤーのpawnを設定
	this->blackboardComp_->SetValueAsObject(this->targetKey_, InPawn);
}
//behaviorTreeのsetter
void AGhostAI::SetBehaviorTree(UBehaviorTree* behaviorTree)
{
	ensure(this->behaviorTreeComp_);
	this->behaviorTree_ = behaviorTree;
}
//behaviorTreeのgetter
UBehaviorTree* AGhostAI::GetBehaviorTree() const
{
	ensure(this->behaviorTree_);
	return this->behaviorTree_;
}
void AGhostAI::SetGhostState_Implementation(GhostState state)
{
	ensure(this->blackboardComp_);
	blackboardComp_->SetValueAsEnum(ghostStateKey_, (uint8)state);
}
void AGhostAI::SetMostNearRestArea_Implementation(ARestArea* restArea)
{
	if (restArea == nullptr)
		UKismetSystemLibrary::PrintString(GetWorld(), "error01");
	else
	UKismetSystemLibrary::PrintString(GetWorld(), "SetMostNearRestArea");
	ensure(this->blackboardComp_);
	blackboardComp_->SetValueAsObject(mostNearRestAreaKey_, restArea);
}
void AGhostAI::SetHitInfo_Implementation(bool hit)
{
	ensure(this->blackboardComp_);
	blackboardComp_->SetValueAsBool(hitKey_, true);
}
void AGhostAI::SetSecondNearRestArea_Implementation(ARestArea* restArea)
{
	if(restArea==nullptr)
		UKismetSystemLibrary::PrintString(GetWorld(), "error02");
	else
	UKismetSystemLibrary::PrintString(GetWorld(), "SetSecondNearRestArea");
	ensure(this->blackboardComp_);
	blackboardComp_->SetValueAsObject(secondNearRestAreaKey_, restArea);
}
void AGhostAI::SetEndRestArea_Implementation(ARestArea* restArea)
{
	ensure(this->blackboardComp_);
	blackboardComp_->SetValueAsObject(endRestAreaKey_, restArea);
}
void AGhostAI::SetFakeOut_Implementation(bool isFakeOut)
{
	ensure(this->blackboardComp_);
	blackboardComp_->SetValueAsBool(FakeOutKey_, isFakeOut);
}