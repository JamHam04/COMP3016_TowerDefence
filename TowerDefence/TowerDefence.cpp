#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver = false;

void Setup() {
	// Set Variables
}

void Draw() {
	// Draw Map

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