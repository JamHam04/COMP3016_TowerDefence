#pragma once
class Enemy {
private:
	int health;
	int pathPosition;
	int speed;
	int moveTick;

public:

	int x, y; //Coordinates


	// Ememy Move
	Enemy(int h, int s);
	void move(const int pathX[], const int pathY[], int pathLength);

	// Enemy Damaged
	void hit(int damage);
	int getPathPosition() const { return pathPosition; }
	int getHealth() const { return health; }
	

};
