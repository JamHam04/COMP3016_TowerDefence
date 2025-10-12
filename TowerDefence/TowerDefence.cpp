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
int money = 100;

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
	int getHealth() const { return health; }
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

Enemy smallEnemy(1, 5);

vector<Enemy> enemies; // Store Enemy instances
int spawnTick = 0;

class Tower {
private:
	int towerPositionX, towerPositionY;
	Direction towerRotation;
	int towerDamage;
	int towerRange;

public:



	Tower(int d, int r, Direction dir) {
		towerDamage = d;
		towerPositionX = cursorX;
		towerPositionY = cursorY;
		towerRotation = dir;
		towerRange = r;
	}

	int getTowerX() const { return towerPositionX; }
	int getTowerY() const { return towerPositionY; }
	Direction getRotation() const { return towerRotation; }
	int getRange() const { return towerRange; }
	int getDamage() const { return towerDamage; }
};

vector<Tower> towers; // Store Tower instances

class Projectile {
	private:
	int projX, projY;
	Direction direction;
	int speed;
	int damage;
	int moveTick;

	public:
		Projectile(int x, int y, Direction dir, int s, int d) {
			projX = x;
			projY = y;
			direction = dir;
			speed = s;
			damage = d;
			moveTick = 0;
		}

		void move() {


			
			//if (moveTick != speed) {
			//	moveTick++;
			//}
			//else {
			moveTick = 0;
			switch (direction) {
			case UP:    projY--; break;
			case RIGHT: projX++; break;
			case DOWN:  projY++; break;
			case LEFT:  projX--; break;
			}
			//}
			// Prevent going out map
		}

		int getProjX() const { return projX; }
		int getProjY() const { return projY; }
		int getDamage() const { return damage; }
};

vector<Projectile> projectiles; // Store Projectile instances



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
		case '1':
			// Place Tower 1
			if (money >= 50) {
				towers.emplace_back(1, 2, cursorDir); // Tower damage, range, direction
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




void Logic() {
	

	// Spawn enemies

	if (waveStart) {
		spawnTick++; // Spawn delay
		if (spawnTick >= 10) {
			enemies.emplace_back(5, 1); // Create new Enemy in vector
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
			int enemyX = enemies[e].x;
			int enemyY = enemies[e].y;
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
				projectiles.emplace_back(towerX, towerY, dir, 1, damage);
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
			if (projX == enemies[e].x && projY == enemies[e].y) {
				// When enemy hit
				enemies[e].hit(damage); // Apply damage to enemy
				projectiles.erase(projectiles.begin() + p); // Remove projectile
				break;
			}
		}
	}

	// Delete Tower
	// Remove from vector
	// Refund cost


}

int main() {
	Setup();

	while (!gameOver) {
		Draw(); //Draw map
		Input(); // Player Inputs
		Logic(); // Game Logic
		Sleep(100); //Pause loop 
	}
}