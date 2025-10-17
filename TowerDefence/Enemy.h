#pragma once
class Enemy {
private:
	int health;
	int pathPosition;
	int speed;
	int moveTick;
	int x, y; //Coordinates
public:

	


	// Ememy Move
	Enemy(int h, int s);
	void move(const int pathX[], const int pathY[], int pathLength);

	// Enemy Damaged
	void hit(int damage);
	int getX() const { return x; }
	int getY() const { return y; }
	int getPathPosition() const { return pathPosition; }
	int getHealth() const { return health; }
	

};
