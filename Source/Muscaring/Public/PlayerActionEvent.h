// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerActionEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSnapFingers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFakeOut);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSCARING_API UPlayerActionEvent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* snapSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* fakeOutSound;

	UFUNCTION()
	void PlaySnapSound();

	UFUNCTION()
	void PlayFakeOutSound();

public:	
	// Sets default values for this component's properties
	UPlayerActionEvent();	

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PlayerActionEvent")
	FOnSnapFingers OnSnapFingers;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PlayerActionEvent")
	FOnFakeOut OnFakeOut;
};
