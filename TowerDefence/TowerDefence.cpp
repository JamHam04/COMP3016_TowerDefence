#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver = false;
const int width = 40;
const int height = 20;

void Setup() {
	// Set Variables
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


		    cout << ' ';

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
	// Tower attacks

	// Spawn enemies
	
	// Enemies move

	// Enemy waves


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