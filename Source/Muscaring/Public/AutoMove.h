// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "MovePoint.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AutoMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSCARING_API UAutoMove : public UActorComponent
{
	GENERATED_BODY()

	UWorld* world_;

	//�����Ă��邩�ǂ���
	bool isMoving_;

	//�e�A�N�^�[
	TObjectPtr<AActor> parentActor_;

	//�e�A�N�^�[��AI�R���g���[���[
	TObjectPtr<AController> controller_;

	//���݂̖ړI�n
	TObjectPtr<AMovePoint> destination_;


	//��]�����ǂ���
	bool isRotating_;

	//��]�X�s�[�h
	UPROPERTY(EditAnywhere, Category = "Rotate")
	float rotationSpeed_;

	//�ړI�n�Ɍ������ĉ�]������
	void RotateToDestination();

public:	
	// Sets default values for this component's properties
	UAutoMove();

	UFUNCTION(BlueprintPure)
	bool IsMoving() { return isMoving_; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//�ړI�n�ɓ��������Ƃ��̏���
	UFUNCTION()
	void PointArrival(AMovePoint* point);

	//�ړI�n���o�������Ƃ��̏���
	UFUNCTION()
	void PointDeparture(AMovePoint* point, AMovePoint* next);
};
