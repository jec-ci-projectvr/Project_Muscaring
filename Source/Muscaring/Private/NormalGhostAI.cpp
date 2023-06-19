// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhostAI.h"
#include "UObject/ConstructorHelpers.h"

//�R���X�g���N�^
ANormalGhostAI::ANormalGhostAI(const class FObjectInitializer& ObjectInitializer)
{
	this->BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	this->BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	//�쐬����bihaviorTree��ǂݍ���
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
//AI��pawn��ێ�
void ANormalGhostAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Pawn������������BehaviorTree��Blackboard���g�p
	if (BehaviorTree != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
		BehaviorTreeComp->StartTree(*BehaviorTree);
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

