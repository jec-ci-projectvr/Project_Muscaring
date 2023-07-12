// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "MovePoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPointArrival, AMovePoint*, point, AMovePoint*, next);


UCLASS()
class MUSCARING_API AMovePoint : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AMovePoint();

	// Scene Component
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	// StaticMesh Component
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	TObjectPtr<AMovePoint> targetDistination;

	UPROPERTY(EditAnywhere)
	bool entryPoint;

	UPROPERTY(EditAnywhere)
	bool waitPoint;

	UPROPERTY(EditAnywhere)
	float arrivalDistance;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AMovePoint> nextPoint;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> targetActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnPointArrival OnPointArrival;

};
