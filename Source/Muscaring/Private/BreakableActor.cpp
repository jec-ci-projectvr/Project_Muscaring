// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

TArray<ABreakableActor*> ABreakableActor::breakableActors;
TArray<UGeometryCollectionComponent*> ABreakableActor::geometryCollectionComponents;

void ABreakableActor::BeginPlay()
{
	//�ŏ��̃t���[���Ŏ������g�ƃR���|�[�l���g���X�^�e�B�b�N�z��ɒǉ�����
	breakableActors.Add(this);
	geometryCollectionComponents.Add(GetComponentByClass<UGeometryCollectionComponent>());

	Super::BeginPlay();
}

TArray<ABreakableActor*> ABreakableActor::GetBreakableActors() 
{
	return breakableActors;
}

TArray<UGeometryCollectionComponent*> ABreakableActor::GetGeometryCollectionComponents()
{
	return geometryCollectionComponents;
}
