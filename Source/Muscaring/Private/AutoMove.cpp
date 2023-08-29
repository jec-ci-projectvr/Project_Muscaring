// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoMove.h"

// Sets default values for this component's properties
UAutoMove::UAutoMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	isMoving = true;
	// ...
}


// Called when the game starts
void UAutoMove::BeginPlay()
{
	parentActor = GetOwner();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMovePoint::StaticClass(), actors);

	//�������^�[�Q�b�g�Ƃ��Ă���S�Ă�MovePoint���擾
	for (auto a : actors)
	{
		AMovePoint* movePoint = Cast<AMovePoint>(a);
		if (movePoint->targetActor == parentActor) {
			movePoints.Add(movePoint);
		}
	}

	//�ŏ���MovePoint���擾
	for (auto p : movePoints) {
		if (p->entryPoint) {
			distination = p;
			break;
		}
	}

	//OnArrivalPoint�ɃC�x���g��o�^
	for (auto p : movePoints) {
		p->OnPointArrival.AddUObject(this, &UAutoMove::PointArrival);
		p->OnPointDeparture.AddUObject(this, &UAutoMove::PointDeparture);
	}

	for (auto p : movePoints) {
		p->targetDistination = distination;
	}

	//Pawn����AIController���擾
	controller = Cast<APawn>(parentActor)->GetController();
	if (controller != nullptr && distination != nullptr) {
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, distination->GetActorLocation());
	}
	Super::BeginPlay();
	// ...
	
}

void UAutoMove::PointArrival(AMovePoint* point)
{
	if (point->waitPoint) {
		isMoving = false;
	}
}

void UAutoMove::PointDeparture(AMovePoint* point, AMovePoint* next)
{
	if (next != nullptr) {
		isMoving = true;
		distination = next;
		for (auto p : movePoints) {
			p->targetDistination = next;
		}
	}
	else {
		isMoving = false;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, distination->GetActorLocation());
	movePoints.Remove(point);
}

