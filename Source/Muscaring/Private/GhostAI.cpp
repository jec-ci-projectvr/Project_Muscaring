// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GhostAI.h"

//�R���X�g���N�^
AGhostAI::AGhostAI(const class FObjectInitializer& ObjectInitializer)
	:targetKey_("Target"), selfActorKey_("SelfActor"), ghostStateKey_("GhostState")
	,mostNearRestAreaKey_("RestArea"),secondNearRestAreaKey_("SecondRestArea"), hitKey_("Hit")
{
	//AIController���쐬
	this->behaviorTreeComp_ = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	this->blackboardComp_ = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}
void AGhostAI::BeginPlay()
{
	Super::BeginPlay();
}
//Tick
void AGhostAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
//AI��pawn��ێ�
void AGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Pawn������������BehaviorTree��Blackboard���g�p
	if (behaviorTree_ != nullptr)
	{
		//BehaviorTreeComp->StartTree(*BehaviorTree);
		RunBehaviorTree(behaviorTree_);
		blackboardComp_->InitializeBlackboard(*(behaviorTree_->BlackboardAsset));
	}
}
//AI��pawn������
void AGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	behaviorTreeComp_->StopTree();
}
//�v���C���[��key��ݒ�
void AGhostAI::SetPlayerKey(APawn* InPawn)
{
	ensure(this->blackboardComp_);

	//blackboard��Target�Ƃ���Key�Ƀv���C���[��pawn��ݒ�
	this->blackboardComp_->SetValueAsObject(this->targetKey_, InPawn);
}
//behaviorTree��setter
void AGhostAI::SetBehaviorTree(UBehaviorTree* behaviorTree)
{
	ensure(this->behaviorTreeComp_);
	this->behaviorTree_ = behaviorTree;
}
//behaviorTree��getter
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
	ensure(this->blackboardComp_);
	blackboardComp_->SetValueAsObject(secondNearRestAreaKey_, restArea);
}