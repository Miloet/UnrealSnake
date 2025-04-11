// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSpawner.generated.h"


UCLASS()
class SNUK_API ALevelSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelSpawner();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	void CreateLevel(int index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float area;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	TSubclassOf<AActor> wallBlueprint;

	class LevelLayout
	{
		public:
		const char empty = '0';
		const char full = '1';

		static const std::string FullRow;
		static const std::string BlockedRow;

		const std::vector<std::string> walls ={
			FullRow,
			BlockedRow,
			BlockedRow,
			BlockedRow,
			BlockedRow,

			BlockedRow,
			BlockedRow,
			BlockedRow,
			BlockedRow,
			BlockedRow,

			BlockedRow,
			BlockedRow,
			BlockedRow,
			BlockedRow,
			BlockedRow,

			BlockedRow,
			BlockedRow,
			BlockedRow,
			BlockedRow,
			FullRow
		};


		std::vector<std::string> level =
		{

		};
		
		bool GetValue(int x, int y);

		LevelLayout(std::vector<std::string> values) : level(values) {}

		
	};

	std::vector<LevelLayout> levels = std::vector<LevelLayout>();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

