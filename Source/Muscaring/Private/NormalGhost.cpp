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
#include "BreakableActor.h"
#include "InterfaceGhostState.h"

// Sets default values
ANormalGhost::ANormalGhost()
	:state(GhostState::Idle)
	, onSeeOnce(false)
	, minimumDist(10000.f)
	, scarePoint(0)
	, player(nullptr)
	, restArea(nullptr)
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
	/*for(const auto& i: ABreakableActor::GetBreakableActors())
	{
		auto geometry = i->GetComponentByClass<UGeometryCollectionComponent>();
		geometry->OnChaosBreakEvent.AddDynamic(this, &ANormalGhost::BrokenActor);
	}*/
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
	if (!onSeeOnce)
	{
		scarePoint+=1;
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetGhostState(normalGhostAI, state);
		onSeeOnce = true;
	}
}

//���|�l�ɉ����ď�Ԃ�ύX����
void ANormalGhost::ChangeState()
{
	if(scarePoint<30)
	{
		state = GhostState::Approach;
	}
	else if(scarePoint<60)
	{
		state = GhostState::Scare;
	}
	else if (scarePoint<100)
	{
		state = GhostState::Escape;
	}
	else if (scarePoint >= 100)
	{
		state = GhostState::Swoon;
	}
}
//��Ԃɂ���Ĉړ����x��ω�������
void ANormalGhost::ChangeMoveSpeed()
{
	switch (state)
	{
	case GhostState::Idle:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	case GhostState::Approach:
		GetCharacterMovement()->MaxWalkSpeed = defaultMoveSpeed;
		break;
	case GhostState::Scare:
		GetCharacterMovement()->MaxWalkSpeed = defaultMoveSpeed / 2;
		break;
	case GhostState::Escape:
		GetCharacterMovement()->MaxWalkSpeed = escapeMoveSpeed;
		break;
	case GhostState::Swoon:
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		break;
	default:
		break;
	}
}

void ANormalGhost::BrokenActor(const FChaosBreakEvent& breakEvent)
{
	scarePoint += 10;
	ChangeState();
	ChangeMoveSpeed();
	IInterfaceGhostState::Execute_SetGhostState(normalGhostAI, state);
}
