// Fill out your copyright notice in the Description page of Project Settings.


#include "RestArea.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "DestroyedRestArea.h"
// Sets default values
ARestArea::ARestArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TObjectPtr<UBoxComponent> boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//�C�x���g��o�^
}

// Called when the game starts or when spawned
void ARestArea::BeginPlay()
{
	//���g���j�����ꂽ�Ƃ��ɌĂ΂��C�x���g��o�^
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGhost::StaticClass(),Ghosts);
	for (auto loop : Ghosts)
	{
		//�L���X�g
		loop = Cast<AGhost>(loop);
	}
}

void ARestArea::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	for (auto loop : Ghosts)
	{
		IDestroyedRestArea::Execute_DestroyedRestArea(loop);
	}
    UKismetSystemLibrary::PrintString(GetWorld(), TEXT("EndPlay"));
}
// Called every frame
void ARestArea::Tick(float DeltaTime)
{
}
void ARestArea::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if (onRestAreaDelegate.IsBound())
		{
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("StepOn"));
			//�I�u�W�F�N�g�̔j��
			this->Destroy();
		}
	}
}
