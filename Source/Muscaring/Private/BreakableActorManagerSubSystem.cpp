// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActorManagerSubSystem.h"

bool UBreakableActorManagerSubSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	if (UWorld* WorldOuter = Cast<UWorld>(Outer))
	{
		if (AMuscaringWorldSettings* worldSettings = Cast<AMuscaringWorldSettings>(WorldOuter->GetWorldSettings()))
		{
			return worldSettings->useBreakableActorManager;
		}
	}

	return false;
}

TArray<UGeometryCollectionComponent*> UBreakableActorManagerSubSystem::GetGeometryCollectionComponents()
{
	TArray<UGeometryCollectionComponent*> result;

	for (auto actor : breakableActors_)
	{
		result.Add(actor->GetComponentByClass<UGeometryCollectionComponent>());
	}

	return result;
}