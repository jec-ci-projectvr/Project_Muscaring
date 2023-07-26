// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhostAI.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

//�R���X�g���N�^
ANormalGhostAI::ANormalGhostAI(const class FObjectInitializer& ObjectInitializer)
{
	//AIController���쐬
	this->BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	this->BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	//�쐬����bihaviorTree��ǂݍ���
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
//AI��pawn��ێ�
void ANormalGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Pawn������������BehaviorTree��Blackboard���g�p
	if (BehaviorTree != nullptr)
	{
		//BehaviorTreeComp->StartTree(*BehaviorTree);
		RunBehaviorTree(BehaviorTree);
		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
	}
}
//AI��pawn������
void ANormalGhostAI::OnUnPossess()
{
	Super::OnUnPossess();
	BehaviorTreeComp->StopTree();
}
//�v���C���[��key��ݒ�
void ANormalGhostAI::SetPlayerKey(APawn* InPawn)
{
	ensure(this->BlackboardComp);

	//blackboard��Target�Ƃ���Key�Ƀv���C���[��pawn��ݒ�
	this->BlackboardComp->SetValueAsObject(this->TargetKey, InPawn);
}
//�v���C���[��key���擾
ANormalGhostAI* ANormalGhostAI::GetPlayerKey() const
{
	ensure(this->BlackboardComp);

	//blackboard��Target�Ƃ���Key�Ƀv���C���[��pawn��ݒ�
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

