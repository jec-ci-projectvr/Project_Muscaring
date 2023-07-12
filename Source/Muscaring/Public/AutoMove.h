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

public:	
	// Sets default values for this component's properties
	UAutoMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool isMoving;
	TObjectPtr<AActor> parentActor;

	TArray<TObjectPtr<AMovePoint>> movePoints;

	TObjectPtr<AMovePoint> distination;

	UFUNCTION()
	void PoinArrival(AMovePoint* point, AMovePoint* next);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
