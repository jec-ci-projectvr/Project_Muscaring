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

	//視野
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	//視野の距離
	PawnSensingComp->SightRadius = 2000.0f;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ANormalGhost::OnSeePlayer);

	//player側のイベントに関数をバインド
	//未実装
}

// Called when the game starts or when spawned
void ANormalGhost::BeginPlay()
{
	Super::BeginPlay();
	//AIコントローラーを設定
	{
		normalGhostAI = Cast<ANormalGhostAI>(GetController());
	}
	//プレイヤーの設定
	{
		player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//プレイヤー
		if (normalGhostAI && player)
		{
			//プレイヤー情報を設定
			normalGhostAI->SetPlayerKey(player);
		}
	}
	//レベル上に存在する特定のアクターを全て取得
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
	//OtherActorがプレイヤーだったらinterfaceを実行(playerの判定が無効であるため一時的に条件を無しに)
	IInterfaceGhostState::Execute_SetHitInfo(normalGhostAI, true);
}
//動的デリゲートで呼び出す関数
//プレイヤーを見つけた時に一度だけ呼び出す
void ANormalGhost::OnSeePlayer(APawn* Pawn)
{
	//プレイヤーを見つけた時に一度だけ呼び出す
	if (!onSeeOnce_)
	{
		scarePoint_+=10;
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetGhostState(normalGhostAI, state_);
		onSeeOnce_ = true;
	}
}

//defaultMoveSpeedのsetter
void ANormalGhost::SetDefaultMoveSpeed(const float speed)
{
	defaultMoveSpeed_ = speed;
}
//defaultMoveSpeedのgetter
float ANormalGhost::GetDefaultMoveSpeed() const
{
	return defaultMoveSpeed_;
}
//escapeMoveSpeedのsetter
void ANormalGhost::SetEscapeMoveSpeed(const float speed)
{
	escapeMoveSpeed_ = speed;
}
//escapeMoveSpeedのgetter
float ANormalGhost::GetEscapeMoveSpeed() const
{
	return escapeMoveSpeed_;
}
//scarePointのsetter
void ANormalGhost::SetScarePoint(const uint32 scarePoint)
{
	scarePoint_ = scarePoint;
}
//恐怖値に応じて状態を変更する
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
//状態によって移動速度を変化させる
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
	//レストエリアの数だけループ
	for (TObjectPtr<AActor> loop : restAreas)
	{
		//レストエリアの位置を取得
		restAreaLocation = loop->GetActorLocation();
		//自身との距離を計測
		if (minimumDist > FVector::Distance(GetActorLocation(), restAreaLocation))
		{
			//最小距離を更新
			minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
			//Actorとして取得しているため、キャストして変換
			restArea = Cast<ARestArea>(loop);
		}
	}
}