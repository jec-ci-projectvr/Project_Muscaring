// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoMove.h"

// Sets default values for this component's properties
UAutoMove::UAutoMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	isMoving = true;
	isRotating = true;
	rotationSpeed = 1.0f;

	// ...
}


// Called when the game starts
void UAutoMove::BeginPlay()
{
	parentActor = GetOwner();

	TArray<AActor*> actors;

	//MovePointを取得
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMovePoint::StaticClass(), actors);
	for (const auto& p : actors)
	{
		TObjectPtr<AMovePoint> point = Cast<AMovePoint>(p);

		if(point->GetTargetActor() != parentActor) continue;

		//イベント登録
		point->OnPointArrival.AddUObject(this, &UAutoMove::PointArrival);
		point->OnPointDeparture.AddUObject(this, &UAutoMove::PointDeparture);

		//最初の目的地を設定
		if (point->IsEntryPoint()) {
			destination = point;
			point->SetActive(true);
		}
	}

	//PawnからAIControllerを取得
	controller = Cast<APawn>(parentActor)->GetController();
	if (controller != nullptr && destination != nullptr) {
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, destination->GetActorLocation());
	}

	world = GEngine->GameViewport->GetWorld();

	Super::BeginPlay();

}

void UAutoMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	RotateToDestination();
}

void UAutoMove::PointArrival(AMovePoint* point)
{
	if(destination != point) return;

	//一時停止ポイントなら移動を止める
	if (point->IsWaitPoint()) {
		isMoving = false;
	}
}

void UAutoMove::PointDeparture(AMovePoint* point, AMovePoint* next)
{
	if(destination != point) return;

	//次点を設定する
	if (next != nullptr) {
		isMoving = true;
		destination = next;
	}
	else {
		isMoving = false;
		return;
	}

	isRotating = point->IsRotate();

	next->SetActive(true);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, destination->GetActorLocation());
}

void UAutoMove::RotateToDestination()
{
	if (!isRotating) return;
	if (destination == nullptr) return;

	FRotator current = parentActor->GetActorRotation();
	FRotator target = UKismetMathLibrary::FindLookAtRotation(parentActor->GetActorLocation(), destination->GetActorLocation());

	FRotator result = UKismetMathLibrary::RInterpTo(current, target, world->GetDeltaSeconds(), rotationSpeed);

	//X軸とZ軸は固定
	result.Roll = 0.0f;
	result.Pitch = 0.0f;

	isRotating = parentActor->SetActorRotation(result);

}

