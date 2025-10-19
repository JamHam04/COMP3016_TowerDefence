#pragma once
#include "Direction.h"


class Tower {
private:
	int towerPositionX, towerPositionY;
	Direction towerRotation;
	int towerDamage;
	int towerRange;
	int fireRate; 
	int fireTick;

public:



	Tower(int x, int y, int d, int r, Direction dir, int rate);

	virtual ~Tower() {};

	void incrementFireTick() {
		// Fire delay
		if (fireTick < fireRate)
			fireTick++;
	}

	void resetFireTick() {
		fireTick = 0;
	}

	int getTowerX() const { return towerPositionX; }
	int getTowerY() const { return towerPositionY; }
	Direction getRotation() const { return towerRotation; }
	int getRange() const { return towerRange; }
	int getDamage() const { return towerDamage; }
	int getFireRate() const { return fireRate; }
	int getFireTick() const { return fireTick; }
};

class basicTower : public Tower {
	public:
		basicTower(int x, int y, Direction dir) : Tower(x, y, 1, 5, dir, 20) {} // Damage 1, Range 5, Fire Rate 20 (Adjust)
};

class longRangeTower : public Tower {
	public:
	longRangeTower(int x, int y, Direction dir)
		: Tower(x, y, 1, 10, dir, 10) {} // Damage 1, Range 10
};

class heavyDamageTower : public Tower {
	public:
	heavyDamageTower(int x, int y, Direction dir)
		: Tower(x, y, 3, 4, dir, 10) {} // Damage 3, Range 4
};

class fourWayTower : public Tower {
	public:
		fourWayTower(int x, int y, Direction dir)
		: Tower(x, y, 1, 5, dir, 10) {} // Damage 1, Range 5, shoots in all directions
};