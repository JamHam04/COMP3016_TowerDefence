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

	int upgrade1Level = 0;
	int upgrade2Level = 0;
	int maxUpgrade1Level = 3;
	int maxUpgrade2Level = 1;
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
	int getUpgrade1Level() const { return upgrade1Level; }
	int getUpgrade2Level() const { return upgrade2Level; }
	int getUpgradeCost() const { return upgradeCost; }
	int getMaxUpgrade1Level() const { return maxUpgrade1Level; }
	int getMaxUpgrade2Level() const { return maxUpgrade2Level; }

	virtual bool upgradeRange() { return false; }
	virtual bool upgradeDamage() { return false; }
	virtual bool upgradeMultiShot() { return false; }

};

class basicTower : public Tower {
	public:
		bool multiShot = false; // Upgrade 3

		basicTower(int x, int y, Direction dir) : Tower(x, y, 1, 5, dir, 20) {} // Damage 1, Range 5, Fire Rate 20 (Adjust)
		virtual towerType getTowerType() const { return BASIC; }

		bool upgradeDamage() override;
		bool upgradeMultiShot();
};

class longRangeTower : public Tower {
	public:
		bool pierce = false;

		longRangeTower(int x, int y, Direction dir) : Tower(x, y, 1, 10, dir, 10) {} // Damage 1, Range 10
		virtual towerType getTowerType() const { return LONG_RANGE; }
		
		bool upgradePierce();
		bool upgradeRange() override;
};

class heavyDamageTower : public Tower {
	public:
		bool slow = false;

		heavyDamageTower(int x, int y, Direction dir) : Tower(x, y, 3, 3, dir, 10) {} // Damage 3, Range 3
		virtual towerType getTowerType() const { return HEAVY_DAMAGE; }
		
		bool upgradeSlow();
		bool upgradeRange() override;
};

class fourWayTower : public Tower {
	int fireTicks[4] = { 0,0,0,0 }; // cooldown for each direction
	public:
		fourWayTower(int x, int y, Direction dir) : Tower(x, y, 1, 4, dir, 10) {} // Damage 1, Range 4, shoots in all directions
		virtual towerType getTowerType() const { return FOUR_WAY; }
		
		bool upgradeFireRate();
		bool upgradeRange() override;

		void incrementFireTicks() {
			for (int i = 0; i < 4; i++) // all four direcxtions
				fireTicks[i]++;
		}

		bool canFire(Direction dir) const {
			return fireTicks[dir] >= fireRate; 
		}

		void resetFireTick(Direction dir) {
			fireTicks[dir] = 0;
		}
};