#include "Wave.h"

Wave::Wave(int rate, int totalEnemies, int type) : spawnRate(rate), enemiesRemaining(totalEnemies), enemyType(type),enemiesSpawned(0), spawnTick(0)
{}

std::vector<std::unique_ptr<Enemy>> Wave::spawnEnemies() {
	std::vector<std::unique_ptr<Enemy>> waveEnemies;

	spawnTick++;
	if (spawnTick >= spawnRate) {
		// Enemy types
		switch (enemyType) {
		case 0:
			waveEnemies.push_back(std::make_unique<smallEnemy>());
			break;
		case 1:
			waveEnemies.push_back(std::make_unique<mediumEnemy>());
			break;
		}
		enemiesSpawned++; // Increase enemy spawn 
		spawnTick = 0; // Reset spawn tick
	}
	return waveEnemies;
}

bool Wave::waveComplete() {
	return enemiesSpawned >= enemiesRemaining;
}