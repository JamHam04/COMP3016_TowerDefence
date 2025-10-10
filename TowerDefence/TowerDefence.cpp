#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver = false;
const int width = 25;
const int height = 25;

// Path coordinates
int pathX[100], pathY[100];
int pathLength = 0;
bool pathMove;

// Classes
class Enemy {
private:
	int health;
	int pathPosition;

public:
	// Enemy Stats
	int x, y; //Coordinates

	Enemy(int h) {
		health = h;
		pathPosition = 0;
		x = pathX[0];
		y = pathY[0];
	}
	
	// Enemy Spawn

	// Ememy Move

	void move() {
		x = pathX[pathPosition];
		y = pathY[pathPosition];
		pathPosition++; // Move 1
	}
	// Enemy Attack

	// Enemy Damaged

};

Enemy smallEnemy(10);

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
			bool Path = false;
			// Loop through map
			for (int k = 0; k < pathLength; k++) {
				if (pathX[k] == j && pathY[k] == i) { // If position is a path
					Path = true; // Set position as path
					break;
				}
			}
			if (smallEnemy.x == j && smallEnemy.y == i)
			{
				cout << '0';
			}
			else if (Path) cout << '+'; // print on path position
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
}

void Input() {
	// Place Tower

	// Upgrade Tower

}



void Logic() {
	

	// Spawn enemies
	smallEnemy.move();


	// Enemies move

	// Enemy waves

	// Tower attacks


}

int main() {
	Setup();

	while (!gameOver) {
		Draw(); //Draw map
		Input();
		Logic();
		Sleep(100); //Pause loop so that it doesn't run 1000s of times a second
	}
}