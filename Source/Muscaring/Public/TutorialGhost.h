// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ghost.h"
#include "TutorialGhost.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ATutorialGhost : public AGhost
{
	GENERATED_BODY()
	
public:
	ATutorialGhost();
private:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void ChangeState() override;

	void ChangeMoveSpeed() override;

	void ListenSnapFingers() override;

	void ListenFakeOut() override;

	UPROPERTY()
		bool snapFingersFlag = false;
	UPROPERTY()
		bool fakeOutFlag = false;
};
