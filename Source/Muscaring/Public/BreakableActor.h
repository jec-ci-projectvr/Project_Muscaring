// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "BreakableActor.generated.h"

/**
 * 
 */
UCLASS()
class MUSCARING_API ABreakableActor : public AGeometryCollectionActor
{
	GENERATED_BODY()

	static TArray<ABreakableActor*> breakableActors; //breakableActorsがすべて入ったスタティック配列
	static TArray<UGeometryCollectionComponent*> geometryCollectionComponents; //ジオメトリコレクションがすべて入ったスタティック配列

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure)
	static TArray<ABreakableActor*> GetBreakableActors(); //すべてのBreakableActorsの取得

	UFUNCTION(BlueprintPure)
	static TArray<UGeometryCollectionComponent*> GetGeometryCollectionComponents(); //すべてのジオメトリコレクションの取得
};
