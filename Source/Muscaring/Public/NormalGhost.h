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
	ANormalGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//éãäEÇÃîÕàÕÇê›íËÇ∑ÇÈ
public:
	UPROPERTY(VisibleAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);
};
