// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeBase.h"
#include "SnakeTail.h"
#include "Food.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < startSize; i++)
	{
		SpawnTail();
	}
	for (int i = 0; i < foodAmount; i++)
	{
		SpawnFood();
	}
}


// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	FVector2D target;
	if (IsValid())
	{
		target = GetDirection();
		target = FVector2D{target.Y, -target.X };
	}
	else
	{
		target = GetDirectionAI();
	}
	FVector temp;

	temp = FMath::VInterpConstantTo(FVector{ direction.X, direction.Y, 0 }, FVector{ target.X, target.Y, 0}, DeltaTime, turnSpeed);
	direction = { temp.X, temp.Y };
	direction.Normalize();
	Move(DeltaTime);
}

// Called to bind functionality to input
void ASnakeBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
FVector2D ASnakeBase::UpdateMouse(FVector2D mousePos, FVector2D screenSize)
{
	FVector2D half = screenSize / 2.0;
	FVector2D target = mousePos - half;;
	target.Normalize();
	if (target == FVector2D{ 0,0 })
		target = FVector2D{ 0,1 };

	return target;
}

FVector2D ASnakeBase::GetDirection()
{
	float mouseX;
	float mouseY;
	int viewX;
	int viewY;
	pController->GetViewportSize(viewX, viewY);
	pController->GetMousePosition(mouseX, mouseY);
	return UpdateMouse({ mouseX,mouseY }, { (float)viewX, (float)viewY });
}

FVector2D ASnakeBase::GetDirectionAI()
{
	return aiDirection;
}
bool ASnakeBase::IsValid()
{
	return pController != nullptr;
}

void ASnakeBase::Move(float deltaTime)
{
	FTransform trans = GetActorTransform();

	trans.SetLocation(trans.GetLocation() + (FVector{ direction.X, direction.Y, 0} * deltaTime * speed));

	SetActorTransform(trans);
}

void ASnakeBase::SpawnTail()
{
	size++;
	FActorSpawnParameters SpawnInfo;
	FTransform trans;

	if (lastTail == nullptr)
	{
		trans = GetActorTransform();
		trans.SetLocation(trans.GetLocation() + FVector{0,300,0});
	}
	else 

		trans = lastTail->GetActorTransform();

	AActor* t = GetWorld()->SpawnActor<AActor>(tailBlueprint, trans, SpawnInfo);
	if (!t) return; 
	ASnakeTail* tail = Cast<ASnakeTail>(t);
	if (!tail) return; 

	if(lastTail == nullptr)
		tail->SetParent((AActor*)(this), speed);
	else
		tail->SetParent(lastTail, speed);

	lastTail = t;
}

void ASnakeBase::SpawnFood()
{
	FActorSpawnParameters SpawnInfo;
	FTransform trans;

	AActor* t = GetWorld()->SpawnActor<AActor>(foodBlueprint, trans, SpawnInfo);
	if (!t) return;
	AFood* food = Cast<AFood>(t);
	if (!food) return;

	food->SpawnFood();
}

void ASnakeBase::NextLevel()
{
	size = 0;
	currentLevel++;
	speed += speedIncrease;
	foodRequirement += foodRequirementIncrease;

	FTransform trans = GetActorTransform();
	trans.SetLocation(FVector{0, 0, 100 });
	SetActorTransform(trans);
	startingInvic = GetGameTimeSinceCreation()+1;

	AActor* t = lastTail;
	while(t != this && t != nullptr)
	{
		t->Destroy();
		t = ((ASnakeTail*)t)->parent;
	}

	lastTail = (AActor*)this;

	for (int i = 0; i < startSize; i++)
	{
		SpawnTail();
	}
}