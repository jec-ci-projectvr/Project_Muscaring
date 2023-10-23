// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoMove.h"

// Sets default values for this component's properties
UAutoMove::UAutoMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	isMoving_ = true;
	isRotating_ = true;
	rotationSpeed_ = 1.0f;

	// ...
}


// Called when the game starts
void UAutoMove::BeginPlay()
{
	parentActor_ = GetOwner();

	TArray<AActor*> actors;

	//MovePointを取得
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMovePoint::StaticClass(), actors);
	for (const auto& p : actors)
	{
		TObjectPtr<AMovePoint> point = Cast<AMovePoint>(p);

		if(point->GetTargetActor() != parentActor_) continue;

		//イベント登録
		point->OnPointArrival.AddUObject(this, &UAutoMove::PointArrival);
		point->OnPointDeparture.AddUObject(this, &UAutoMove::PointDeparture);

		//最初の目的地を設定
		if (point->IsEntryPoint()) {
			destination_ = point;
			point->SetActive(true);
		}
	}

	//PawnからAIControllerを取得
	controller_ = Cast<APawn>(parentActor_)->GetController();
	if (controller_ != nullptr && destination_ != nullptr) {
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller_, destination_->GetActorLocation());
	}
	else {
		isMoving_ = false;
	}

	world_ = GEngine->GameViewport->GetWorld();

	Super::BeginPlay();

}

void UAutoMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	RotateToDestination();
}

void UAutoMove::PointArrival(AMovePoint* point)
{
	if(destination_ != point) return;

	//一時停止ポイントなら移動を止める
	if (point->IsWaitPoint()) {
		isMoving_ = false;
	}
}

void UAutoMove::PointDeparture(AMovePoint* point, AMovePoint* next)
{
	if(destination_ != point) return;

	//次点を設定する
	if (next != nullptr) {
		isMoving_ = true;
		destination_ = next;
	}
	else {
		isMoving_ = false;
		return;
	}

	isRotating_ = point->IsRotate();

	next->SetActive(true);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller_, destination_->GetActorLocation());
}

void UAutoMove::RotateToDestination()
{
	if (!isRotating_) return;
	if (destination_ == nullptr) return;

	FRotator current = parentActor_->GetActorRotation();
	FRotator target = UKismetMathLibrary::FindLookAtRotation(parentActor_->GetActorLocation(), destination_->GetActorLocation());

	FRotator result = UKismetMathLibrary::RInterpTo(current, target, world_->GetDeltaSeconds(), rotationSpeed_);

	//X軸とZ軸は固定
	result.Roll = 0.0f;
	result.Pitch = 0.0f;

	isRotating_ = parentActor_->SetActorRotation(result);

}

