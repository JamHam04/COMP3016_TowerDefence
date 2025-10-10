#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

bool gameOver = false;
bool waveStart = false; // Wait for input to start wave (waveStart = true during waves)
const int width = 25;
const int height = 25;
int baseHealth = 10;
int money;

// Path coordinates
int pathX[100], pathY[100];
int pathLength = 0;
bool pathMove;

// Input
enum Direction { UP, RIGHT, DOWN, LEFT };
Direction cursorDir;
int cursorX, cursorY;

// Classes
class Enemy {
private:
	int health;
	int pathPosition;
	int speed;
	int moveTick;

public:
	int getPathPosition() const {return pathPosition;}
	// Enemy Stats
	int x, y; //Coordinates


	Enemy(int h, int s) {
		health = h;
		pathPosition = 0;
		x = pathX[0];
		y = pathY[0];
		speed = s;
		moveTick = 0;
	}

	// Ememy Move

	void move() {
		
		// If at end
		// Decrease player health, remove enemy?
		if (moveTick != speed) {
			moveTick++;
		}
		else {
			x = pathX[pathPosition];
			y = pathY[pathPosition];
			pathPosition++; // Move 1
			moveTick = 0;
		}
	}

	// Enemy Damaged
	void hit(int damage) {
		// Take damage
		health -= damage;

		if (health <= 0) {
			// Enemy die (erase from vector somehow here?) 
			
			
		}
	}
	
};

Enemy smallEnemy(10, 5);

vector<Enemy> enemies; // Store Enemy instances
int spawnTick = 0;

class Tower {
private:
	int towerPositionX, towerPositionY;
	int towerRotation;
	int towerDamage;
	int projectileSpeed;

public:
	Tower(int d, int s) {
		towerDamage = d;
		projectileSpeed = s;
	}
};

void createPath() {
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

void Setup() {
	// Set Variables
	createPath();
}

void Draw() {
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
				if (enemies[enemy].x == j && enemies[enemy].y == i)
				{
					enemySpawn = true;
					break;
				}
			}
			if (i == cursorY && j == cursorX)
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

	// Draw Towers


	// Draw Enemies

	// Controls 
	cout << "1 - Tower 1 [Price - 50]" << endl;
	cout << "2 - Tower 2 [Price - 200]" << endl;
	cout << "3 - Tower 3 [Price - 500]" << endl;
	// Print Stats
	cout << endl << "Base Health: " << baseHealth << endl;
	cout << "Money: " << money;
	// Print Wave Number
}


void Input() {
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
		}
	}

	// Wave Start
	
	if (!waveStart) {
		cout << endl << "Press Y to start wave";
	}
	// Upgrade Tower

}




void Logic() {
	

	// Spawn enemies

	if (waveStart) {
		spawnTick++; // Spawn delay
		if (spawnTick >= 10) {
			enemies.emplace_back(10, 1); // Create new Enemy in vector
			spawnTick = 0;
		}
	}

	// Move enemies
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i].move(); // Loop through vector and move each

		if (enemies[i].getPathPosition() >= pathLength) {
			// Decrease player health
			baseHealth--;

			// Delete enemy
			enemies.erase(enemies.begin() + i); // Delete from vector

			
		}
	}

	// Game Over
	if (baseHealth <= 0) {
		gameOver = true;
		cout << "GAME OVER";
	}

	// Enemy waves


    // Movement logic


	// Tower attacks


}

int main() {
	Setup();

	while (!gameOver) {
		Draw(); //Draw map
		Input(); // Player Inputs
		Logic(); // Game Logic
		Sleep(100); //Pause loop so that it doesn't run 1000s of times a second
	}
}