// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObjActor2.h"

// Sets default values
AMyObjActor2::AMyObjActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    VisualMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset1(TEXT("/Game/model/engine_Mesh_2.engine_Mesh_2"));

    if (CubeVisualAsset1.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeVisualAsset1.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }

}

// Called when the game starts or when spawned
void AMyObjActor2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyObjActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
    FRotator NewRotation = GetActorRotation();
    float RunningTime = GetGameTimeSinceCreation();
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
    NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
    float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
    NewRotation.Yaw += DeltaRotation;
    SetActorLocationAndRotation(NewLocation, NewRotation);
}

