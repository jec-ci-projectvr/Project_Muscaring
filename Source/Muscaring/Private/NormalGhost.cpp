// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalGhost.h"
#include "PerCeption/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Muscaring/Muscaring.h"
#include "Muscaring/Public/NormalGhostAI.h"
#include "Muscaring/Public/NormalGhost.h"
#include <Kismet/GameplayStatics.h>
#include "RestArea.h"
// Sets default values
ANormalGhost::ANormalGhost(): defaultMoveSpeed(60.f), escapeMoveSpeedSpeed(90.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	//視野
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	//視野の距離
	PawnSensingComp->SightRadius = 2000.0f;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ANormalGhost::OnSeePlayer);

}

// Called when the game starts or when spawned
void ANormalGhost::BeginPlay()
{
	Super::BeginPlay();
	//レベル上に存在する特定のアクターを全て取得
	TArray<AActor*> restAreas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARestArea::StaticClass(), restAreas);
//レストエリアの数だけループ
	for (auto& loop : restAreas)
	{
		//レストエリアの位置を取得
		FVector restAreaLocation = loop->GetActorLocation();
		//自身との距離を計測
		if(minimumDist>FVector::Distance(GetActorLocation(),restAreaLocation))
        {
			//最小距離を更新
			minimumDist = FVector::Distance(GetActorLocation(), restAreaLocation);
			restArea= Cast<ARestArea>(loop);
		}
	}
}

// Called every frame
void ANormalGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormalGhost::OnSeePlayer(APawn* Pawn)
{
	ANormalGhostAI* AIController = Cast<ANormalGhostAI>(GetController());
	//プレイヤー
	APawn* Player = Pawn;
	if (AIController && Player)
	{
		//プレイヤー情報を設定
		AIController->SetPlayerKey(Player);
	}
}

