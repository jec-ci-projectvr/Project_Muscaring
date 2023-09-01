// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MuscaringWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API AMuscaringWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	bool useBreakableActorManager = true;

	
};
