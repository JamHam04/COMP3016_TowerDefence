#pragma once
#include "Direction.h"
#include <string>
using namespace std;

// Tower Types
enum towerType { BASIC, LONG_RANGE, HEAVY_DAMAGE, FOUR_WAY }; // Tower Types

// Base Tower class
class Tower {
protected:
	// Tower position and rotation
	int towerPositionX, towerPositionY;
	Direction towerRotation;

	// Tower stats
	int towerDamage;
	int towerRange;
	int fireRate; 
	int fireTick;
	int towerCost;

	// Upgrades
	string upgrade1Name;
	string upgrade2Name;
	int upgrade1Level = 0;
	int upgrade2Level = 0;
	int maxUpgrade1Level = 3;
	int maxUpgrade2Level = 1;
	int upgrade1Cost = 100; 
	int upgrade2Cost = 100;
	int totalUpgradeCost = 0;

	// Tower deletion
	bool towerDelete = false;;

public:
	// Tower constructor
	Tower(int x, int y, int d, int r, Direction dir, int rate); 
	virtual ~Tower() {};

	// Get tower type
	virtual towerType getTowerType() const = 0;
	
	// Fire management
	void incrementFireTick() {
		// Fire delay
		if (fireTick < fireRate)
			fireTick++;
	}

	// Reset fire tick after firing
	void resetFireTick() {
		fireTick = 0;
	}

	// Tower position and rotation getters
	int getTowerX() const { return towerPositionX; }
	int getTowerY() const { return towerPositionY; }
	Direction getRotation() const { return towerRotation; }

	// Tower stats getters
	int getRange() const { return towerRange; }
	int getDamage() const { return towerDamage; }
	int getFireRate() const { return fireRate; }
	int getFireTick() const { return fireTick; }

	// Upgrade getters and methods
	string getUpgrade1Name() const { return upgrade1Name; }
	string getUpgrade2Name() const { return upgrade2Name; }
	int getUpgrade1Level() const { return upgrade1Level; }
	int getUpgrade2Level() const { return upgrade2Level; }
	int getUpgrade1Cost() const { return upgrade1Cost; }
	int getUpgrade2Cost() const { return upgrade2Cost; }
	int getMaxUpgrade1Level() const { return maxUpgrade1Level; }
	int getMaxUpgrade2Level() const { return maxUpgrade2Level; }
	virtual bool upgrade1() { return false; }
	virtual bool upgrade2() { return false; }

	// Tower cost getter
	int getTowerCost() const { return towerCost; }

	// Upgrade methods
	virtual bool upgradeRange() { return false; }
	virtual bool upgradeDamage() { return false; }
	virtual bool upgradeBurn() { return false; }

	// Tower deletion methods
	void setTowerDelete() { towerDelete = true; }
	bool deleteTower() { return towerDelete; }

	// Refund tower cost
	int refundTower() {
		return (towerCost + totalUpgradeCost) / 2; // Refund half cost spent
	}

};

// Basic Tower class
class basicTower : public Tower {
	public:
		bool burn = false; 
		
		// Basic Tower constructor
		basicTower(int x, int y, Direction dir) : Tower(x, y, 1, 5, dir, 20) { 
			towerCost = 50;
			upgrade1Cost = 100;
			upgrade2Cost = 250;
			upgrade1Name = "Damage";
			upgrade2Name = "Burn";
		} // Damage 1, Range 5, Fire Rate 20
		virtual towerType getTowerType() const { return BASIC; }

		// Upgrade methods
		bool upgradeDamage() override;
		bool upgradeBurn();

		bool upgrade1() override { return upgradeDamage(); }
		bool upgrade2() override { return upgradeBurn(); }

		
};

// Long Range Tower class
class longRangeTower : public Tower {
	public:
		bool pierce = false;

		// Long Range Tower constructor
		longRangeTower(int x, int y, Direction dir) : Tower(x, y, 1, 10, dir, 10) {
			towerCost = 200;
			upgrade1Cost = 50;
			upgrade2Cost = 600;
			upgrade1Name = "Range";
			upgrade2Name = "Pierce";
		} // Damage 1, Range 10, Fire Rate 10
		virtual towerType getTowerType() const { return LONG_RANGE; }
		
		// Upgrade methods
		bool upgradePierce();
		bool upgradeRange() override;

		bool upgrade1() override { return upgradeRange(); }
		bool upgrade2() override { return upgradePierce(); }
};

// Heavy Damage Tower class
class heavyDamageTower : public Tower {
	public:
		bool slow = false;

		// Heavy Damage Tower constructor
		heavyDamageTower(int x, int y, Direction dir) : Tower(x, y, 5, 3, dir, 40) {
			towerCost = 350;
			upgrade1Cost = 200;
			upgrade2Cost = 300;
			upgrade1Name = "Range";
			upgrade2Name = "Slow";
		} // Damage 5, Range 3, Fire Rate 40
		virtual towerType getTowerType() const { return HEAVY_DAMAGE; }
		
		// Upgrade methods
		bool upgradeRange() override;
		bool upgradeSlow();
		

		bool upgrade1() override { return upgradeRange(); }
		bool upgrade2() override { return upgradeSlow(); }
};

// Four Way Tower class
class fourWayTower : public Tower {
	int fireTicks[4] = { 0,0,0,0 }; // cooldown for each direction
	public:
		// Four Way Tower constructor
		fourWayTower(int x, int y, Direction dir) : Tower(x, y, 2, 4, dir, 15) {
			towerCost = 500;
			upgrade1Cost = 350;
			upgrade2Cost = 450;
			upgrade1Name = "Fire Rate";
			upgrade2Name = "Range";
		} // Damage 2, Range 4, Fire Rate 15, shoots in all directions
		virtual towerType getTowerType() const { return FOUR_WAY; }
		
		// Upgrade methods
		bool upgradeFireRate();
		bool upgradeRange() override;

		bool upgrade1() override { return upgradeFireRate(); }
		bool upgrade2() override { return upgradeRange(); }

		// Fire management for four directions
		void incrementFireTicks() {
			for (int i = 0; i < 4; i++) // all four direcxtions
				fireTicks[i]++;
		}

		// Check if can fire in a direction
		bool canFire(Direction dir) const {
			return fireTicks[dir] >= fireRate; 
		}

		// Reset fire tick for a single direction after firing
		void resetFireTick(Direction dir) {
			fireTicks[dir] = 0;
		}
};