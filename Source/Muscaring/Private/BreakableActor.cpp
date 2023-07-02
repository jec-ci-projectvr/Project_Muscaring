// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

TArray<ABreakableActor*> ABreakableActor::breakableActors;
void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	ABreakableActor::breakableActors.Add(this);	
}

TArray<ABreakableActor*> ABreakableActor::GetActors()
{
	return breakableActors;
}
