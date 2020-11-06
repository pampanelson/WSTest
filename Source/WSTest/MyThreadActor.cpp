// Fill out your copyright notice in the Description page of Project Settings.


#include "MyThreadActor.h"

// Sets default values
AMyThreadActor::AMyThreadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyThreadActor::BeginPlay()
{
	Super::BeginPlay();
	DoMyAsyncTask();
	
}

// Called every frame
void AMyThreadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyThreadActor::DoMyAsyncTask()
{
	/*Create a new Task and pass as a parameter our MaxPrime
	Then, tell that Task to execute in the background.
 
	The FAutoDeleteAsyncTask will make sure to delete the task when it's finished.
 
	Multithreading requires cautious handle of the available threads, in order to avoid
	race conditions and strange bugs that are not easy to solve
	
	Fortunately, UE4 contains a class (FAutoDeleteAsyncTask) which handles everything by itself
	and the programmer is able to perform async operations without any real effort.*/
 
	(new FAutoDeleteAsyncTask<MyAsyncTask>())->StartBackgroundTask();
}