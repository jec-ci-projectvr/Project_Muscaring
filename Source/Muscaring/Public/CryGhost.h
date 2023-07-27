// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NormalGhost.h"
#include "CryGhost.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ACryGhost : public ANormalGhost
{
	GENERATED_BODY()
	
public:
	ACryGhost();
protected:
	virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void OnSeePlayer(APawn* Pawn) override;
	UFUNCTION()
	virtual void ChangeState() override;
    UFUNCTION()
	virtual void ChangeMoveSpeed() override;

};
