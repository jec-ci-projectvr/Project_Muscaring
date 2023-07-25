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
	//プレイヤー
	if (normalGhostAI && player)
	{
		//プレイヤー情報を設定
		normalGhostAI->SetPlayerKey(player);
	}
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
	normalGhostAI = Cast<ANormalGhostAI>(GetController());
	//レベル上に存在する特定のアクターを全て取得
	//TArray<AActor*> restAreas;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARestArea::StaticClass(), restAreas);
//レストエリアの数だけループ
	//for (auto& loop : restAreas)
	//{
	//	//レストエリアの位置を取得
	//	FVector restAreaLocation = loop->GetActorLocation();
	//	//自身との距離を計測
	//	if(minimumDist>FVector::Distance(GetActorLocation(),restAreaLocation))
 //       {
	//		//最小距離を更新
	//		minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
	//		//Actorとして取得しているため、キャストして変換
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
//動的デリゲートで呼び出す関数
//プレイヤーを見つけた時に一度だけ呼び出す
void ANormalGhost::OnSeePlayer(APawn* Pawn)
{
	//プレイヤーを見つけた時に一度だけ呼び出す
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

//恐怖値に応じて状態を変更する
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
//状態によって移動速度を変化させる
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
