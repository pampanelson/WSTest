// Fill out your copyright notice in the Description page of Project Settings.


#include "NewActorComponent.h"

// Sets default values for this component's properties
UNewActorComponent::UNewActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	myX = 0.0f;
}


// Called when the game starts
void UNewActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNewActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    myX += 1.0;
    AActor* myBoss = GetOwner();
    FString myname = myBoss->GetHumanReadableName();
    UE_LOG(LogTemp, Warning, TEXT("%s"), *myname);

	
	myBoss->SetActorLocation(FVector(myX,0.0f,50.0f));
}

