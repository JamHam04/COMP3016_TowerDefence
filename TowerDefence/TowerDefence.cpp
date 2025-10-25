#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Game.h"

#include <SDL.h>


using namespace std;

void Game::createPath() {
	int currentCol = 15; // Where path will start 
	int currentPath = 0;

	int previousCol = currentCol;

	// Loop throuugh rows
	for (int currentRow = 0; currentRow < height; currentRow++) {
		pathX[currentPath] = currentCol; // Set X to current col position
		pathY[currentPath] = currentRow; // Set Y to current row
		currentPath++; // Increment array index

		// Move left or right
		if (currentRow == 5) {
			currentCol -= 3; // Move 3 left
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

	// Setup waves (Change to file load?)
	waves.push_back(std::make_unique<Wave>(25, 5, 0)); // 10 smallEnemy, spawn every 25 ticks
	waves.push_back(std::make_unique<Wave>(20, 2, 1));  // 5 mediumEnemy, spawn every 20 ticks
	waves.push_back(std::make_unique<Wave>(50, 3, 2)); // 15 smallEnemy, spawn every 15 ticks
	waves.push_back(std::make_unique<Wave>(20, 5, 0));
	waves.push_back(std::make_unique<Wave>(15, 5, 0));

	// Setup special waves
	floodAreas.push_back({ 13, 6, 3, 5, 2, false });
	floodAreas.push_back({ 12, 15, 6, 4, 2, false });
	floodAreas.push_back({ 3, 12, 2, 2, 2, false });

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

void drawEnemy(SDL_Renderer* renderer, int x, int y, int gridSize, Enemy* enemy, enemyType type) {
	
	int circleX = x * gridSize + 12; // Circle center X pixel (tileX * tileSize + tileSize/2)
	int circleY = y * gridSize + 12; // Circle center Y pixel (tileX * tileSize + tileSize/2)
	int radius = 0; // Circle size
	// Switch color based on enemy type
	switch (type) {
	case SMALL:
		SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
		radius = 6;
		break;
	case MEDIUM:
		SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255);
		
		radius = 8;
		break;
	case LARGE:
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		radius = 10;
	}

	// Enemy damaged effect
	if (enemy->enemyHitEffect()) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Flash white
	}
	if (enemy->enemyBurnHitEffect()) {
		SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255); // Flash orange
	}

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

void Game::drawTowerControls() {

	int controlX = 5;
	int controlY = 21 * gridSize; // 4 tower types
	int controlWidth = gridSize * 4;
	int controlHeight = gridSize * 4;

	SDL_Color textColor = { 255, 255, 255, 255 };

	// Draw control background
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
	SDL_Rect controlRect = { controlX - 5 , controlY , controlWidth, controlHeight };
	SDL_RenderFillRect(renderer, &controlRect);
	


	// Tower prices
	const int towerPrices[4] = { 50, 100, 200, 300 }; // Change to class gets?

	// For each tower type
	for (int i = 0; i < 4; ++i) {
		std::unique_ptr<Tower> tower;
		switch (i) {
			case 0:
				tower = std::make_unique<basicTower>(cursorX, cursorY, cursorDir);
				break;
			case 1:
				tower = std::make_unique<longRangeTower>(cursorX, cursorY, cursorDir);
				break;
			case 2:
				tower = std::make_unique<heavyDamageTower>(cursorX, cursorY, cursorDir);
				break;
			case 3:
				tower = std::make_unique<fourWayTower>(cursorX, cursorY, cursorDir);
				break;
		}
		int cost = tower->getTowerCost();


		std::string controlText = std::to_string(i + 1);
		std::string priceText = " $" + std::to_string(cost);
		SDL_Surface* controlSurface = TTF_RenderText_Blended(font, controlText.c_str(), textColor);
		SDL_Texture* controlTexture = SDL_CreateTextureFromSurface(renderer, controlSurface);
		SDL_Surface* priceSurface = TTF_RenderText_Blended(fontSmall, priceText.c_str(), textColor);
		SDL_Texture* priceTexture = SDL_CreateTextureFromSurface(renderer, priceSurface);
		int w, h;
		int priceW, priceH;
		SDL_QueryTexture(controlTexture, NULL, NULL, &w, &h);
		SDL_QueryTexture(priceTexture, NULL, NULL, &priceW, &priceH);

		SDL_Rect controlRect = { controlX, controlY + i * gridSize, w, h };
		SDL_RenderCopy(renderer, controlTexture, NULL, &controlRect);

		SDL_Rect priceRect = { controlX + 45, controlY + i * gridSize + 5, priceW, priceH };
		SDL_RenderCopy(renderer, priceTexture, NULL, &priceRect);

		SDL_FreeSurface(controlSurface);
		SDL_DestroyTexture(controlTexture);
		
		SDL_FreeSurface(priceSurface);
		SDL_DestroyTexture(priceTexture);

		towerType type = static_cast<towerType>(i);  

		// Draw towers
		drawTower(renderer, 1, (controlY / gridSize) + i, gridSize, UP, type);


	}
}

void Game::drawHUD() {
	// Example positions
	int hudX = 5;
	int hudY = 5;
	int hudWidth = gridSize * 8;
	int hudHeight = gridSize * 5;

	SDL_Color textColor = { 255, 255, 255, 255 };

	// Draw HUD background
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
	SDL_Rect hudRect = { hudX - 5, hudY - 5, hudWidth, hudHeight};
	SDL_RenderFillRect(renderer, &hudRect);

	// Health
	if (isbaseDamged()) {
		textColor = { 255, 0, 0, 255 }; 
	}
	std::string healthText = "Base Health: " + std::to_string(baseHealth);
	SDL_Surface* healthSurface = TTF_RenderText_Blended(font, healthText.c_str(), textColor);
	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);
	int w, h;
	SDL_QueryTexture(healthTexture, NULL, NULL, &w, &h);
	SDL_Rect healthRect = { hudX, hudY, w, h };
	SDL_RenderCopy(renderer, healthTexture, NULL, &healthRect);
	SDL_FreeSurface(healthSurface);
	SDL_DestroyTexture(healthTexture);

	textColor = { 255, 255, 255, 255 };

	// Money
	std::string moneyText = "Money: " + std::to_string(money);
	SDL_Surface* moneySurface = TTF_RenderText_Blended(font, moneyText.c_str(), textColor);
	SDL_Texture* moneyTexture = SDL_CreateTextureFromSurface(renderer, moneySurface);
	SDL_QueryTexture(moneyTexture, NULL, NULL, &w, &h);
	SDL_Rect moneyRect = { hudX, hudY + 20, w, h };
	SDL_RenderCopy(renderer, moneyTexture, NULL, &moneyRect);
	SDL_FreeSurface(moneySurface);
	SDL_DestroyTexture(moneyTexture);

	// Wave number
	std::string waveText = "Wave: " + std::to_string(currentWave + 1) + " / " + std::to_string(waves.size());
	SDL_Surface* waveSurface = TTF_RenderText_Blended(font, waveText.c_str(), textColor);
	SDL_Texture* waveTexture = SDL_CreateTextureFromSurface(renderer, waveSurface);
	SDL_QueryTexture(waveTexture, NULL, NULL, &w, &h);
	SDL_Rect waveRect = { hudX, hudY + 40, w, h };
	SDL_RenderCopy(renderer, waveTexture, NULL, &waveRect);
	SDL_FreeSurface(waveSurface);
	SDL_DestroyTexture(waveTexture);

	// Enemies left
	std::string enemiesLeftText = "Enemies Left: " + std::to_string(enemies.size());
	SDL_Surface* enemiesSurface = TTF_RenderText_Blended(font, enemiesLeftText.c_str(), textColor);
	SDL_Texture* enemiesTexture = SDL_CreateTextureFromSurface(renderer, enemiesSurface);
	SDL_QueryTexture(enemiesTexture, NULL, NULL, &w, &h);
	SDL_Rect enemiesRect = { hudX, hudY + 60, w, h };
	SDL_RenderCopy(renderer, enemiesTexture, NULL, &enemiesRect);
	SDL_FreeSurface(enemiesSurface);
	SDL_DestroyTexture(enemiesTexture);

	// Wave start prompt
	if (!waveStart) {
		std::string startText = "Press Y to start wave";
		SDL_Color textColor = { 255, 160, 0, 255 };
		SDL_Surface* startSurface = TTF_RenderText_Blended(font, startText.c_str(), textColor);
		SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
		int w, h;
		SDL_QueryTexture(startTexture, NULL, NULL, &w, &h);
		SDL_Rect startRect = { 5, 4 * gridSize, w, h };
		SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
		SDL_FreeSurface(startSurface);
		SDL_DestroyTexture(startTexture);
	}

}

void Game::drawUpgradeMenu() {
	int menyX = cursorX * gridSize;
	int menyY = cursorY * gridSize;

	// Draw upgrade menu background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_Rect upgradeMenuRect = { menyX, menyY, 180, 110 };
	SDL_RenderFillRect(renderer, &upgradeMenuRect);

	// Draw upgrade options 
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect upgrade1Rect = { menyX + 10, menyY + 10, 160, 40 };
	SDL_Rect upgrade2Rect = { menyX + 10, menyY + 60, 160, 40 };
	SDL_RenderFillRect(renderer, &upgrade1Rect);
	SDL_RenderFillRect(renderer, &upgrade2Rect);

	// Upgrade Text
	string upgradeDamageText = "1 - " + towers[selectedTower]->getUpgrade1Name() + " " + to_string(towers[selectedTower]->getUpgrade1Level()) + "/" + to_string(towers[selectedTower]->getMaxUpgrade1Level());
	string upgradeRangeText = "2 - " + towers[selectedTower]->getUpgrade2Name() + " " + to_string(towers[selectedTower]->getUpgrade2Level()) + " / " + to_string(towers[selectedTower]->getMaxUpgrade2Level());
	SDL_Color textColor = { 255, 0, 0, 255 };
	SDL_Surface* upgradeDamageSurface = TTF_RenderText_Blended(font, upgradeDamageText.c_str(), textColor);
	SDL_Surface* upgradeRangeSurface = TTF_RenderText_Blended(font, upgradeRangeText.c_str(), textColor);

	SDL_Texture* upgradeDamageTexture = SDL_CreateTextureFromSurface(renderer, upgradeDamageSurface);
	SDL_Texture* upgradeRangeTexture = SDL_CreateTextureFromSurface(renderer, upgradeRangeSurface);

	int upgradeDamageW, upgradeDamageH;
	int upgradeRangeW, upgradeRangeH;
	SDL_QueryTexture(upgradeDamageTexture, NULL, NULL, &upgradeDamageW, &upgradeDamageH);
	SDL_QueryTexture(upgradeRangeTexture, NULL, NULL, &upgradeRangeW, &upgradeRangeH);

	SDL_Rect upgradeDamageTextRect = { menyX + 15, menyY + 20,upgradeDamageW, upgradeDamageH };
	SDL_Rect upgradeRangeTextRect = { menyX + 15, menyY + 70, upgradeRangeW, upgradeRangeH };

	SDL_RenderCopy(renderer, upgradeDamageTexture, NULL, &upgradeDamageTextRect);
	SDL_RenderCopy(renderer, upgradeRangeTexture, NULL, &upgradeRangeTextRect);

	SDL_FreeSurface(upgradeDamageSurface);
	SDL_FreeSurface(upgradeRangeSurface);
	SDL_DestroyTexture(upgradeDamageTexture);
	SDL_DestroyTexture(upgradeRangeTexture);

	// Upgrade Costs
	int upgrade1Cost = towers[selectedTower]->getUpgrade1Cost();
	int upgrade2Cost = towers[selectedTower]->getUpgrade2Cost();
	string upgradeCostText1 = "Cost: $" + to_string(upgrade1Cost);
	string upgradeCostText2 = "Cost: $" + to_string(upgrade2Cost);

	SDL_Color upgrade1CostColor = { 0, 150, 0, 255 };
	SDL_Color upgrade2CostColor = { 0, 150, 0, 255 };
	if (money < upgrade1Cost) {
		upgrade1CostColor = { 255, 0, 0, 255 }; // Not enough money
	}
	if (money < upgrade2Cost) {
		upgrade2CostColor = { 255, 0, 0, 255 }; // Not enough money
	}

	
	SDL_Surface* upgradeCostSurface1 = TTF_RenderText_Blended(fontSmall, upgradeCostText1.c_str(), upgrade1CostColor);
	SDL_Surface* upgradeCostSurface2 = TTF_RenderText_Blended(fontSmall, upgradeCostText2.c_str(), upgrade2CostColor);
	SDL_Texture* upgradeCostTexture1 = SDL_CreateTextureFromSurface(renderer, upgradeCostSurface1);
	SDL_Texture* upgradeCostTexture2 = SDL_CreateTextureFromSurface(renderer, upgradeCostSurface2);

	int upgradeCostW1, upgradeCostH1, upgradeCostW2, upgradeCostH2;
	SDL_QueryTexture(upgradeCostTexture1, NULL, NULL, &upgradeCostW1, &upgradeCostH1);
	SDL_QueryTexture(upgradeCostTexture2, NULL, NULL, &upgradeCostW2, &upgradeCostH2);

	SDL_Rect upgradeCostRect1 = { menyX + 90, menyY + 35, upgradeCostW1, upgradeCostH1 };
	SDL_Rect upgradeCostRect2 = { menyX + 90, menyY + 85, upgradeCostW2, upgradeCostH2 };

	// Only draw cost if not maxed
	if (towers[selectedTower]->getUpgrade1Level() != towers[selectedTower]->getMaxUpgrade1Level()) {
		SDL_RenderCopy(renderer, upgradeCostTexture1, NULL, &upgradeCostRect1);
	}
	if (towers[selectedTower]->getUpgrade2Level() != towers[selectedTower]->getMaxUpgrade2Level()) {
		SDL_RenderCopy(renderer, upgradeCostTexture2, NULL, &upgradeCostRect2);
	}
	SDL_FreeSurface(upgradeCostSurface1);
	SDL_FreeSurface(upgradeCostSurface2);
	SDL_DestroyTexture(upgradeCostTexture1);
	SDL_DestroyTexture(upgradeCostTexture2);
}

void Game::Render() {

	// Drawn background
	SDL_SetRenderDrawColor(renderer, 40, 140, 40, 255);
	SDL_RenderClear(renderer);

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
	for (int enemy = 0; enemy < enemies.size(); enemy++) {
		drawEnemy(renderer, enemies[enemy]->getX(), enemies[enemy]->getY(), gridSize, enemies[enemy].get(), enemies[enemy]->getEnemyType());
		enemies[enemy]->resetHitEffect();
		enemies[enemy]->resetBurnHitEffect();
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
		drawUpgradeMenu();
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

		// Wave Start

	drawHUD();
	resetDamageEffect();
	drawTowerControls();
	SDL_RenderPresent(renderer);
	SDL_Delay(50);
};




bool Game::isTileFree(int x, int y) {
	// Check if tile has tower 
	for (int t = 0; t < towers.size(); t++) {
		if (towers[t]->getTowerX() == x && towers[t]->getTowerY() == y) {
			return false; // Tower in tile
		}
	}
	for (int k = 0; k < pathLength; k++) {
		if (pathX[k] == x && pathY[k] == y) { // If position is a path
			return false;
		}

		
	}
	return true; // Tile is free
}

bool Game::isTileHUD (int x, int y) {
	// HUD area
	int hudX = 5;
	int hudY = 5;
	int hudWidth = gridSize * 8;
	int hudHeight = gridSize * 5;
	// Check if tile is inside HUD area
	if (x * gridSize >= hudX - 5 && x * gridSize < hudX - 5 + hudWidth &&
		y * gridSize >= hudY - 5 && y * gridSize < hudY - 5 + hudHeight) {
		return true; // HUD tile
	}

	// Tower controls area
	int controlX = 0;
	int controlY = 21 * gridSize; // 4 tower types
	int controlWidth = gridSize * 4;
	int controlHeight = gridSize * 4;
	if (x * gridSize >= controlX && x * gridSize < controlX + controlWidth &&
		y * gridSize >= controlY && y * gridSize < controlY + 4 * controlHeight) {
		return true; // Tower controls tile
	}
	return false; // Free tile
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
				if (openUpgradeMenu) {
					openUpgradeMenu = false;
					break;
				}
				if (cursorY > 0 && !isTileHUD(cursorX, cursorY - 1))
					cursorY--;
				break;
			case SDL_SCANCODE_S:
				if (openUpgradeMenu) {
					openUpgradeMenu = false;
					break;
				}
				if (cursorY < height - 1 && !isTileHUD(cursorX, cursorY + 1))
					cursorY++;
				break;
			case SDL_SCANCODE_A:
				if (openUpgradeMenu) {
					openUpgradeMenu = false;
					break;
				}
				if (cursorX > 0 && !isTileHUD(cursorX - 1, cursorY))
					cursorX--;
				break;
			case SDL_SCANCODE_D:
				if (openUpgradeMenu) {
					openUpgradeMenu = false;
					break;
				}
				if (cursorX < width - 1 && !isTileHUD(cursorX + 1, cursorY))
					cursorX++;
				break;
			case SDL_SCANCODE_Y:
				waveStart = true;
				break;

				// Buy Towers
			case SDL_SCANCODE_1: {
				std::unique_ptr<basicTower> tower = std::make_unique<basicTower>(cursorX, cursorY, cursorDir);
				int cost = tower->getTowerCost();
				if (money >= cost && isTileFree(cursorX, cursorY)) {
					money -= cost;
					towers.push_back(std::move(tower));
				}
				break;
			}
			case SDL_SCANCODE_2: {
				std::unique_ptr<longRangeTower> tower = std::make_unique<longRangeTower>(cursorX, cursorY, cursorDir);
				int cost = tower->getTowerCost();
				if (money >= cost && isTileFree(cursorX, cursorY)) {
					towers.push_back(std::move(tower));
					money -= cost;
				}
				break;
			}
			case SDL_SCANCODE_3: {
				std::unique_ptr<heavyDamageTower> tower = std::make_unique<heavyDamageTower>(cursorX, cursorY, cursorDir);
				int cost = tower->getTowerCost();
				if (money >= cost && isTileFree(cursorX, cursorY)) {
					towers.push_back(std::move(tower));
					money -= cost;
				}
				break;
			}
			case SDL_SCANCODE_4: {
				std::unique_ptr<fourWayTower> tower = std::make_unique<fourWayTower>(cursorX, cursorY, cursorDir);
				int cost = tower->getTowerCost();
				if (money >= cost && isTileFree(cursorX, cursorY)) {
					towers.push_back(std::move(tower));
					money -= cost;
				}
				break;
			}
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

			case SDL_SCANCODE_0: // Close upgrade menu
				for (int t = 0; t < towers.size(); t++) {
					if (towers[t]->getTowerX() == cursorX && towers[t]->getTowerY() == cursorY) {
						towers[t]->setTowerDelete();
						break;
					}
					
				}
			}

			// buy upgrades
			if (openUpgradeMenu) {

				if (selectedTower >= 0 && selectedTower < towers.size()) {
					Tower* t = towers[selectedTower].get();
					int upgrade1Cost = t->getUpgrade1Cost();
					int upgrade2Cost = t->getUpgrade2Cost();
					switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_1: // Upgrade 1 selected
						if (money >= upgrade1Cost && t->getUpgrade1Level() < t->getMaxUpgrade1Level()) {
							money -= upgrade1Cost;
							t->upgrade1();
							openUpgradeMenu = false; // Close menu
						}
		
						break;
					case SDL_SCANCODE_2: // Upgrade 1 selected
						if (money >= upgrade2Cost && t->getUpgrade2Level() < t->getMaxUpgrade2Level()) {
							money -= upgrade2Cost;
							t->upgrade2();
							openUpgradeMenu = false; // Close menu
						}
						
						break;

					}
				}
			}
		}
	}
				


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
			baseDamaged = true;
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
			// Able to attack in all 4 direction independently:
			fourWayTower* fwTower = static_cast<fourWayTower*>(towers[t].get()); // Get pointer to fourWayTower
			fwTower->incrementFireTicks();

			for (int e = 0; e < enemies.size(); e++) { // Loop throguh enemies
				int enemyX = enemies[e]->getX();
				int enemyY = enemies[e]->getY();

				for (int d = 0; d < 4; d++) {
					Direction attackDir = static_cast<Direction>(d); // Get each direction individually 
					bool inRange = false;
					switch (attackDir) {
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
					if (inRange && fwTower->canFire(attackDir)) {
						int projX = towerX;
						int projY = towerY;
						switch (attackDir) {
						case UP:    projY--; break;
						case RIGHT: projX++; break;
						case DOWN:  projY++; break;
						case LEFT:  projX--; break;
						}
						projectiles.emplace_back(projX, projY, attackDir, 1, damage, range, 0);
						fwTower->resetFireTick(attackDir); // Reset fire    tick for specific direction
					}
				}
			}
		
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
					Projectile p(projX, projY, dir, 1, damage, range, 0);
					if (type == BASIC) {
						basicTower* bTower = static_cast<basicTower*>(towers[t].get());
						if (bTower->burn) {
							p.setBurn(true); // Set burn
						}
						projectiles.push_back(p);
						towers[t]->resetFireTick(); // Reset fire tick

					}
					if (type == LONG_RANGE) {
						longRangeTower* lrTower = static_cast<longRangeTower*>(towers[t].get());
						
						if (lrTower->pierce) {

							p.setPenetrate(true); 
						}
							//projectiles().setPenetrate(); // Set pirece
			
							projectiles.push_back(p); 
							towers[t]->resetFireTick();
							break;
						

					}
					if (type == HEAVY_DAMAGE) {
						heavyDamageTower* hdTower = static_cast<heavyDamageTower*>(towers[t].get());
						if (hdTower->slow) {
							p.setSlow(true);
						}

						projectiles.push_back(p);
						towers[t]->resetFireTick();
						break;
					}
					else {
						projectiles.emplace_back(projX, projY, dir, 1, damage, range, 0);
						towers[t]->resetFireTick(); // Reset fire tick
					}
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
				
				// Slow
				if (projectiles[p].canSlow()) {
					std::cout << "Slow";
					enemies[e]->enemySlow(4);
				}
				//burn
				if (projectiles[p].canBurn()) {
					std::cout << "Burn";
					enemies[e]->enemyBurn(3, 2); // 3 damage, 2 times
				}
				// Pierce
				if (!projectiles[p].canPenetrate()) {
					enemyHit = true; // Remove projectile after loop
					break;
				}
				
	
			}
		}

		if (enemyHit || projectiles[p].maxRange()) {
			projectiles.erase(projectiles.begin() + p); // Remove projectile
			p--;
		}
	}

	 //Delete Tower 
	for (int t = 0; t < towers.size(); t++) {
		if (towers[t]->deleteTower()) {
			// Refund money
			money += towers[t]->refundTower();

			openUpgradeMenu = false; // Close upgrade menu if open


			// Remove from vector
			towers.erase(towers.begin() + t);
			t--;
		}
	}
	
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