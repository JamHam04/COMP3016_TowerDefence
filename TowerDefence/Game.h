#pragma once
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include "Direction.h"
#include <vector>

class Game
{
private:
	// Game 
	bool gameOver = false;
	bool waveStart = false; // Wait for input to start wave (waveStart = true during waves)
	const int width = 25;
	const int height = 25;
	int baseHealth = 10;
	int money = 100;
	int spawnTick = 0;
	

	// Path coordinates
	int pathX[100], pathY[100];
	int pathLength = 0;
	bool pathMove;

	// Input
	int cursorX, cursorY;
	Direction cursorDir;

	// Enemy vectors
	std::vector<Enemy> enemies; // Store Enemy instances
	std::vector<Tower> towers; // Store Tower instances
	std::vector<Projectile> projectiles; // Store Projectile instances
public:

	void Setup();
	void Draw();
	void Logic();
	void Input();
	void createPath();

	bool getGameOver() const { return gameOver; }
};

