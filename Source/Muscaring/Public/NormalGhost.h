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
		virtual void OnSeePlayer(APawn* Pawn);

	//scarePointに応じてstateを変更する
	UFUNCTION()
	virtual void ChangeState();
	UFUNCTION()
	virtual void ChangeMoveSpeed();
UFUNCTION()
void SetDefaultMoveSpeed(const float speed);
	//escapeMoveSpeedのgetter
	UFUNCTION()
float GetDefaultMoveSpeed() const;
//escapeMoveSpeedのsetter
	UFUNCTION()
void SetEscapeMoveSpeed(const float speed);
//escapeMoveSpeedのgetter
	UFUNCTION()
float GetEscapeMoveSpeed() const;

//scarePointのgetter
UFUNCTION()
uint32 GetScarePoint() const;
//scarePointのsetter
UFUNCTION()
void SetScarePoint(const uint32 scarePoint);
	void SettingMostNearRestArea();
private:
	UPROPERTY(EditAnyWhere)
	uint32 scarePoint_;

	UPROPERTY(EditAnyWhere)
	GhostState state_;

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
	bool onSeeOnce_;

	UPROPERTY(EditAnyWhere)
	float defaultMoveSpeed_;

	UPROPERTY(EditAnyWhere)
	float escapeMoveSpeed_;

	
};
