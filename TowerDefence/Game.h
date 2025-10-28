#pragma once
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include "Direction.h"
#include <vector>
#include <SDL.h>
#include <memory>
#include "Wave.h"
#include <SDL_ttf.h>
#include <string>

class Game
{
private:
	// Game 
	bool gameOver = false;
	bool waveStart = false; // Wait for input to start wave (waveStart = true during waves)
	const int width = 25;
	const int height = 25;
	int spawnTick = 0;
	int gridSize = 24;
	int currentWave = 0;
	int specialWave = 5;
	bool openUpgradeMenu = false;
	int selectedTower = 0;
	bool baseDamaged = false;

	// Game stats
	int baseHealth = 50;
	int money = 150;
	

	// Path coordinates
	int pathX[100], pathY[100];
	int pathLength = 0;
	bool pathMove;


	// Input
	int cursorX = 10, cursorY = 10;
	Direction cursorDir = UP;

	// Game vectors
	std::vector<std::unique_ptr<Enemy>> enemies; // Store Enemy pointers
	std::vector<std::unique_ptr<Tower>> towers; // Store Tower pointers
	std::vector<std::unique_ptr<Wave>> waves; // Store Wave pointers
	std::vector<Projectile> projectiles; // Store Projectile instances

	// Environmental effects
	struct floodArea {
		int x, y, w, h; 
		int specialRound;
		bool effectActive = false;
	};
	std::vector < floodArea > floodAreas;
	

	// Render
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	TTF_Font* fontSmall;

public:
	// Render
	Game();
	~Game();

	// Base damged 
	bool baseDamageEffect() { return baseDamaged; }
	void resetDamageEffect() { baseDamaged = false; }
	bool isbaseDamged() const { return baseDamaged; } 


	// Game functions
	void Setup();
	void Logic();
	void Input();
	void createPath();
	void createWaves();
	void Render();
	void drawHUD();
	void drawTowerControls();
	void drawUpgradeMenu();
	bool getGameOver() const { return gameOver; }
	bool isTileFree(int x, int y);
	bool isTileHUD(int x, int y);
	void updateWaves();
	void updateEnemies();
	void updateTowers();
	void updateProjectiles();
	void isGameOver();
};

