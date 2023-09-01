// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPunch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSnapFingers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFakeOut);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSCARING_API UPlayerActionEvent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerActionEvent();	

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PlayerActionEvent")
	FOnPunch OnPunch;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PlayerActionEvent")
	FOnSnapFingers OnSnapFingers;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "PlayerActionEvent")
	FOnFakeOut OnFakeOut;
};
