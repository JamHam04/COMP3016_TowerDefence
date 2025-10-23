#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Game.h"

#include <SDL.h>


using namespace std;

void Game::createPath() {
	int currentCol = 10; // Where path will start 
	int currentPath = 0;

	int previousCol = currentCol;

	// Loop throuugh rows
	for (int currentRow = 0; currentRow < height; currentRow++) {
		pathX[currentPath] = currentCol; // Set X to current col position
		pathY[currentPath] = currentRow; // Set Y to current row
		currentPath++; // Increment array index

		// Move left or right
		if (currentRow == 5) {
			currentCol += 3; // Move 3 right
		}

		if (currentRow == 12) {
			currentCol -= 7;
		}

		if (currentRow == 15) {
			currentCol += 5;
		}

		if (currentRow == 17) {
			currentCol -= 4;
		}

		if (currentRow == 20) {
			currentCol += 10;
		}

		// If col moves
		if (previousCol != currentCol) {
			int colDiff = abs(currentCol - previousCol);
			// Set direction to move
			int dir = (currentCol > previousCol) ? 1 : -1;

			for (int i = 1; i <= colDiff; i++) {
				pathX[currentPath] = previousCol + (i * dir);
				pathY[currentPath] = currentRow;
				currentPath++;
			}
		}
		previousCol = currentCol; // Update previousCol for if col moves again
	}
	pathLength = currentPath; //Stop path when it reaches end
}

void Game::Setup() {
	// Set Variables
	createPath();

	// Setup waves
	waves.push_back(std::make_unique<Wave>(25, 2, 0)); // 10 smallEnemy, spawn every 25 ticks
	waves.push_back(std::make_unique<Wave>(20, 3, 1));  // 5 mediumEnemy, spawn every 20 ticks
	waves.push_back(std::make_unique<Wave>(15, 5, 0)); // 15 smallEnemy, spawn every 15 ticks
	waves.push_back(std::make_unique<Wave>(15, 5, 0));

	// Setup special waves
	floodAreas.push_back({ 9, 6, 3, 5, 2, false });

	// TO DOL: ADD MORE WAVES
}

void drawTower(SDL_Renderer* renderer, int towerX, int towerY, int gridSize, Direction dir, towerType type) {
	
	int edgeOffset = 0;
		switch (type) {
		case BASIC:
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			edgeOffset = 8;
			break;
		case LONG_RANGE:
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			edgeOffset = 10;
			break;
		case HEAVY_DAMAGE:
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			edgeOffset = 6;
			break;
		case FOUR_WAY:
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			edgeOffset = 4;
			break;
		}

		SDL_Rect towerRect = { towerX * gridSize + edgeOffset / 2, towerY * gridSize + edgeOffset / 2, gridSize - edgeOffset, gridSize - edgeOffset };
		SDL_RenderFillRect(renderer, &towerRect);

		int centerX = towerX * gridSize + gridSize / 2;
		int centerY = towerY * gridSize + gridSize / 2;


		SDL_Rect barrelRect;
		int barrelLength = 0;
		int barrelWidth = 0;

		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Barrel color

		switch (type) {
		case BASIC:
			barrelLength = 12;
			barrelWidth = 8;
			switch (dir) {
			case UP:
				barrelRect = { centerX - barrelWidth / 2, centerY - barrelLength, barrelWidth, barrelLength };
				break;
			case RIGHT:
				barrelRect = { centerX, centerY - barrelWidth / 2, barrelLength, barrelWidth };
				break;
			case DOWN:
				barrelRect = { centerX - barrelWidth / 2, centerY, barrelWidth, barrelLength };
				break;
			case LEFT:
				barrelRect = { centerX - barrelLength, centerY - barrelWidth / 2, barrelLength, barrelWidth };
				break;
			}
			SDL_RenderFillRect(renderer, &barrelRect);
			break;

		case LONG_RANGE:
			barrelLength = 16;
			barrelWidth = 6;
			switch (dir) {
			case UP:
				barrelRect = { centerX - barrelWidth / 2, centerY - barrelLength, barrelWidth, barrelLength };
				break;
			case RIGHT:
				barrelRect = { centerX, centerY - barrelWidth / 2, barrelLength, barrelWidth };
				break;
			case DOWN:
				barrelRect = { centerX - barrelWidth / 2, centerY, barrelWidth, barrelLength };
				break;
			case LEFT:
				barrelRect = { centerX - barrelLength, centerY - barrelWidth / 2, barrelLength, barrelWidth };
				break;
			}
			SDL_RenderFillRect(renderer, &barrelRect);
			break;

		case HEAVY_DAMAGE:
			barrelLength = 12;
			barrelWidth = 10;
			switch (dir) {
			case UP:
				barrelRect = { centerX - barrelWidth / 2, centerY - barrelLength, barrelWidth, barrelLength };
				break;
			case RIGHT:
				barrelRect = { centerX, centerY - barrelWidth / 2, barrelLength, barrelWidth };
				break;
			case DOWN:
				barrelRect = { centerX - barrelWidth / 2, centerY, barrelWidth, barrelLength };
				break;
			case LEFT:
				barrelRect = { centerX - barrelLength, centerY - barrelWidth / 2, barrelLength, barrelWidth };
				break;
			}
			SDL_RenderFillRect(renderer, &barrelRect);
			break;

		case FOUR_WAY:
			barrelLength = 14;
			barrelWidth = 6;
			// Up
			barrelRect = { centerX - barrelWidth / 2, centerY - barrelLength, barrelWidth, barrelLength };
			SDL_RenderFillRect(renderer, &barrelRect);
			// Right
			barrelRect = { centerX, centerY - barrelWidth / 2, barrelLength, barrelWidth };
			SDL_RenderFillRect(renderer, &barrelRect);
			// Down
			barrelRect = { centerX - barrelWidth / 2, centerY, barrelWidth, barrelLength };
			SDL_RenderFillRect(renderer, &barrelRect);
			// Left
			barrelRect = { centerX - barrelLength, centerY - barrelWidth / 2, barrelLength, barrelWidth };
			SDL_RenderFillRect(renderer, &barrelRect);
			break;
		}
	
}

void Game::Render() {

	


	// Drawn background
	SDL_SetRenderDrawColor(renderer, 60, 130, 30, 255);
	SDL_RenderClear(renderer);

	// Draw random points?

		// Draw flood areas
	for (floodArea& flood : floodAreas) {
		if (flood.effectActive) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_Rect floodRect = { flood.x * gridSize, flood.y * gridSize, flood.w * gridSize, flood.h * gridSize };
			SDL_RenderFillRect(renderer, &floodRect);
		}
		else if (!flood.effectActive) {
			SDL_SetRenderDrawColor(renderer, 60, 120, 30, 255);
			SDL_Rect floodRect = { flood.x * gridSize, flood.y * gridSize, flood.w * gridSize, flood.h * gridSize };
			SDL_RenderFillRect(renderer, &floodRect);
		}
	}


	// Draw grid
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); 
	for (int i = 0; i < height; i++) { // Rows
		for (int j = 0; j < width; j++) { // Columns
			SDL_Rect mapRect = { j * gridSize, i * gridSize, gridSize, gridSize };
			SDL_RenderDrawRect(renderer, &mapRect);
		}
	}

	// Draw path
	SDL_SetRenderDrawColor(renderer, 120, 100, 60, 255); 
	for (int i = 0; i < pathLength; i++) {
		SDL_Rect pathTile = { pathX[i] * gridSize, pathY[i] * gridSize, gridSize, gridSize };
		SDL_RenderFillRect(renderer, &pathTile);
	}
	

	// Draw enemies
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int enemy = 0; enemy < enemies.size(); enemy++) {
		int circleX = enemies[enemy]->getX() * gridSize + 12; // Circle center X pixel (tileX * tileSize + tileSize/2)
		int circleY = enemies[enemy]->getY() * gridSize + 12; // Circle center Y pixel (tileX * tileSize + tileSize/2)
		int radius = 10; // Circle size

		// Switch color based on enemy type:


		// Loop through tile and draw pixel within radius
		for (int yOffset = -radius; yOffset <= radius; yOffset++) {
			for (int xOffset = -radius; xOffset <= radius; xOffset++) {
				// If within radius 
				if (xOffset * xOffset + yOffset * yOffset <= radius * radius) {
					SDL_RenderDrawPoint(renderer, circleX + xOffset, circleY + yOffset);
				}
			}
		}
	}



	
	// Draw Tower
	for (int t = 0; t < towers.size(); t++) {
		drawTower(renderer, towers[t]->getTowerX(), towers[t]->getTowerY(), gridSize, towers[t]->getRotation(), towers[t]->getTowerType());
	}




	// Draw path
	bool path = false;
	// Loop through map
	for (int k = 0; k < pathLength; k++) {
		if (pathX[k] == cursorX && pathY[k] == cursorY) { // If position is a path
			path = true; // Set position as path
			break;
		}
	}

	// Draw cursor box
	if (path)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red if on path
	else
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White normal
	SDL_Rect cursorRect = { cursorX * gridSize, cursorY * gridSize, gridSize, gridSize };
	SDL_RenderDrawRect(renderer, &cursorRect);

	// Draw cursor arrow
	int centerX = cursorX * gridSize + gridSize / 2;
	int centerY = cursorY * gridSize + gridSize / 2;
	int cusorLength = 10; 


	SDL_Rect arrowRect;

	switch (cursorDir) {
	case UP:
		arrowRect = { centerX - 2, centerY - cusorLength, 4, cusorLength };
		break;
	case RIGHT:
		arrowRect = { centerX, centerY - 2, cusorLength, 4 };
		break;
	case DOWN:
		arrowRect = { centerX - 2, centerY, 4, cusorLength };
		break;
	case LEFT:
		arrowRect = { centerX - cusorLength, centerY - 2, cusorLength, 4 };
		break;
	}
	SDL_RenderFillRect(renderer, &arrowRect);

	// Draw projectiles
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	for (int p = 0; p < projectiles.size(); p++) {
		int projX = projectiles[p].getProjX() * gridSize + gridSize / 2; // Center X pixel
		int projY = projectiles[p].getProjY() * gridSize + gridSize / 2; // Center Y pixel
		int radius = 4;

		// Loop through tile and draw pixel within radius
		for (int yOffset = -radius; yOffset <= radius; yOffset++) {
			for (int xOffset = -radius; xOffset <= radius; xOffset++) {
				// If within radius 
				if (xOffset * xOffset + yOffset * yOffset <= radius * radius) {
					SDL_RenderDrawPoint(renderer, projX + xOffset, projY + yOffset);
				}
			}
		}
	}

	// Upgrade Menu
	if (openUpgradeMenu) {
		int menyX = cursorX * gridSize;
		int menyY = cursorY * gridSize;

		// Draw upgrade menu background
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200); 
		SDL_Rect upgradeMenuRect = { menyX, menyY, 160, 110 };
		SDL_RenderFillRect(renderer, &upgradeMenuRect);
		
		// Draw upgrade options 
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect upgrade1Rect = { menyX + 10, menyY + 10, 140, 40 };
		SDL_Rect upgrade2Rect = { menyX + 10, menyY + 60, 140, 40 };
		SDL_RenderFillRect(renderer, &upgrade1Rect);
		SDL_RenderFillRect(renderer, &upgrade2Rect);

		// Upgrade Text
		string upgradeDamageText = "1 - Damage " + to_string(towers[selectedTower]->getUpgrade1Level()) + "/" + to_string(towers[selectedTower]->getMaxUpgrade1Level());
		string upgradeRangeText = "2 - Range " + to_string(towers[selectedTower]->getUpgrade2Level()) + " / " + to_string(towers[selectedTower]->getMaxUpgrade2Level());
		SDL_Color textColor = {255, 0, 0, 255};
		SDL_Surface* upgradeDamageSurface = TTF_RenderText_Blended(font, upgradeDamageText.c_str(), textColor);
		SDL_Surface* upgradeRangeSurface = TTF_RenderText_Blended(font, upgradeRangeText.c_str(), textColor);

		SDL_Texture* upgradeDamageTexture = SDL_CreateTextureFromSurface(renderer, upgradeDamageSurface);
		SDL_Texture* upgradeRangeTexture = SDL_CreateTextureFromSurface(renderer, upgradeRangeSurface);

		int upgradeDamageW, upgradeDamageH;
		int upgradeRangeW, upgradeRangeH;
		SDL_QueryTexture(upgradeDamageTexture, NULL, NULL, &upgradeDamageW, &upgradeDamageH);
		SDL_QueryTexture(upgradeRangeTexture, NULL, NULL, &upgradeRangeW, &upgradeRangeH);

		SDL_Rect upgradeDamageTextRect = {menyX + 15, menyY + 20,upgradeDamageW, upgradeDamageH };
		SDL_Rect upgradeRangeTextRect = {menyX + 15, menyY + 70, upgradeRangeW, upgradeRangeH};

		SDL_RenderCopy(renderer, upgradeDamageTexture, NULL, &upgradeDamageTextRect);
		SDL_RenderCopy(renderer, upgradeRangeTexture, NULL, &upgradeRangeTextRect);

		SDL_FreeSurface(upgradeDamageSurface);
		SDL_FreeSurface(upgradeRangeSurface);
		SDL_DestroyTexture(upgradeDamageTexture);
		SDL_DestroyTexture(upgradeRangeTexture);
	}

	// Print HUD (CONVERT TO SDL)
	//// Controls 
	//cout << "1 - Tower 1 [Price - 50]" << endl; // Shoots in straight line 
	//cout << "2 - Tower 2 [Price - 200]" << endl; // Shoots in 4 directions
	//cout << "3 - Tower 3 [Price - 500]" << endl; // Shoorts in radius
	//// Upgrade ideas - increase damage, range, fire rate, multi shot, pierce, slow
	//// Print Stats
	//cout << endl << "Base Health: " << baseHealth << endl;
	//cout << "Money: " << money;
	//// Print Wave Number


	SDL_RenderPresent(renderer);
	SDL_Delay(50);
};

bool Game::isTileFree (int x, int y) {
	// Check if tile has tower 
	for (int t = 0; t < towers.size(); t++) {
		if (towers[t]->getTowerX() == x && towers[t]->getTowerY() == y) {
			return false; // Tower in tile
		}
	}
	return true; // Tile is free
}

void Game::Input() {
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (state[SDL_SCANCODE_L]) {
			gameOver = true;
		}

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_E: // Rotate right
				cursorDir = static_cast<Direction>((cursorDir + 1) % 4);
				break;
			case SDL_SCANCODE_Q: // Rotate left
				cursorDir = static_cast<Direction>((cursorDir + 3) % 4);
				break;
			case SDL_SCANCODE_W:
				cursorY--;
				break;
			case SDL_SCANCODE_S:
				cursorY++;
				break;
			case SDL_SCANCODE_A:
				cursorX--;
				break;
			case SDL_SCANCODE_D:
				cursorX++;
				break;
			case SDL_SCANCODE_Y:
				waveStart = true;
				break;

			// Buy Towers
			case SDL_SCANCODE_1:
				if (money >= 50 && isTileFree(cursorX, cursorY)) {
					towers.push_back(std::make_unique<basicTower>(cursorX, cursorY, cursorDir));
					money -= 50;
				}
				break;

			case SDL_SCANCODE_2:
				if (money >= 100 && isTileFree(cursorX, cursorY)) {
					towers.push_back(std::make_unique<longRangeTower>(cursorX, cursorY, cursorDir));
					money -= 100;
				}
				break;
			case SDL_SCANCODE_3:
				if (money >= 200 && isTileFree(cursorX, cursorY)) {
					towers.push_back(std::make_unique<heavyDamageTower>(cursorX, cursorY, cursorDir));
					money -= 200;
				}
				break;
			case SDL_SCANCODE_4:
				if (money >= 300 && isTileFree(cursorX, cursorY)) {
					towers.push_back(std::make_unique<fourWayTower>(cursorX, cursorY, cursorDir));
					money -= 300;
				}
				break;
			// Upgrade Menu
			case SDL_SCANCODE_F:
				// Upgrade tower at cursor position
				for (int t = 0; t < towers.size(); t++) {
					if (towers[t]->getTowerX() == cursorX && towers[t]->getTowerY() == cursorY) {
						// Open upgrade menu
						if (openUpgradeMenu) {
							openUpgradeMenu = false; // Close if already open
							break;
						}
						else {
							openUpgradeMenu = true;
							selectedTower = t;
							break;
						}
					}
				}
				break;


			}

			// buy upgrades
			if (openUpgradeMenu) {
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_1: // Upgrade 1 selected
					if (selectedTower >= 0 && selectedTower < towers.size()) {
						towers[selectedTower]->upgradeDamage();
						openUpgradeMenu = false; // Close menu
					}
					break;
				case SDL_SCANCODE_2: // Upgrade 2 selected
					if (selectedTower >= 0 && selectedTower < towers.size()) {
						towers[selectedTower]->upgradeMultiShot();
						openUpgradeMenu = false;
					}
					break;
				}
			}
	
		

		}
	}


	

	// Wave Start
	
	/*if (!waveStart) {
		cout << endl << "Press Y to start wave";
	}*/


}

void Game::Logic() {

	// Enemy waves
	if (waveStart) {
		if (!waves[currentWave]->waveComplete()) {
			auto waveEnemies = waves[currentWave]->spawnEnemies();
			for (auto& enemy : waveEnemies) {
				enemies.push_back(std::move(enemy));
			}
			waveEnemies.clear();
		}
	
	// If wave complete
		if (waves[currentWave]->waveComplete() && enemies.empty()) {

		

			waveStart = false; // End wave
			currentWave++; // Next wave


			// If all waves complete
			if (currentWave >= waves.size()) {
				// print SDL endscreen
				gameOver = true;
			}
		}
	}

	// Special Waves
	for (floodArea& flood : floodAreas) {
		// Activate flood area
		if ((currentWave + 1) % flood.specialRound == 0) {
			flood.effectActive = true;
		}

		//Deactivate after round ends
		else {
			flood.effectActive = false;
		}
	}




	// Move enemies
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i]->move(pathX, pathY, pathLength); // Loop through vector and move each

		if (enemies[i]->getPathPosition() >= pathLength) {
			// Decrease player health
			baseHealth--;

			// Delete enemy
			enemies.erase(enemies.begin() + i); // Delete from vector
			continue;
			
		}

		// If enemy dead
		if (enemies[i]->getHealth() <= 0) {
			money += 10; // Give money for kill
			// Delete enemy
			enemies.erase(enemies.begin() + i); // Delete from vector
			
			continue;
		}
	}

	// Game Over
	if (baseHealth <= 0) {
		gameOver = true;
		cout << endl <<"GAME OVER";
	}

	



	// Tower attacks
	for (int t = 0; t < towers.size(); t++) { // Loop through towers
		towers[t]->incrementFireTick(); // Increment fire tick

		int towerX = towers[t]->getTowerX();
		int towerY = towers[t]->getTowerY();
		Direction dir = towers[t]->getRotation();
		int range = towers[t]->getRange();
		int damage = towers[t]->getDamage();
		towerType type = towers[t]->getTowerType();


		bool towerDisabled = false;

		// Diable tower if in flood area
		for (floodArea& flood : floodAreas) {
			if (flood.effectActive && towerX >= flood.x && towerX < flood.x + flood.w && towerY >= flood.y && towerY < flood.y + flood.h) {
				towerDisabled = true;
				break;
			}
		}
		
		if (towerDisabled) {
			continue; // Skip fire
		}

		if (towers[t]->getFireTick() < towers[t]->getFireRate())
			continue; // Skip fire 

		if (type == FOUR_WAY) {
			// Able to attack in all 4 direction independently
			
		}
		else {
			for (int e = 0; e < enemies.size(); e++) { // Loop throguh enemies
				int enemyX = enemies[e]->getX();
				int enemyY = enemies[e]->getY();

				bool inRange = false;
				switch (dir) {
				case UP:
					if (enemyX == towerX && enemyY < towerY && enemyY >= towerY - range) inRange = true;
					break;
				case RIGHT:
					if (enemyY == towerY && enemyX > towerX && enemyX <= towerX + range) inRange = true;
					break;
				case DOWN:
					if (enemyX == towerX && enemyY > towerY && enemyY <= towerY + range) inRange = true;
					break;
				case LEFT:
					if (enemyY == towerY && enemyX < towerX && enemyX >= towerX - range) inRange = true;
					break;
				}
				// If enemy in range
				if (inRange) {
					int projX = towerX;
					int projY = towerY;

					switch (dir) {
					case UP:    projY--; break;
					case RIGHT: projX++; break;
					case DOWN:  projY++; break;
					case LEFT:  projX--; break;
					}
					projectiles.emplace_back(projX, projY, dir, 1, damage, range, 0);
					towers[t]->resetFireTick(); // Reset fire tick
					break;

				}
			}
		}
	}

	// Move projectiles
	for (int p = 0; p < projectiles.size(); p++) {
		projectiles[p].move();
		// Get projectile stats
		int projX = projectiles[p].getProjX();
		int projY = projectiles[p].getProjY();
		int damage = projectiles[p].getDamage();
		bool enemyHit = false;
		// Check if hit an enemy
		for (int e = 0; e < enemies.size(); e++) {
			if (projX == enemies[e]->getX() && projY == enemies[e]->getY()) {
				// When enemy hit
				enemies[e]->hit(damage); // Apply damage to enemy
				
		
				enemyHit = true; // Remove projectile after loop
					
				break;
			}
		}

		if (enemyHit || projectiles[p].maxRange()) {
			projectiles.erase(projectiles.begin() + p); // Remove projectile
			p--;
		}
	}

	// Delete Tower - Add functions to Tower class
	//for (int t = 0; t < towers.size(); t++) {
	//	if (towers[t]->deleteTower()) {
	//		// Refund money
	//		money += towers[t]->refundTower();
	//		// Remove from vector
	//		towers.erase(towers.begin() + t);
	//		t--;
	//	}
	//}
	
	// Remove from vector
	// Refund cost
}


int main(int argc, char* argv[]) {

	Game game;
	game.Setup();

	while (!game.getGameOver()) {
		game.Input(); // Player Inputs
		game.Logic(); // Game Logic
		game.Render(); // Render map
	}

	return 0;
}