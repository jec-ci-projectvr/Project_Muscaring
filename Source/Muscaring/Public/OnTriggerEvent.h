// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OnTriggerEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUSCARING_API UOnTriggerEvent : public UActorComponent
{
	GENERATED_BODY()
		FOnTriggerEvent OnTriggerEvent;

//public:	
//	// Sets default values for this component's properties
//	UOnTriggerEvent();
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
