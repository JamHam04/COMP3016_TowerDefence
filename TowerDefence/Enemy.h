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
	virtual ~Enemy() {};
	void move(const int pathX[], const int pathY[], int pathLength);

	// Enemy Damaged
	void hit(int damage);
	int getX() const { return x; }
	int getY() const { return y; }
	int getPathPosition() const { return pathPosition; }
	int getHealth() const { return health; }
	

};

class smallEnemy : public Enemy {
public: 
	smallEnemy() : Enemy(5, 1) {} // Health 5, Speed 1
};

class mediumEnemy : public Enemy {
public:
	mediumEnemy() : Enemy(10, 2) {} // Health 10, Speed 2
};
class largeEnemy : public Enemy {
public:
	largeEnemy() : Enemy(20, 3) {} // Health 20, Speed 3
};