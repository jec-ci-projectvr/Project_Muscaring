// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhost.h"
#include "PerCeption/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Muscaring/Muscaring.h"
#include "Muscaring/Public/NormalGhostAI.h"
#include "Muscaring/Public/NormalGhost.h"
#include <Kismet/GameplayStatics.h>
#include "RestArea.h"
#include "Enum_GhostState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InterfaceGhostState.h"

// Sets default values
ANormalGhost::ANormalGhost()
	:state_(GhostState::Idle)
	, onSeeOnce_(false)
	, minimumDist(10000.f)
	, scarePoint_(0)
	, player(nullptr)
	, restArea(nullptr)
	, defaultMoveSpeed_(60.f)
	, escapeMoveSpeed_(90.f)
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	//����
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	//����̋���
	PawnSensingComp->SightRadius = 2000.0f;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ANormalGhost::OnSeePlayer);

	//player���̃C�x���g�Ɋ֐����o�C���h
	//������
}

// Called when the game starts or when spawned
void ANormalGhost::BeginPlay()
{
	Super::BeginPlay();
	//AI�R���g���[���[��ݒ�
	{
		normalGhostAI = Cast<ANormalGhostAI>(GetController());
	}
	//�v���C���[�̐ݒ�
	{
		player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//�v���C���[
		if (normalGhostAI && player)
		{
			//�v���C���[����ݒ�
			normalGhostAI->SetPlayerKey(player);
		}
	}
	//���x����ɑ��݂������̃A�N�^�[��S�Ď擾
	{
		
		SettingMostNearRestArea();
		IInterfaceGhostState::Execute_SetMostNearRestArea(normalGhostAI, restArea);
	}
}

// Called every frame
void ANormalGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ANormalGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//OtherActor���v���C���[��������interface�����s(player�̔��肪�����ł��邽�߈ꎞ�I�ɏ����𖳂���)
	IInterfaceGhostState::Execute_SetHitInfo(normalGhostAI, true);
}
//���I�f���Q�[�g�ŌĂяo���֐�
//�v���C���[�����������Ɉ�x�����Ăяo��
void ANormalGhost::OnSeePlayer(APawn* Pawn)
{
	//�v���C���[�����������Ɉ�x�����Ăяo��
	if (!onSeeOnce_)
	{
		scarePoint_+=10;
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetGhostState(normalGhostAI, state_);
		onSeeOnce_ = true;
	}
}

//defaultMoveSpeed��setter
void ANormalGhost::SetDefaultMoveSpeed(const float speed)
{
	defaultMoveSpeed_ = speed;
}
//defaultMoveSpeed��getter
float ANormalGhost::GetDefaultMoveSpeed() const
{
	return defaultMoveSpeed_;
}
//escapeMoveSpeed��setter
void ANormalGhost::SetEscapeMoveSpeed(const float speed)
{
	escapeMoveSpeed_ = speed;
}
//escapeMoveSpeed��getter
float ANormalGhost::GetEscapeMoveSpeed() const
{
	return escapeMoveSpeed_;
}
//scarePoint��setter
void ANormalGhost::SetScarePoint(const uint32 scarePoint)
{
	scarePoint_ = scarePoint;
}
//���|�l�ɉ����ď�Ԃ�ύX����
void ANormalGhost::ChangeState()
{
	if(scarePoint_<30)
	{
		state_ = GhostState::Approach;
	}
	else if(scarePoint_<60)
	{
		state_ = GhostState::Scare;
	}
	else if (scarePoint_<100)
	{
		state_ = GhostState::Escape;
	}
	else if (scarePoint_ >= 100)
	{
		state_ = GhostState::Swoon;
	}
}
//��Ԃɂ���Ĉړ����x��ω�������
void ANormalGhost::ChangeMoveSpeed()
{
	switch (state_)
	{
	case GhostState::Idle:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	case GhostState::Approach:
		GetCharacterMovement()->MaxWalkSpeed = defaultMoveSpeed_;
		break;
	case GhostState::Scare:
		GetCharacterMovement()->MaxWalkSpeed = defaultMoveSpeed_ / 2;
		break;
	case GhostState::Escape:
		GetCharacterMovement()->MaxWalkSpeed = escapeMoveSpeed_;
		break;
	case GhostState::Swoon:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	default:
		break;
	}
}

void ANormalGhost::SettingMostNearRestArea()
{
	TArray<AActor*> restAreas;
	FVector restAreaLocation;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARestArea::StaticClass(), restAreas);
	//���X�g�G���A�̐��������[�v
	for (TObjectPtr<AActor> loop : restAreas)
	{
		//���X�g�G���A�̈ʒu���擾
		restAreaLocation = loop->GetActorLocation();
		//���g�Ƃ̋������v��
		if (minimumDist > FVector::Distance(GetActorLocation(), restAreaLocation))
		{
			//�ŏ��������X�V
			minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
			//Actor�Ƃ��Ď擾���Ă��邽�߁A�L���X�g���ĕϊ�
			restArea = Cast<ARestArea>(loop);
		}
	}
}