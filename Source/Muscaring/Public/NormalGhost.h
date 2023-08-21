// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceGhostState.h"
#include "Enum_GhostState.h"
#include "GameFramework/Character.h"
#include "Ghost.h"
#include "PlayerActionEvent.h"
#include "NormalGhost.generated.h"
UCLASS()
class MUSCARING_API ANormalGhost : public AGhost
{
	GENERATED_BODY()
		
public:
	// Sets default values for this character's properties
	ANormalGhost();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//‹ŠE‚Ì”ÍˆÍ‚ğİ’è‚·‚é
public:
	/*UPROPERTY(EditAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		virtual void OnSeePlayer(APawn* Pawn);*/

	//scarePoint‚É‰‚¶‚Ästate‚ğ•ÏX‚·‚é
	UFUNCTION()
	virtual void ChangeState() override;
	UFUNCTION()
	void ChangeMoveSpeed() override;
	virtual void ListenSnapFingers() override;
	virtual void ListenFakeOut() override;
	virtual void StepOnRestArea() override;
};
