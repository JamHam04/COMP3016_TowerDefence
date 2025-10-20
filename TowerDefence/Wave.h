#pragma once
#include <vector>
#include "Enemy.h"
#include <memory>

class Wave {
private:
	std::vector<std::unique_ptr<Enemy>> enemies;
	int enemiesRemaining;
	int enemiesSpawned;
	int enemyType;
	int spawnRate;
	int spawnTick;
public:
	Wave(int rate, int totalEnemies, int type);

	bool spawnEnemies();

	std::vector<std::unique_ptr<Enemy>> getEnemies() { return enemies; }
};