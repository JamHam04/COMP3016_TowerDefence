#pragma once
#include "Direction.h"

enum towerType { BASIC, LONG_RANGE, HEAVY_DAMAGE, FOUR_WAY }; // Tower Types

class Tower {
protected:
	int towerPositionX, towerPositionY;
	Direction towerRotation;
	int towerDamage;
	int towerRange;
	int fireRate; 
	int fireTick;

	int upgradeLevel = 1;
	int maxUpgradeLevel = 3;
	int upgradeCost = 100; // Initial upgrade cost
	

public:



	Tower(int x, int y, int d, int r, Direction dir, int rate);

	virtual ~Tower() {};
	virtual towerType getTowerType() const = 0;
	

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
		bool multiShot = false; // Upgrade 3

		basicTower(int x, int y, Direction dir) : Tower(x, y, 1, 5, dir, 20) {} // Damage 1, Range 5, Fire Rate 20 (Adjust)
		virtual towerType getTowerType() const { return BASIC; }
		virtual bool upgrade();
};

class longRangeTower : public Tower {
	public:
		bool pierce = false;

		longRangeTower(int x, int y, Direction dir) : Tower(x, y, 1, 10, dir, 10) {} // Damage 1, Range 10
		virtual towerType getTowerType() const { return LONG_RANGE; }
		virtual bool upgrade();
};

class heavyDamageTower : public Tower {
	public:
		bool slow = false;

		heavyDamageTower(int x, int y, Direction dir) : Tower(x, y, 3, 3, dir, 10) {} // Damage 3, Range 3
		virtual towerType getTowerType() const { return HEAVY_DAMAGE; }
		virtual bool upgrade();
};

class fourWayTower : public Tower {
	public:
		fourWayTower(int x, int y, Direction dir) : Tower(x, y, 1, 4, dir, 10) {} // Damage 1, Range 4, shoots in all directions
		virtual towerType getTowerType() const { return FOUR_WAY; }
		virtual bool upgrade();
};