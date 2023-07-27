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
	//���E�͈̔͂�ݒ肷��
public:
	UPROPERTY(EditAnyWhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;
	UFUNCTION()
		virtual void OnSeePlayer(APawn* Pawn);

	//scarePoint�ɉ�����state��ύX����
	UFUNCTION()
	virtual void ChangeState();
	UFUNCTION()
	virtual void ChangeMoveSpeed();
UFUNCTION()
void SetDefaultMoveSpeed(const float speed);
	//escapeMoveSpeed��getter
	UFUNCTION()
float GetDefaultMoveSpeed() const;
//escapeMoveSpeed��setter
	UFUNCTION()
void SetEscapeMoveSpeed(const float speed);
//escapeMoveSpeed��getter
	UFUNCTION()
float GetEscapeMoveSpeed() const;

//scarePoint��getter
UFUNCTION()
uint32 GetScarePoint() const;
//scarePoint��setter
UFUNCTION()
void SetScarePoint(const uint32 scarePoint);
	void SettingMostNearRestArea();
private:
	UPROPERTY(EditAnyWhere)
	uint32 scarePoint_;

	UPROPERTY(EditAnyWhere)
	GhostState state_;

	UPROPERTY()
	TObjectPtr<ARestArea> restArea;//restArea�̃|�C���^

	//target�Ƃ̍ŒZ����
	UPROPERTY(EditAnyWhere)
	float minimumDist;

	//pawn�̃|�C���^
    TObjectPtr<APawn> player;

	//NormalGhostAI�̃|�C���^
    TObjectPtr<class ANormalGhostAI> normalGhostAI;


	//��x�̂ݎ��E�ɓ��������ǂ���
	UPROPERTY()
	bool onSeeOnce_;

	UPROPERTY(EditAnyWhere)
	float defaultMoveSpeed_;

	UPROPERTY(EditAnyWhere)
	float escapeMoveSpeed_;

	
};
