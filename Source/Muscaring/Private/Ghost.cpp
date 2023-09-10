// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"
#include "GhostAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PerCeption/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NormalGhostAI.h"
#include "Enum_GhostState.h"
#include "RestArea.h"
#include "PlayerActionEvent.h"
#include "BreakableActor.h"
#include "Kismet/KismetSystemLibrary.h"

AGhost::AGhost()
	: state_(GhostState::Idle)
	, onSeeOnce_(false)
	, scarePoint_(0)
	, recoverPoint_(30)
	, player_(nullptr)
	, mostNearRestArea_(nullptr)
	, endRestArea_(nullptr)
	, defaultMoveSpeed_(60.f)
	, escapeMoveSpeed_(150.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LoadAllExpression();
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//����
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	//����̋���
	PawnSensingComp->SightRadius = 5000.0f;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AGhost::OnSeePlayer);
    //��������͈�
    PawnSensingComp->HearingThreshold = 2000.0f;
    //��������͈͂̋���
    PawnSensingComp->LOSHearingThreshold = 2500.0f;
}
// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
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
		SettingNearRestArea();
	}
	PlayerActionEvent = Cast<UPlayerActionEvent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass(UPlayerActionEvent::StaticClass()));
	PlayerActionEvent->OnSnapFingers.AddDynamic(this, &AGhost::ListenSnapFingers);
	PlayerActionEvent->OnFakeOut.AddDynamic(this, &AGhost::ListenFakeOut);

	//�S�Ă�BreakableActor���擾���A�C�x���g��o�^
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABreakableActor::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		auto breakableActor = Cast<ABreakableActor>(Actor);
		//breakableActor->GetGeometryCollectionComponent()->OnChaosBreakEvent.AddDynamic(this, &AGhost::ListenFakeOut);
	}
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isBeginMoveToPlayer)
	{
		//���g�̑O���Ƀv���C���[�����邩�ǂ���
		if (FVector::DotProduct(GetActorForwardVector(), player_->GetActorLocation() - GetActorLocation()) > 0)
		{
			SettingNearRestArea();
			ChangeMoveSpeed();
			isBeginMoveToPlayer = false;
			UKismetSystemLibrary::PrintString(GetWorld(), "exe");
		}
	}
}
void AGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//OtherActor���v���C���[��������interface�����s
    if (OtherActor==player_)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Hit");
		IInterfaceGhostState::Execute_SetHitInfo(ghostAI_, true);
		GetCharacterMovement()->MaxWalkSpeed = escapeMoveSpeed_;
	}
	//OtherActor��endRestArea�����������
	if (endRestArea_)
	{
		if (OtherActor == endRestArea_)
		{
			//������Ԃł̂ݏ�������
			if (state_ == GhostState::Escape)
			{
				Destroy();
			}
		}
	}
}
//���I�f���Q�[�g�ŌĂяo���֐�
//�v���C���[�����������Ɉ�x�����Ăяo��
void AGhost::OnSeePlayer(APawn* Pawn)
{
	//�v���C���[�����������Ɉ�x�����Ăяo��
	if (!onSeeOnce_)
	{
		++scarePoint_;
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetGhostState(ghostAI_, state_);
		IInterfaceGhostState::Execute_SetEndRestArea(ghostAI_, endRestArea_);
		onSeeOnce_ = true;

		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("see"));
	}
}
//�w�|�L�C�x���g�ŌĂяo��
void AGhost::ListenSnapFingers()
{
	//�v���C���[�Ƃ̋������v��(�������܂܂Ȃ�)
	const float distance = FVector::Dist2D(player_->GetActorLocation(), GetActorLocation());
	//��������͈͓��ł���Ύ��s
	if (distance <= PawnSensingComp->HearingThreshold)
	{
		scarePoint_ += 3;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}
//�L���܂��C�x���g�ŌĂяo��
void AGhost::ListenFakeOut()
{
	//�v���C���[�Ƃ̋������v��(�������܂܂Ȃ�)
	const float distance = FVector::Dist2D(player_->GetActorLocation(), GetActorLocation());
	//��������͈͓��ł���Ύ��s
	if (distance <= PawnSensingComp->HearingThreshold)
	{
		scarePoint_ += 10;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetFakeOut(ghostAI_, true);
		IInterfaceGhostState::Execute_SetGhostState(ghostAI_,state_ );
	}

}
//�v���C���[��restArea�𓥂񂾎��ɌĂяo��
void AGhost::StepOnRestArea()
{
	
}

void AGhost::RecoverScarePoint(uint32 recoverAmount)
{
	scarePoint_ -= recoverAmount;
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
    mostNearRestArea_ = restArea;		
}
//restArea��getter
ARestArea* AGhost::GetMostNearRestArea() const
{
	return mostNearRestArea_;
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
//materials��getter
TArray<UMaterial*> AGhost::GetMaterials() const
{
	return materials_;
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
	ChangeExpression();
	IInterfaceGhostState::Execute_SetGhostState(ghostAI_, state_);
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

void AGhost::ChangeExpression()
{
	switch (state_)
	{
	case GhostState::Approach:
		GetMesh()->SetMaterial(0, materials_[0]);
		break;
	case GhostState::Scare:
		GetMesh()->SetMaterial(0, materials_[1]);
		break;
	case GhostState::Escape:
		GetMesh()->SetMaterial(0, materials_[2]);
		break;
	case GhostState::Swoon:
		GetMesh()->SetMaterial(0, materials_[2]);
		break;
	}
}
//��ԋ߂����X�g�G���A�Ɠ�Ԗڂɋ߂����X�g�G���A��ݒ肷��
void AGhost::SettingNearRestArea()
{
	TArray<AActor*> restAreas;
	FVector restAreaLocation;
	float minimumDist = 100000.f;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARestArea::StaticClass(), restAreas);
	//�S�Ẵ��X�g�G���A�̂������g�̑O���ɂ��郌�X�g�G���A�̂ݎ擾
	for (TObjectPtr<AActor> loop : restAreas)
	{
		//���X�g�G���A�̈ʒu���擾
		restAreaLocation = loop->GetActorLocation();
		//���g�̑O���ɂ��郌�X�g�G���A�����O
		if (FVector::DotProduct(GetActorForwardVector(), restAreaLocation - GetActorLocation()) > 0)
		{
			continue;
		}
		{
			//���g�Ƃ̋������v��
			if (minimumDist > FVector::Distance(GetActorLocation(), restAreaLocation))
			{
				//�ŏ��������X�V
				minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
				//Actor�Ƃ��Ď擾���Ă��邽�߁A�L���X�g���ĕϊ�
				mostNearRestArea_ = Cast<ARestArea>(loop);
			}
		}
	}
	//��Ԗڂɋ߂����X�g�G���A��ݒ�
	minimumDist = 100000.f;
	for (TObjectPtr<AActor> loop : restAreas)
	{
		//���X�g�G���A�̈ʒu���擾
		restAreaLocation = loop->GetActorLocation();
		//���g�̑O���ɂ��郌�X�g�G���A�����O
		if (FVector::DotProduct(GetActorForwardVector(), restAreaLocation - GetActorLocation()) > 0)
		{
			continue;
		}
		{
			//��ԋ߂����X�g�G���A�Ɠ������̂͏��O
			if (mostNearRestArea_ == loop)
			{
				continue;
			}
			else if (minimumDist > FVector::Distance(GetActorLocation(), restAreaLocation))//���g�Ƃ̋������v��
			{
				//�ŏ��������X�V
				minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
				//Actor�Ƃ��Ď擾���Ă��邽�߁A�L���X�g���ĕϊ�
				secondNearRestArea_ = Cast<ARestArea>(loop);
			}
		}
	}

	if (endRestArea_!=nullptr)
	{
		//endRestArea��500���ȓ��ɂ���Γ������Ԃɂ���
		if (FVector::Distance(GetActorLocation(), endRestArea_->GetActorLocation()) < 500.f)
		{
			state_ = GhostState::Escape;
			IInterfaceGhostState::Execute_SetGhostState(ghostAI_, state_);
		}
	}

	IInterfaceGhostState::Execute_SetMostNearRestArea(ghostAI_, mostNearRestArea_);
	IInterfaceGhostState::Execute_SetSecondNearRestArea(ghostAI_, secondNearRestArea_);
}
void AGhost::LoadAllExpression()
{
}
//�I�o�P���v���C���[�Ɍ������n�߂����̏���
void AGhost::BeginMoveToPlayer_Implementation()
{
	isBeginMoveToPlayer = true;
}
