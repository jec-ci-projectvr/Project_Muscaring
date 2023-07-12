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

	//‘S‚Ä‚ÌMovePoint‚ðŽæ“¾
	for (auto a : actors)
	{
		AMovePoint* movePoint = Cast<AMovePoint>(a);
		if (movePoint->targetActor == parentActor)
		{
			movePoints.Add(movePoint);
		}
	}

	//Å‰‚ÌMovePoint‚ðŽæ“¾
	for (auto p : movePoints)
	{
		if (p->entryPoint) {
			distination = p;
			break;
		}
	}

	//OnArrivalPoint‚ÉƒCƒxƒ“ƒg‚ð“o˜^
	for (auto p : movePoints)
	{
		p->OnPointArrival.AddDynamic(this, &UAutoMove::PoinArrival);
	}

	for (const auto p : movePoints) {
		p->targetDistination = distination;
	}

	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAutoMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if(distination == nullptr) return;
	if (!isMoving) return;

	FVector direction =  distination->GetActorLocation() - parentActor->GetActorLocation();
	IMoveable::Execute_Move(parentActor, direction);

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UAutoMove::PoinArrival(AMovePoint* point, AMovePoint* next)
{
	if (next != nullptr)
	{
		distination = next;
		for (auto p : movePoints){
			p->targetDistination = next;
		}

		if (point->waitPoint) {
			isMoving = false;
		}
	}
	else
	{
		isMoving = false;
	}
}

