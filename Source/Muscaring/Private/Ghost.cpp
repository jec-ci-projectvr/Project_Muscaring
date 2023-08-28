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
AGhost::AGhost()
	: state_(GhostState::Idle)
	, onSeeOnce_(false)
	, scarePoint_(0)
	, player_(nullptr)
	, mostNearRestArea_(nullptr)
	, defaultMoveSpeed_(60.f)
	, escapeMoveSpeed_(90.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	//視野
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	//視野の距離
	PawnSensingComp->SightRadius = 5000.0f;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AGhost::OnSeePlayer);
    //聞こえる範囲
    PawnSensingComp->HearingThreshold = 1000.0f;
    //聞こえる範囲の距離
    PawnSensingComp->LOSHearingThreshold = 2000.0f;
}
// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
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
	}
	PlayerActionEvent= Cast<UPlayerActionEvent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass(UPlayerActionEvent::StaticClass()));
	PlayerActionEvent->OnSnapFingers.AddDynamic(this, &AGhost::ListenSnapFingers);
	PlayerActionEvent->OnFakeOut.AddDynamic(this, &AGhost::ListenFakeOut);
	//mostNearRestArea_->onRestAreaDelegate.AddDynamic(this, &AGhost::StepOnRestArea);
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//自身の前方にプレイヤーがいるかどうか
	if (isBeginMoveToPlayer)
	{
		if (FVector::DotProduct(GetActorForwardVector(), player_->GetActorLocation() - GetActorLocation()) > 0)
		{
			SettingMostNearRestArea();
			isBeginMoveToPlayer = false;
			UKismetSystemLibrary::PrintString(GetWorld(), "exe");
		}
	}
}
void AGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//OtherActorがプレイヤーだったらinterfaceを実行
    if (OtherActor==player_)
	{
		IInterfaceGhostState::Execute_SetHitInfo(ghostAI_, true);
		GetCharacterMovement()->MaxWalkSpeed = escapeMoveSpeed_;
	}
}
//動的デリゲートで呼び出す関数
//プレイヤーを見つけた時に一度だけ呼び出す
void AGhost::OnSeePlayer(APawn* Pawn)
{
	//プレイヤーを見つけた時に一度だけ呼び出す
	if (!onSeeOnce_)
	{
		++scarePoint_;
		ChangeState();
		ChangeMoveSpeed();
		IInterfaceGhostState::Execute_SetGhostState(ghostAI_, state_);
		onSeeOnce_ = true;

		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("see"));
	}
}
//指ポキイベントで呼び出す
void AGhost::ListenSnapFingers()
{
	//プレイヤーとの距離を計測(高さを含まない)
	const float distance = FVector::Dist2D(player_->GetActorLocation(), GetActorLocation());
	//聞こえる範囲内であれば実行
	if (distance <= PawnSensingComp->HearingThreshold)
	{
		scarePoint_ += 3;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}
//猫だましイベントで呼び出す
void AGhost::ListenFakeOut()
{
	//プレイヤーとの距離を計測(高さを含まない)
	const float distance = FVector::Dist2D(player_->GetActorLocation(), GetActorLocation());
	//聞こえる範囲内であれば実行
	if (distance <= PawnSensingComp->HearingThreshold)
	{
		scarePoint_ += 10;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("scarePoint:%d"), GetScarePoint()));
		ChangeState();
		ChangeMoveSpeed();
	}
}
//プレイヤーがrestAreaを踏んだ時に呼び出す
void AGhost::StepOnRestArea()
{
	
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
    mostNearRestArea_ = restArea;		
}
//restAreaのgetter
ARestArea* AGhost::GetMostNearRestArea() const
{
	return mostNearRestArea_;
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
	float minimumDist = 100000.f;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARestArea::StaticClass(), restAreas);
	int count = 0;
	//全てのレストエリアのうち自身の前方にあるレストエリアのみ取得
	for (TObjectPtr<AActor> loop : restAreas)
	{
		//レストエリアの位置を取得
		restAreaLocation = loop->GetActorLocation();
		//自身の前方にあるレストエリアを除外
		if (FVector::DotProduct(GetActorForwardVector(), restAreaLocation - GetActorLocation()) > 0)
		{
			count++;
			continue;
		}
		{
			//自身との距離を計測
			if (minimumDist > FVector::Distance(GetActorLocation(), restAreaLocation))
			{
				//最小距離を更新
				minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
				//Actorとして取得しているため、キャストして変換
				mostNearRestArea_ = Cast<ARestArea>(loop);
			}
		}
	}
	//二番目に近いレストエリアを設定
	minimumDist = 100000.f;
	for (TObjectPtr<AActor> loop : restAreas)
	{
		//レストエリアの位置を取得
		restAreaLocation = loop->GetActorLocation();
		//自身の前方にあるレストエリアを除外
		if (FVector::DotProduct(GetActorForwardVector(), restAreaLocation - GetActorLocation()) > 0)
		{
			continue;
		}
		{
			//一番近いレストエリアと同じものは除外
			if (mostNearRestArea_ == loop)
			{
				continue;
			}
			else if (minimumDist > FVector::Distance(GetActorLocation(), restAreaLocation))//自身との距離を計測
			{
				//最小距離を更新
				minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
				//Actorとして取得しているため、キャストして変換
				secondNearRestArea_ = Cast<ARestArea>(loop);
			}
		}
	}
	if(mostNearRestArea_==nullptr) UKismetSystemLibrary::PrintString(GetWorld(), "nullptr01");
	if(secondNearRestArea_==nullptr) UKismetSystemLibrary::PrintString(GetWorld(), "nullptr02");
	//countを表示
	UKismetSystemLibrary::PrintString(GetWorld(), FString::FromInt(count));
	IInterfaceGhostState::Execute_SetMostNearRestArea(ghostAI_, mostNearRestArea_);
	IInterfaceGhostState::Execute_SetSecondNearRestArea(ghostAI_, secondNearRestArea_);
}
//レストエリアが破棄されたときの処理
void AGhost::DestroyedRestArea_Implementation()
{
	
}
//オバケがプレイヤーに向かい始めた時の処理
void AGhost::BeginMoveToPlayer_Implementation()
{
	isBeginMoveToPlayer = true;
	//SettingMostNearRestArea();
	UKismetSystemLibrary::PrintString(GetWorld(), "startMove");
}
