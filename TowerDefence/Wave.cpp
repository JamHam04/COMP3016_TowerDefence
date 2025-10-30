#include "Wave.h"

// Wave constructor
Wave::Wave(int rate, int totalEnemies, int type) : spawnRate(rate), enemiesRemaining(totalEnemies), enemyType(type),enemiesSpawned(0), spawnTick(0)
{}

// Spawn enemies based on spawn rate
std::vector<std::unique_ptr<Enemy>> Wave::spawnEnemies() {
	std::vector<std::unique_ptr<Enemy>> waveEnemies;

	spawnTick++; // Increment spawn tick
	if (spawnTick >= spawnRate) {
		// Enemy types
		switch (enemyType) {
		case 0:
			waveEnemies.push_back(std::make_unique<smallEnemy>());
			break;
		case 1:
			waveEnemies.push_back(std::make_unique<mediumEnemy>());
			break;

		case 2:
			waveEnemies.push_back(std::make_unique<largeEnemy>());
			break;
		
	}
		enemiesSpawned++; // Increase enemy spawn 
		spawnTick = 0; // Reset spawn tick
	}
	return waveEnemies;
}

// Check if wave is complete
bool Wave::waveComplete() {
	return enemiesSpawned >= enemiesRemaining;
}