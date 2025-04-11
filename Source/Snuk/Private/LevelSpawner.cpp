// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"

const std::string ALevelSpawner::LevelLayout::FullRow = "11111111111111111111";
const std::string ALevelSpawner::LevelLayout::BlockedRow = "10000000000000000001";

// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	levels.emplace_back(LevelLayout({
		"",
		"",
		"",
		"00000011111111000000",
		"",

		"",
		"",
		"",
		"",
		"",

		"",
		"",
		"",
		"",
		"",

		"",
		"00000011111111000000",
		"",
		"",
		""}));
	levels.emplace_back(LevelLayout({}));
	levels.emplace_back(LevelLayout({
		LevelLayout::FullRow,
		"10000000000000000001",
		"10000000000000000001",
		"10001110000001111001",
		"10001000000000001001",

		"10001000000000001001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",

		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10001000000000001001",

		"10001000000000001001",
		"10001110000001111001",
		"10000000000000000001",
		"10000000000000000001",
		LevelLayout::FullRow }));
	levels.emplace_back(LevelLayout({
		LevelLayout::FullRow,
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",

		"11111111100111111111",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",

		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"11111111100111111111",

		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		LevelLayout::FullRow }));
	levels.emplace_back(LevelLayout({
		LevelLayout::FullRow,
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",

		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",
		"10000000000000000001",

		"10000000000000000001",
		"10000000000000000001",
		"10000000100100000001",
		"10000000100100000001",
		"10000000000000000001",

		"10000001011010000001",
		"10000000100100000001",
		"10000000000000000001",
		"10000000000000000001",
		LevelLayout::FullRow }));
}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSpawner::CreateLevel(int index)
{
	auto world = GetWorld();
	LevelLayout* level = &levels.at(index % levels.size());
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	FTransform trans = GetActorTransform();

	

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (level->GetValue(x, y))
			{
				trans.SetLocation({
					(y * (20.0f / 19.0f) - 10.0f) / 10.0f * (950.0f * area*1.2f),
					(x * (20.0f / 19.0f) - 10.0f) / 10.0f * (950.0f * area * 1.2f), 50});
				auto actor = world->SpawnActor(wallBlueprint, &trans, spawnParams);
				actor->SetActorScale3D(FVector{ area * 1.2f, area * 1.2f, 1 });
			}
		}
	}
}

bool ALevelSpawner::LevelLayout::GetValue(int x, int y)
{
	if (!(level.size() > y) || level.size() == 0) return walls.at(y).at(x) == full;
	int sizey = level.size();
	int sizex = level.at(std::min(y, sizey - 1)).size();
	int lx = std::min(x, sizex - 1);
	int ly = std::min(y, sizey - 1);
	bool isWall = walls.at(y).at(x) == full;
	bool isLevel;

	if (level.at(ly).size() == 0) isLevel = false;
	else isLevel = level[ly][lx] == full;

	return isLevel || isWall;
}