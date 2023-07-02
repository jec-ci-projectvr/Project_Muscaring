// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "BreakableActor.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ABreakableActor : public AGeometryCollectionActor
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	static TArray<ABreakableActor*> breakableActors;

	UFUNCTION(BlueprintPure)
	TArray<ABreakableActor*> GetActors();
};
