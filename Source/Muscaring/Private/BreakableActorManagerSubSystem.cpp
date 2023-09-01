// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActorManagerSubSystem.h"

TArray<UGeometryCollectionComponent*> UBreakableActorManagerSubSystem::GetGeometryCollectionComponents()
{
	TArray<UGeometryCollectionComponent*> result;

	for (auto actor : breakableActors)
	{
		result.Add(actor->GetComponentByClass<UGeometryCollectionComponent>());
	}

	return result;
}