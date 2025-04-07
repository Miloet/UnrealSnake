// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeBase.generated.h"

UCLASS()
class SNUK_API ASnakeBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakeBase();

	FVector2D direction;
	AActor* lastTail;
	//bool isPlayer;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float startingInvic = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int foodRequirement = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int foodRequirementIncrease = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	bool isAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float speedIncrease = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int currentLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int startSize = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int foodAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	APlayerController* pController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	TSubclassOf<AActor> tailBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	TSubclassOf<AActor> foodBlueprint;

	void UpdateMouse(FVector2D mousePos, FVector2D screenSize);

	void Move(float deltaTime);
	virtual void GetDirection();
	virtual bool IsValid();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	void SpawnTail();
	UFUNCTION(BlueprintCallable, Category = "Functions")
	void SpawnFood();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	void NextLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
