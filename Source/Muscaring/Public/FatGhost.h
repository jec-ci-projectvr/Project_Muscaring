// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ghost.h"
#include "FatGhost.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API AFatGhost : public AGhost
{
	GENERATED_BODY()
public:
	AFatGhost();

private:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void ChangeState() override;

	void ChangeMoveSpeed() override;

	void ChangeExpression() override;

	void LoadAllExpression() override;

	void ListenSnapFingers() override;

	void ListenFakeOut() override;
};
