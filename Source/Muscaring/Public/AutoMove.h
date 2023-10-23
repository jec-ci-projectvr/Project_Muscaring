// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "MovePoint.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AutoMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSCARING_API UAutoMove : public UActorComponent
{
	GENERATED_BODY()

	UWorld* world_;

	//動いているかどうか
	bool isMoving_;

	//親アクター
	TObjectPtr<AActor> parentActor_;

	//親アクターのAIコントローラー
	TObjectPtr<AController> controller_;

	//現在の目的地
	TObjectPtr<AMovePoint> destination_;


	//回転中かどうか
	bool isRotating_;

	//回転スピード
	UPROPERTY(EditAnywhere, Category = "Rotate")
	float rotationSpeed_;

	//目的地に向かって回転させる
	void RotateToDestination();

public:	
	// Sets default values for this component's properties
	UAutoMove();

	UFUNCTION(BlueprintPure)
	bool IsMoving() { return isMoving_; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//目的地に到着したときの処理
	UFUNCTION()
	void PointArrival(AMovePoint* point);

	//目的地を出発したときの処理
	UFUNCTION()
	void PointDeparture(AMovePoint* point, AMovePoint* next);
};
