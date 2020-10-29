// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ListenSocket = NULL;


}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp,Display,TEXT("hello"));
    StartUDPReceiver();

	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    //Clear all sockets!
    //        makes sure repeat plays in Editor dont hold on to old sockets!
    if (ListenSocket)
    {
        ListenSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
    }
    ListenSocket = nullptr;
}


void AMyActor::StartUDPReceiver() {

    ListenSocket = FUdpSocketBuilder(TEXT("WSTest"))
        .BoundToPort(65000)
        .Build();

    //UE_LOG(LogTemp, Warning, TEXT("UDP start"));
}