// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MoveResumeTrigger.h"
#include "MovePoint.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointArrival, AMovePoint*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPointDeparture, AMovePoint*, AMovePoint*);

UCLASS()
class MUSCARING_API AMovePoint : public AActor
{
	GENERATED_BODY()

	// Scene Component
	TObjectPtr<USceneComponent> defaultSceneRoot_;

	// StaticMesh Component
	TObjectPtr<UStaticMeshComponent> staticMesh_;

	//最初に到達するべきポイントか
	UPROPERTY(EditAnywhere, Category = "Entry")
	bool entryPoint_;

	//この地点に到達すると一時停止させるか
	UPROPERTY(EditAnywhere, Category = "Event")
	bool waitPoint_;

	//一時停止を解除するトリガーとなるアクター(IMoveResumeTriggerが実装されたオブジェクトである必要がある)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "waitPoint"), Category = "Event")
	TObjectPtr<AActor> resumeTriggerObject_;

	//この地点で回転させるか
	UPROPERTY(EditAnywhere, Category = "Event")
	bool rotate_;

	//到達したと判定する距離
	UPROPERTY(EditAnywhere, Category = "General")
	float arrivalDistance_;

	//このポイントの次に到達するポイント
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AMovePoint> nextPoint_;

	//このポイントを追従するアクター("なし"だとプレイヤーになります)
	UPROPERTY(EditAnywhere, Category = "General")
	TObjectPtr<AActor> targetActor_;

	//到達済みかどうか
	bool isArrived_;

	//MovePointが有効かどうか
	bool isActive_;

	//到達したときの処理
	void Arrival();

	//出発したときの処理
	void Departure();
	
	//ターゲットとの距離をチェック
	bool CheckDistance();

	//一時停止を解除するトリガーが有効かどうかチェック
	bool CheckResumeTrigger();

public:	
	// Sets default values for this actor's properties
	AMovePoint();

	TObjectPtr<AActor> GetTargetActor() { return targetActor_; }

	bool IsEntryPoint() { return entryPoint_; }

	bool IsWaitPoint() { return waitPoint_; }

	bool IsRotate() { return rotate_; }

	void SetActive(bool active) { isActive_ = active; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnPointArrival OnPointArrival;

	FOnPointDeparture OnPointDeparture;

};
