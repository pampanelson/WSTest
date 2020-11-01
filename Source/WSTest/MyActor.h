// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "Runtime/Online/HTTP/Public/Http.h" // include for http request
#include "MyActor.generated.h"

UCLASS()
class WSTEST_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    FSocket* ListenSocket = nullptr;
    void StartUDPReceiver();
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;



	void SendHttpRequest(const FString& Url, const FString& RequestContent);	
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void SendHttpJsonRequest(const FString& Url);
	void OnJsonResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
