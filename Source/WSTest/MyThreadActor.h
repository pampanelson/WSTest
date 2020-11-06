// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyThreadActor.generated.h"

UCLASS()
class WSTEST_API AMyThreadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyThreadActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, Category = MultiThreading)
	void DoMyAsyncTask();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

class MyAsyncTask : public FNonAbandonableTask
{

 
public:
	/*Default constructor*/
	MyAsyncTask()
	{
	}
 
	/*This function is needed from the API of the engine. 
	My guess is that it provides necessary information
	about the thread that we occupy and the progress of our task*/
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeCalculationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}
 
	/*This function is executed when we tell our task to execute*/
	void DoWork()
	{
 
		GLog->Log("--------------------------------------------------------------------");
		GLog->Log("<---- my task background thread ---->");
		GLog->Log("--------------------------------------------------------------------");
	}
};