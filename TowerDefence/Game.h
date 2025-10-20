#pragma once
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include "Direction.h"
#include <vector>
#include <SDL.h>
#include <memory>
#include "Wave.h"


class Game
{
private:
	// Game 
	bool gameOver = false;
	bool waveStart = false; // Wait for input to start wave (waveStart = true during waves)
	const int width = 25;
	const int height = 25;
	int baseHealth = 10;
	int money = 500;
	int spawnTick = 0;
	int gridSize = 24;
	int currentWave = 0;
	

	// Path coordinates
	int pathX[100], pathY[100];
	int pathLength = 0;
	bool pathMove;

	// Input
	int cursorX, cursorY;
	Direction cursorDir;

	// Enemy vectors
	std::vector<std::unique_ptr<Enemy>> enemies; // Store Enemy pointers
	std::vector<std::unique_ptr<Tower>> towers; // Store Tower pointers
	std::vector<std::unique_ptr<Wave>> waves;
	std::vector<Projectile> projectiles; // Store Projectile instances
	

	// Render
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	// Render
	Game();
	~Game();


	// Game functions
	void Setup();
	void Logic();
	void Input();
	void createPath();
	void Render();

	bool getGameOver() const { return gameOver; }
};

