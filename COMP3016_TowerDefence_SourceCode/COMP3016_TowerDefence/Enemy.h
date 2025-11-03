#pragma once

// Enemy types: SMALL, MEDIUM, LARGE
enum enemyType { SMALL, MEDIUM, LARGE };

// Enemy class to manage enemy stats and movement
class Enemy {
private:
	// Enemy stats
	int health;
	int speed;

	// Enemy position
	int x, y; //Coordinates
	int prevX, prevY;
	int pathPosition;
	
	// Enemy movement
	int moveTick;

	// Enemy hit effect
	bool enemyDamaged;

	// Slow effect
	int slowAmount;
	bool enemySlowed;
	int slowDuration;
	int slowTick;

	// Burn effect
	int burnDamage;
	int burnTick;
	int burnDuration;
	bool enemyBurned;
	bool enemyBurnEffect;

public:

	// Enemy constructor
	Enemy(int h, int s);
	virtual ~Enemy() {};

	// Move enemy along path
	void move(const int pathX[], const int pathY[], int pathLength);

	// Enemy Damaged
	void hit(int damage);
	bool enemyHitEffect() { return enemyDamaged; }
	void resetHitEffect() { enemyDamaged = false; }
	bool enemyBurnHitEffect() { return enemyBurnEffect; }
	void resetBurnHitEffect() { enemyBurnEffect = false; }

	// Slow effect
	void enemySlow(int amount, int tick); 
	void enemyBurn(int amount, int tick);

	// Getters
	int getX() const { return x; }
	int getY() const { return y; }
	int getPrevX() const { return prevX; }
	int getPrevY() const { return prevY; }
	int getPathPosition() const { return pathPosition; }
	int getHealth() const { return health; }

	// Get enemy type
	virtual enemyType getEnemyType() const = 0;
};

// Small Enemy class
class smallEnemy : public Enemy {
public: 
	smallEnemy() : Enemy(5, 7) {} // Health 5, Speed 7
	virtual enemyType getEnemyType() const { return SMALL; }
};

// Medium Enemy class
class mediumEnemy : public Enemy {
public:
	mediumEnemy() : Enemy(12, 9) {} // Health 12, Speed 9
	virtual enemyType getEnemyType() const { return MEDIUM; }
};

// Large Enemy class
class largeEnemy : public Enemy {
public:
	largeEnemy() : Enemy(25, 12) {} // Health 25, Speed 12
	virtual enemyType getEnemyType() const { return LARGE; }
};

