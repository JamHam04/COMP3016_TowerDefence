#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "Game.h"

#include <SDL.h>


using namespace std;

//Enemy smallEnemy(1, 5);

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
}

void Game::Draw() {
	// Draw Map
	system("cls");

	// Draw top border
	for (int i = 0; i < width + 2; i++) { //Print one row along the top width (+2 for corners)
		cout << '#';
	}
	cout << endl;

	// Centre Map
	for (int i = 0; i < height; i++) { // Rows
		for (int j = 0; j < width; j++) { // Columns
			if (j == 0) cout << '#'; // Print left border

			// Draw path
			bool path = false;
			// Loop through map
			for (int k = 0; k < pathLength; k++) {
				if (pathX[k] == j && pathY[k] == i) { // If position is a path
					path = true; // Set position as path
					break;
				}
			}

			// Draw enemies
			bool enemySpawn = false;
			
			for (int enemy = 0; enemy < enemies.size(); enemy++) {
				if (enemies[enemy].getX() == j && enemies[enemy].getY() == i)
				{
					enemySpawn = true;
					break;
				}
			}

			// Draw Tower
			bool towerHere = false;
			for (int t = 0; t < towers.size(); t++) {
				if (towers[t].getTowerX() == j && towers[t].getTowerY() == i) {
					switch (towers[t].getRotation()) {
					case UP:
						cout << 'A';
						break;
					case RIGHT:
						cout << '>';
						break;
					case DOWN:
						cout << 'V';
						break;
					case LEFT:
						cout << '<';
						break;
					}
					towerHere = true;
					break;
				}
			}

			// Draw protectiles
			bool projectileHere = false;
			for (int p = 0; p < projectiles.size(); p++) {
				if (projectiles[p].getProjX() == j && projectiles[p].getProjY() == i) {
					cout << 'B';
					projectileHere = true;
					break;
				}
			}
			
			if (towerHere) continue;
			if (projectileHere) continue;
			else if (i == cursorY && j == cursorX)
				if (path)
					cout << '!';
				else
					switch (cursorDir) {
					case UP:
						cout << '^';
						break;
					case RIGHT:
						cout << '>';
						break;
					case DOWN:
						cout << 'v';
						break;
					case LEFT:
						cout << '<';
						break;
					}


			else if (enemySpawn) cout << '0';
			else if (path) cout << '+'; // print on path position
			// Else empty space
			
			else {
				cout << ' ';
			}

			if (j == width - 1) cout << '#'; // Print right border

		}
		cout << endl; //Move to next row
	}

	// Draw bottom border
	for (int i = 0; i < width + 2; i++) { //Print one along the bottom width (+2 for corners)
		cout << '#';
	}
	cout << endl;


	// Draw Enemies

	// Controls 
	cout << "1 - Tower 1 [Price - 50]" << endl; // Shoots in straight line 
	cout << "2 - Tower 2 [Price - 200]" << endl; // Shoots in 4 directions
	cout << "3 - Tower 3 [Price - 500]" << endl; // Shoorts in radius
	// Upgrade ideas - increase damage, range, fire rate, multi shot, pierce, slow
	// Print Stats
	cout << endl << "Base Health: " << baseHealth << endl;
	cout << "Money: " << money;
	// Print Wave Number
}

void Game::Render() {

	


	// Drawn background
	SDL_SetRenderDrawColor(renderer, 60, 120, 30, 255);
	SDL_RenderClear(renderer);

	// Draw random points?


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
		int circleX = enemies[enemy].getX() * gridSize + 12; // Circle center X pixel (tileX * tileSize + tileSize/2)
		int circleY = enemies[enemy].getY() * gridSize + 12; // Circle center Y pixel (tileX * tileSize + tileSize/2)
		int radius = 10; // Circle size

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
	bool towerHere = false;
	for (int t = 0; t < towers.size(); t++) {
		int edgeOffset = 8;
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_Rect towerRect = { towers[t].getTowerX() * gridSize + edgeOffset /2, towers[t].getTowerY() * gridSize + edgeOffset /2, gridSize - edgeOffset, gridSize - edgeOffset };
		SDL_RenderFillRect(renderer, &towerRect);

		int centerX = towers[t].getTowerX() * gridSize + gridSize / 2;
		int centerY = towers[t].getTowerY() * gridSize + gridSize / 2;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		
		
		SDL_Rect barrelRect;
			switch (towers[t].getRotation()) {
			case UP:
				barrelRect = { centerX - 4, centerY - 12, 8, 12 };
				break;
			case RIGHT:
				barrelRect = { centerX, centerY - 4, 12, 8 };
				break;
			case DOWN:
				barrelRect = { centerX - 4, centerY, 8, 12 };
				break;
			case LEFT:
				barrelRect = { centerX - 12, centerY - 4, 12, 8 };
				break;
			}
			SDL_RenderFillRect(renderer, &barrelRect);
	}

	// Draw cursor box
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect cursorRect = { cursorX * gridSize, cursorY * gridSize, gridSize, gridSize };
	SDL_RenderDrawRect(renderer, &cursorRect);

	// Draw cursor arrow
	int centerX = cursorX * gridSize + gridSize / 2;
	int centerY = cursorY * gridSize + gridSize / 2;
	int cusorLength = 10; // How far the pointer sticks out

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Yellow for visibility
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



	SDL_RenderPresent(renderer);
	SDL_Delay(50);
};

void Game::Input() {
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
		if (state[SDL_SCANCODE_X]) {
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
			case SDL_SCANCODE_1:
				if (money >= 50) {
					towers.emplace_back(cursorX, cursorY, 1, 2, cursorDir);
					money -= 50;
				}
				break;
			}
		}
	}


	// Place Tower 
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			cursorX--;
			break;
		case 'd':
			cursorX++;
			break;
		case 'w':
			cursorY--;
			break;
		case 's':
			cursorY++;
			break;
		case 'y':
			waveStart = true;
			break;
		case 'e':
			// Rotate right
			cursorDir = static_cast<Direction>((cursorDir + 1) % 4);
			break;
		case 'q':
			// Rotate left
			cursorDir = static_cast<Direction>((cursorDir + 3) % 4); 
			break;
		case '1':
			// Place Tower 1
			if (money >= 50) {
				towers.emplace_back(cursorX, cursorY, 1, 2, cursorDir); // Tower damage, range, direction
				money -= 50;
			}
			break;
		case '2':
			waveStart = true;
			break;
		case '3':
			waveStart = true;
			break;
		}
	}

	// Wave Start
	
	if (!waveStart) {
		cout << endl << "Press Y to start wave";
	}
	// Upgrade Tower

}

void Game::Logic() {
	

	// Spawn enemies

	if (waveStart) {
		spawnTick++; // Spawn delay
		if (spawnTick >= 25) {
			enemies.emplace_back(10, 10); // Create new Enemy in vector (health, speed)
			spawnTick = 0;
		}
	}

	// Move enemies
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i].move(pathX, pathY, pathLength); // Loop through vector and move each

		if (enemies[i].getPathPosition() >= pathLength) {
			// Decrease player health
			baseHealth--;

			// Delete enemy
			enemies.erase(enemies.begin() + i); // Delete from vector
			continue;
			
		}

		// If enemy dead
		if (enemies[i].getHealth() <= 0) {
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

	// Enemy waves



	// Tower attacks
	for (int t = 0; t < towers.size(); t++) { // Loop through towers
		// Get tower stats
		int towerX = towers[t].getTowerX();
		int towerY = towers[t].getTowerY();
		Direction dir = towers[t].getRotation();
		int range = towers[t].getRange();
		int damage = towers[t].getDamage();
		// Check for enemies in range
		for (int e = 0; e < enemies.size(); e++) { // Loop throguh enemies
			// Get enemy position
			int enemyX = enemies[e].getX();
			int enemyY = enemies[e].getY();
			bool inRange = false;
			switch (dir) {
			// Check direction and range
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

				projectiles.emplace_back(projX, projY, dir, 1, damage);

				break; 
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
		// Check if hit an enemy
		for (int e = 0; e < enemies.size(); e++) {
			if (projX == enemies[e].getX() && projY == enemies[e].getY()) {
				// When enemy hit
				enemies[e].hit(damage); // Apply damage to enemy
				projectiles.erase(projectiles.begin() + p); // Remove projectile
				// BUG - Projectiles not being removed (projeciles timing step over enemies)
				p--;
					
				break;
			}
		}
	}

	// Delete Tower
	// Remove from vector
	// Refund cost
}

Game::Game() {
	SDL_Init(SDL_INIT_VIDEO);


	window = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * gridSize, height * gridSize, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

int main(int argc, char* argv[]) {

	Game game;
	game.Setup();

	while (!game.getGameOver()) {
		//game.Draw(); //Draw map
		game.Input(); // Player Inputs
		game.Logic(); // Game Logic
		game.Render(); // Render map
		//SDL_Delay(100); //Pause loop 
	}

	return 0;
}