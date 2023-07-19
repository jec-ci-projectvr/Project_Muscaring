// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovePoint.h"
#include "Moveable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AutoMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSCARING_API UAutoMove : public UActorComponent
{
	GENERATED_BODY()

	bool isMoving;
	TObjectPtr<AActor> parentActor;
	TArray<TObjectPtr<AMovePoint>> movePoints;
	TObjectPtr<AMovePoint> distination;

public:	
	// Sets default values for this component's properties
	UAutoMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void PointArrival(AMovePoint* point);

	UFUNCTION()
	void PointDeparture(AMovePoint* point, AMovePoint* next);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
