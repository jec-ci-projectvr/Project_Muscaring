// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionEvent.h"

// Sets default values for this component's properties
UPlayerActionEvent::UPlayerActionEvent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPlayerActionEvent::BeginPlay()
{
	OnSnapFingers.AddDynamic(this, &UPlayerActionEvent::PlaySnapSound);
	OnFakeOut.AddDynamic(this, &UPlayerActionEvent::PlayFakeOutSound);
	// ...
}

void UPlayerActionEvent::PlaySnapSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), snapSound, GetOwner()->GetActorLocation());
}

void UPlayerActionEvent::PlayFakeOutSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), fakeOutSound, GetOwner()->GetActorLocation());
}




