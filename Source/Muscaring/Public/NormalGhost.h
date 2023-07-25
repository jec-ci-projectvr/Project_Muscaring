// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceGhostState.h"
#include "Enum_GhostState.h"
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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//視界の範囲を設定する
public:
	UPROPERTY(EditAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

	//scarePointに応じてstateを変更する
	UFUNCTION()
	virtual void ChangeState();
	virtual void ChangeMoveSpeed();
private:
	UPROPERTY(EditAnyWhere)
	uint32 scarePoint;

	UPROPERTY(EditAnyWhere)
	GhostState state;

	UPROPERTY()
	TObjectPtr<ARestArea> restArea;//restAreaのポインタ

	//targetとの最短距離
	UPROPERTY(EditAnyWhere)
	float minimumDist;

	//pawnのポインタ
    TObjectPtr<APawn> player;

	//NormalGhostAIのポインタ
    TObjectPtr<class ANormalGhostAI> normalGhostAI;


	//一度のみ視界に入ったかどうか
	UPROPERTY()
	bool onSeeOnce;

	UPROPERTY(EditAnyWhere)
	float defaultMoveSpeed=60.f;

	UPROPERTY(EditAnyWhere)
	float escapeMoveSpeed=90.f;

	//プレイヤーにヒットした際にtrueになる
	UPROPERTY()
	bool hitPlayer;
};
