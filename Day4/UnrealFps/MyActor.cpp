// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealFps.h"
#include "MyActor.h"
#include "Engine.h"
#include <memory>

class TestClass
{
public:
	TestClass()
	{
		number = 5;
	}

	int number;
};

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// C++11 std shared pointers can be used normally 
	std::shared_ptr<TestClass> abc =
		//std::make_shared<TestClass>();
		std::shared_ptr<TestClass>(new TestClass());

	// Unreal shared pointers work similary
	TSharedPtr<TestClass> hello = TSharedPtr<TestClass>(new TestClass());
	hello->number++;
	hello.Reset();
	//Now hello is destroyed and cannot be used
	UE_LOG(LogStreaming, Log, TEXT("Hello"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, "Welcome to my UnrealFPS");
}

// Called every frame
void AMyActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator newRotation = GetActorRotation();
	newRotation.Yaw += DeltaTime * 20;
	SetActorRotation(newRotation);
}