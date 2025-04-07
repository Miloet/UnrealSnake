// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeTail.generated.h"


UCLASS()
class SNUK_API ASnakeTail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeTail();

	float* parentSpeed;

	UPROPERTY(EditAnywhere, Category = "Value")
	float distance = 1;

	UPROPERTY(EditAnywhere, Category = "Value")
	AActor* parent;

	UFUNCTION(BlueprintCallable)
	void Move(float deltaTime, FVector parentLocation);

	UFUNCTION(BlueprintCallable)
	void SetParent(AActor* actor, float& speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
