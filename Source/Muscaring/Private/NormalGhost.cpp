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

	player=UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//�v���C���[
	if (normalGhostAI && player)
	{
		//�v���C���[����ݒ�
		normalGhostAI->SetPlayerKey(player);
	}
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
	normalGhostAI = Cast<ANormalGhostAI>(GetController());
	//���x����ɑ��݂������̃A�N�^�[��S�Ď擾
	//TArray<AActor*> restAreas;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARestArea::StaticClass(), restAreas);
//���X�g�G���A�̐��������[�v
	//for (auto& loop : restAreas)
	//{
	//	//���X�g�G���A�̈ʒu���擾
	//	FVector restAreaLocation = loop->GetActorLocation();
	//	//���g�Ƃ̋������v��
	//	if(minimumDist>FVector::Distance(GetActorLocation(),restAreaLocation))
 //       {
	//		//�ŏ��������X�V
	//		minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
	//		//Actor�Ƃ��Ď擾���Ă��邽�߁A�L���X�g���ĕϊ�
	//		restArea = Cast<ARestArea>(loop);
	//	}
	//}
	//IInterfaceGhostState::Execute_SetMostNearRestArea(this, restArea);
}

// Called every frame
void ANormalGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANormalGhost::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	IInterfaceGhostState::Execute_SetHitInfo(this, hitPlayer);
}
//���I�f���Q�[�g�ŌĂяo���֐�
//�v���C���[�����������Ɉ�x�����Ăяo��
void ANormalGhost::OnSeePlayer(APawn* Pawn)
{
	//�v���C���[�����������Ɉ�x�����Ăяo��
	if (!onSeeOnce)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "see");
		scarePoint+=80;
		//state=GhostState::Approach;
		ChangeState();
		ChangeMoveSpeed();
		//normalGhostAI->SetGhostState_Implementation(state);
		IInterfaceGhostState::Execute_SetGhostState(this, state);
		onSeeOnce = true;
	}
}

//���|�l�ɉ����ď�Ԃ�ύX����
void ANormalGhost::ChangeState()
{
	if(scarePoint<30)
	{
		state = GhostState::Approach;
		UKismetSystemLibrary::PrintString(GetWorld(), "app");
	}
	else if(scarePoint<60)
	{
		state = GhostState::Scare;
		UKismetSystemLibrary::PrintString(GetWorld(),"scare");
	}
	else if (scarePoint<100)
	{
		state = GhostState::Escape;
		UKismetSystemLibrary::PrintString(GetWorld(),"esc");
	}
	else if (scarePoint >= 100)
	{
		state = GhostState::Swoon;
		UKismetSystemLibrary::PrintString(GetWorld(), "swo");
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
