// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NormalGhost.generated.h"

UCLASS()
class MUSCARING_API ANormalGhost : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ANormalGhost()
		:state(GhostState::Idle)
		, onSeeOnce(false)
		, minimumDist(10000.f)
		, scarePoint(0)
		, player(nullptr)
		, restArea(nullptr)
		, defaultMoveSpeed(60.f)
        , escapeMoveSpeedSpeed(90.f)
	{

	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//éãäEÇÃîÕàÕÇê›íËÇ∑ÇÈ
public:
	UPROPERTY(EditAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);
	int scarePoint;
	enum class GhostState
	{
		Idle,Approach,Scare,Escape,Swoon
	};
	TObjectPtr<AActor> restArea;
    GhostState state;
	float minimumDist;
	//pawnÇÃÉ|ÉCÉìÉ^
    TObjectPtr<APawn> player;
	bool onSeeOnce;
	const float defaultMoveSpeed;
	const float escapeMoveSpeedSpeed;
};
