#include "Wave.h"

Wave::Wave(int rate, int totalEnemies, int type) : spawnRate(rate), enemiesRemaining(totalEnemies), enemyType(type),enemiesSpawned(0), spawnTick(0)
{}

bool Wave::spawnEnemies() {
	if (enemiesSpawned >= enemiesRemaining)
		return true; // Complete wave
	spawnTick++;
	if (spawnTick >= spawnRate) {
		// Enemy types
		switch (enemyType) {
		case 0:
			enemies.push_back(std::make_unique<smallEnemy>());
			break;
		case 1:
			enemies.push_back(std::make_unique<mediumEnemy>());
			break;
		}
		enemiesSpawned++; // Increase enemy spawn 
		spawnTick = 0; // Reset spawn tick
	}
	return false;
}