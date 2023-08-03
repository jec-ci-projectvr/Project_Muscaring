// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RestArea.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestAreaDelegate);

//DECLARE_DYNAMIC_DELEGATE(FOnActorDestroyed)

UCLASS()
class MUSCARING_API ARestArea : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ARestArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//overlap begin function
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FOnRestAreaDelegate onRestAreaDelegate;
};
