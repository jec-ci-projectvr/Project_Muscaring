// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

TArray<ABreakableActor*> ABreakableActor::breakableActors;
TArray<UGeometryCollectionComponent*> ABreakableActor::geometryCollectionComponents;

void ABreakableActor::BeginPlay()
{
	isBreaked = false;

	auto g = this->GetComponentByClass<UGeometryCollectionComponent>();
	g->OnChaosBreakEvent.AddDynamic(this, &ABreakableActor::Break);

	//�ŏ��̃t���[���Ŏ������g�ƃR���|�[�l���g���X�^�e�B�b�N�z��ɒǉ�����
	breakableActors.Add(this);
	geometryCollectionComponents.Add(g);

	Super::BeginPlay();
}

void ABreakableActor::Break(const FChaosBreakEvent& breakEvent)
{
	isBreaked = true;
}

bool ABreakableActor::CheckBreaked()
{
	return isBreaked;
}

TArray<ABreakableActor*> ABreakableActor::GetBreakableActors() 
{
	return breakableActors;
}

TArray<UGeometryCollectionComponent*> ABreakableActor::GetGeometryCollectionComponents()
{
	return geometryCollectionComponents;
}
