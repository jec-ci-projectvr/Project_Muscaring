// Fill out your copyright notice in the Description page of Project Settings.


#include "RestArea.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARestArea::ARestArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARestArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARestArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARestArea::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{

	}
}
