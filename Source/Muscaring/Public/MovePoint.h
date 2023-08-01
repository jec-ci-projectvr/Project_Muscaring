// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "MoveResumeTrigger.h"
#include "MovePoint.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointArrival, AMovePoint*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPointDeparture, AMovePoint*, AMovePoint*);

UCLASS()
class MUSCARING_API AMovePoint : public AActor
{
	GENERATED_BODY()

	// Scene Component
	TObjectPtr<USceneComponent> defaultSceneRoot;

	// StaticMesh Component
	TObjectPtr<UStaticMeshComponent> staticMesh;

public:	
	// Sets default values for this actor's properties
	AMovePoint();

	TObjectPtr<AMovePoint> targetDistination;

	//最初に到達するべきポイントか
	UPROPERTY(EditAnywhere, Category = "Entry")
	bool entryPoint;

	//この地点に到達すると一時停止させるか
	UPROPERTY(EditAnywhere, Category = "Wait")
	bool waitPoint;

	//一時停止を解除するトリガーとなるアクター(IMoveResumeTriggerが実装されたオブジェクトである必要がある)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "waitPoint"), Category = "Wait")
	TObjectPtr<AActor> resumeTriggerObject;

	//到達したと判定する距離
	UPROPERTY(EditAnywhere, Category = "General")
	float arrivalDistance;

	//このポイントの次に到達するポイント
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AMovePoint> nextPoint;

	//このポイントを追従するアクター("なし"だとプレイヤーになります)
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AActor> targetActor;

	//ゲーム中にポイントのメッシュを表示させるか
	UPROPERTY(EditAnywhere, Category = "Visible")
	bool displayMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	IMoveResumeTrigger* resumeTrigger;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnPointArrival OnPointArrival;

	FOnPointDeparture OnPointDeparture;

};
