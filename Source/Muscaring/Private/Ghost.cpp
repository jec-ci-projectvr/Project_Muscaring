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

	//視野
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	//視野の距離
	PawnSensingComp->SightRadius = 2000.0f;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AGhost::OnSeePlayer);

	//player側のイベントに関数をバインド
	//未実装
}
// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	////AIコントローラーを設定
	//{
	//	ghostAI_ = Cast<ANormalGhostAI>(GetController());
	//}
	//プレイヤーの設定
	{
		player_ = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//プレイヤー
		if (ghostAI_ && player_)
		{
			//プレイヤー情報を設定
			ghostAI_->SetPlayerKey(player_);
		}
	}
	//レベル上に存在する特定のアクターを全て取得
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
	//OtherActorがプレイヤーだったらinterfaceを実行(playerの判定が無効であるため一時的に条件を無しに)
	IInterfaceGhostState::Execute_SetHitInfo(ghostAI_, true);
}
//動的デリゲートで呼び出す関数
//プレイヤーを見つけた時に一度だけ呼び出す
void AGhost::OnSeePlayer(APawn* Pawn)
{
	//プレイヤーを見つけた時に一度だけ呼び出す
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

//defaultMoveSpeedのsetter
void AGhost::SetDefaultMoveSpeed(const float speed)
{
	defaultMoveSpeed_ = speed;
}
//defaultMoveSpeedのgetter
float AGhost::GetDefaultMoveSpeed() const
{
	return defaultMoveSpeed_;
}
//escapeMoveSpeedのsetter
void AGhost::SetEscapeMoveSpeed(const float speed)
{
	escapeMoveSpeed_ = speed;
}
//escapeMoveSpeedのgetter
float AGhost::GetEscapeMoveSpeed() const
{
	return escapeMoveSpeed_;
}
//scarePointのsetter
void AGhost::SetScarePoint(const uint32 scarePoint)
{
	scarePoint_ = scarePoint;
}
//scarePointのgetter
uint32 AGhost::GetScarePoint() const
{
	return scarePoint_;
}
//stateのsetter
void AGhost::SetState(const GhostState state)
{
	state_ = state;
}
//stateのgetter
GhostState AGhost::GetState() const
{
	return state_;
}
//playerのsetter
void AGhost::SetPlayer(APawn* player)
{
	player_ = player;
}
 //playerのgetter
APawn* AGhost::GetPlayer() const
{
	return player_;
}
//restAreaのsetter
void AGhost::SetMostNearRestArea(ARestArea* restArea)
{
  mostNearrestArea_ = restArea;		
}
//restAreaのgetter
ARestArea* AGhost::GetMostNearRestArea() const
{
	return mostNearrestArea_;
}
//secondNearrestAreaのsetter
void AGhost::SetSecondNearRestArea(ARestArea* restArea)
{
	secondNearRestArea_ = restArea;
}
//secondNearrestAreaのgetter
ARestArea* AGhost::GetSecondNearRestArea() const
{
	return secondNearRestArea_;
}

//ghostAIのsetter
void AGhost::SetGhostAI(AGhostAI* ghostAI)
{
	ghostAI_ = ghostAI;
}
//ghostAIのgetter
AGhostAI* AGhost::GetGhostAI() const
{
	return ghostAI_;
}
//minimumDistのsetter
void AGhost::SetMinimumDist(const float minimumDist)
{
	minimumDist_ = minimumDist;
}
//minimumDistのgetter
float AGhost::GetMinimumDist() const
{
	return minimumDist_;
}
//onSeeOnceのsetter
void AGhost::SetOnSeeOnce(const bool onSeeOnce)
{
	onSeeOnce_ = onSeeOnce;
}
//onSeeOnceのgetter
bool AGhost::GetOnSeeOnce() const
{
	return onSeeOnce_;
}

//恐怖値に応じて状態を変更する
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
//状態によって移動速度を変化させる
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
//一番近いレストエリアと二番目に近いレストエリアを設定する
void AGhost::SettingMostNearRestArea()
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
		if (minimumDist_ > FVector::Distance(GetActorLocation(), restAreaLocation))
		{
			//最小距離を更新
			minimumDist_ = FVector::Distance(GetActorLocation(), restAreaLocation);
            //二番目に近いレストエリアを更新
			secondNearRestArea_ = mostNearrestArea_;
			//Actorとして取得しているため、キャストして変換
			mostNearrestArea_ = Cast<ARestArea>(loop);
		}
	}
}
