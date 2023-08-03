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
	//©g‚ª”jŠü‚³‚ê‚½‚Æ‚«‚ÉŒÄ‚Î‚ê‚éƒCƒxƒ“ƒg‚ğ“o˜^
}

void ARestArea::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//onRestAreaDelegate.Broadcast();
}
void ARestArea::Destroyed()
{
	//onRestAreaDelegate.Broadcast();
}
// Called every frame
void ARestArea::Tick(float DeltaTime)
{

}
void ARestArea::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if (onRestAreaDelegate.IsBound())
		{
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("StepOn"));
		}
		Destroy();
	}
}
