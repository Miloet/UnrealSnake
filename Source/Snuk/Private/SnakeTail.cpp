// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeTail.h"

// Sets default values
ASnakeTail::ASnakeTail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakeTail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeTail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (parent == nullptr) return;

	FVector v = GetActorTransform().GetLocation();
	FVector p = parent->GetActorTransform().GetLocation();

	float dist = FVector::Distance(p, v);
	if (dist > distance)
	{
		Move(DeltaTime, p);
	}
}

void ASnakeTail::Move(float deltaTime, FVector parentLocation)
{
	FTransform trans = GetActorTransform();
	
	FVector pos = trans.GetLocation();
	FVector dir = parentLocation - pos;
	float dist = FVector::Dist(parentLocation, pos);
	dir.Normalize();
	pos += dir * std::min(deltaTime * *parentSpeed, dist);

	trans.SetLocation(pos);

	SetActorTransform(trans);
}

void ASnakeTail::SetParent(AActor* actor, float& speed)
{
	parentSpeed = &speed;
	parent = actor;
}
