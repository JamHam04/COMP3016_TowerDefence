#pragma once
#include <vector>
#include "Enemy.h"
#include <memory>

// Wave class to manage enemy waves
class Wave {
private:
	// Enemies in the wave
	std::vector<std::unique_ptr<Enemy>> enemies;

	// Wave stats
	int enemiesRemaining;
	int enemiesSpawned;
	int enemyType;
	int spawnRate;
	int spawnTick;
public:
	// Wave constructor
	Wave(int rate, int totalEnemies, int type);

	// Spawn enemies based on spawn rate
	std::vector<std::unique_ptr<Enemy>> spawnEnemies();

	// Check if wave is complete
	bool waveComplete();

};