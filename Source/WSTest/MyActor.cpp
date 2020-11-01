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

    SendHttpJsonRequest(FString("https://reqbin.com/echo/get/json"));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ListenSocket == nullptr) return;

	uint32 PendingData = 0;
    uint8 attysdata[0x10000];

	ListenSocket->HasPendingData(PendingData);

	if (PendingData > 0)
	{

		int32 BytesRead;
		int nSamples = 0;

		do {
			ListenSocket->Recv(attysdata, PendingData, BytesRead);
			nSamples++;


			ListenSocket->HasPendingData(PendingData);

		} while (PendingData > 0);

        UE_LOG(LogTemp,Display,TEXT("attysdata %d"),attysdata[0]);


	}


    // GEngine->AddOnScreenDebugMessage(10,100,FColor::Green,FString::Printf(TEXT("Hello %s"),TEXT("你好")));


        FString TestHUDString = FString(TEXT("Buy this crap!你好"));


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


void AMyActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		GLog->Log("Hey we received the following response!");
		GLog->Log(Response->GetContentAsString());

        UE_LOG(LogTemp,Display,TEXT("got a http reply"));

	}
}


 
void AMyActor::SendHttpRequest(const FString& Url, const FString& RequestContent)
{
	
    UE_LOG(LogTemp,Display,TEXT("send a http req"));


	//Creating a request using UE4's Http Module
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
 
	//Binding a function that will fire when we receive a response from our request
	Request->OnProcessRequestComplete().BindUObject(this, &AMyActor::OnResponseReceived);
 
	//This is the url on which to process the request
	Request->SetURL(Url);
	//We're sending data so set the Http method to GET
	Request->SetVerb("GET");
 

 	// //We're sending data so set the Http method to POST
	// Request->SetVerb("POST");

	//Tell the host that we're an unreal agent
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
 
	//In case you're sending json you can also make use of headers using the following command. 
        //Just make sure to convert the Json to string and use the SetContentAsString.
	//Request->SetHeader("Content-Type", TEXT("application/json"));
	//Use the following command in case you want to send a string value to the server
	//Request->SetContentAsString("Hello kind server.");
 
	//Send the request
	Request->ProcessRequest();
}


void AMyActor::SendHttpJsonRequest(const FString& Url)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();;
	Request->OnProcessRequestComplete().BindUObject(this, &AMyActor::OnJsonResponseReceived);
	//This is the url on which to process the request
	Request->SetURL(Url);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}


void AMyActor::OnJsonResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		GLog->Log("Hey we received the following response!");
		GLog->Log(Response->GetContentAsString());

        UE_LOG(LogTemp,Display,TEXT("got a http json reply"));

		



			//Create a pointer to hold the json serialized data
		TSharedPtr<FJsonObject> JsonObject;

		//Create a reader pointer to read the json data
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		//Deserialize the json data given Reader and the actual object to deserialize
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			//Get the value of the json object by field name
			// int32 recievedInt = JsonObject->GetIntegerField("customInt");

			//Output it to the engine
			// GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
		}





	}
}

