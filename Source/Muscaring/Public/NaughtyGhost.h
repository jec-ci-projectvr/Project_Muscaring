// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ghost.h"
#include "NaughtyGhost.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ANaughtyGhost : public AGhost
{
	GENERATED_BODY()
public:
	ANaughtyGhost();
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
