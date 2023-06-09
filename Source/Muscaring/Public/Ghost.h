// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "AIController.h"
#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ghost.generated.h"
UCLASS()
class MUSCARING_API AGhost : public AAIController
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//Scene Component
	UPROPERTY(EditAnyWhere)
		TObjectPtr<USceneComponent> DefaultSceneRoot;
	//Skeltal Meshを追加
    UPROPERTY(EditAnyWhere)
		TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
    //arrow componentを追加
    UPROPERTY(VisibleAnyWhere)
		TObjectPtr<UArrowComponent> ArrowComponent;
    
};
