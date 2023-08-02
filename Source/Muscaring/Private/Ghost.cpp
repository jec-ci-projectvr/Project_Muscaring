// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"
#include "GhostAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PerCeption/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NormalGhostAI.h"
#include "Enum_GhostState.h"
#include "RestArea.h"

AGhost::AGhost()
	:state_(GhostState::Idle)
	, onSeeOnce_(false)
	, minimumDist_(10000.f)
	, scarePoint_(0)
	, player_(nullptr)
	, mostNearrestArea_(nullptr)
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
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AGhost::OnSeePlayer);

	//player���̃C�x���g�Ɋ֐����o�C���h
	//������
}
// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	////AI�R���g���[���[��ݒ�
	//{
	//	ghostAI_ = Cast<ANormalGhostAI>(GetController());
	//}
	//�v���C���[�̐ݒ�
	{
		player_ = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//�v���C���[
		if (ghostAI_ && player_)
		{
			//�v���C���[����ݒ�
			ghostAI_->SetPlayerKey(player_);
		}
	}
	//���x����ɑ��݂������̃A�N�^�[��S�Ď擾
	{

		SettingMostNearRestArea();
		IInterfaceGhostState::Execute_SetMostNearRestArea(ghostAI_, mostNearrestArea_);
		IInterfaceGhostState::Execute_SetSecondNearRestArea(ghostAI_, secondNearRestArea_);
	}
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//OtherActor���v���C���[��������interface�����s(player�̔��肪�����ł��邽�߈ꎞ�I�ɏ����𖳂���)
	IInterfaceGhostState::Execute_SetHitInfo(ghostAI_, true);
}
//���I�f���Q�[�g�ŌĂяo���֐�
//�v���C���[�����������Ɉ�x�����Ăяo��
void AGhost::OnSeePlayer(APawn* Pawn)
{
	//�v���C���[�����������Ɉ�x�����Ăяo��
	if (!onSeeOnce_)
	{
		scarePoint_ += 10;
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetGhostState(ghostAI_, state_);
		onSeeOnce_ = true;

		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("see"));
	}
}

//defaultMoveSpeed��setter
void AGhost::SetDefaultMoveSpeed(const float speed)
{
	defaultMoveSpeed_ = speed;
}
//defaultMoveSpeed��getter
float AGhost::GetDefaultMoveSpeed() const
{
	return defaultMoveSpeed_;
}
//escapeMoveSpeed��setter
void AGhost::SetEscapeMoveSpeed(const float speed)
{
	escapeMoveSpeed_ = speed;
}
//escapeMoveSpeed��getter
float AGhost::GetEscapeMoveSpeed() const
{
	return escapeMoveSpeed_;
}
//scarePoint��setter
void AGhost::SetScarePoint(const uint32 scarePoint)
{
	scarePoint_ = scarePoint;
}
//scarePoint��getter
uint32 AGhost::GetScarePoint() const
{
	return scarePoint_;
}
//state��setter
void AGhost::SetState(const GhostState state)
{
	state_ = state;
}
//state��getter
GhostState AGhost::GetState() const
{
	return state_;
}
//player��setter
void AGhost::SetPlayer(APawn* player)
{
	player_ = player;
}
 //player��getter
APawn* AGhost::GetPlayer() const
{
	return player_;
}
//restArea��setter
void AGhost::SetMostNearRestArea(ARestArea* restArea)
{
  mostNearrestArea_ = restArea;		
}
//restArea��getter
ARestArea* AGhost::GetMostNearRestArea() const
{
	return mostNearrestArea_;
}
//secondNearrestArea��setter
void AGhost::SetSecondNearRestArea(ARestArea* restArea)
{
	secondNearRestArea_ = restArea;
}
//secondNearrestArea��getter
ARestArea* AGhost::GetSecondNearRestArea() const
{
	return secondNearRestArea_;
}

//ghostAI��setter
void AGhost::SetGhostAI(AGhostAI* ghostAI)
{
	ghostAI_ = ghostAI;
}
//ghostAI��getter
AGhostAI* AGhost::GetGhostAI() const
{
	return ghostAI_;
}
//minimumDist��setter
void AGhost::SetMinimumDist(const float minimumDist)
{
	minimumDist_ = minimumDist;
}
//minimumDist��getter
float AGhost::GetMinimumDist() const
{
	return minimumDist_;
}
//onSeeOnce��setter
void AGhost::SetOnSeeOnce(const bool onSeeOnce)
{
	onSeeOnce_ = onSeeOnce;
}
//onSeeOnce��getter
bool AGhost::GetOnSeeOnce() const
{
	return onSeeOnce_;
}

//���|�l�ɉ����ď�Ԃ�ύX����
void AGhost::ChangeState()
{
	if (scarePoint_ < 30)
	{
		state_ = GhostState::Approach;
	}
	else if (scarePoint_ < 60)
	{
		state_ = GhostState::Scare;
	}
	else if (scarePoint_ < 100)
	{
		state_ = GhostState::Escape;
	}
	else if (scarePoint_ >= 100)
	{
		state_ = GhostState::Swoon;
	}
}
//��Ԃɂ���Ĉړ����x��ω�������
void AGhost::ChangeMoveSpeed()
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
//��ԋ߂����X�g�G���A�Ɠ�Ԗڂɋ߂����X�g�G���A��ݒ肷��
void AGhost::SettingMostNearRestArea()
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
		if (minimumDist_ > FVector::Distance(GetActorLocation(), restAreaLocation))
		{
			//�ŏ��������X�V
			minimumDist_ = FVector::Distance(GetActorLocation(), restAreaLocation);
            //��Ԗڂɋ߂����X�g�G���A���X�V
			secondNearRestArea_ = mostNearrestArea_;
			//Actor�Ƃ��Ď擾���Ă��邽�߁A�L���X�g���ĕϊ�
			mostNearrestArea_ = Cast<ARestArea>(loop);
		}
	}
}
