#pragma once
#include "Direction.h"
#include <string>
using namespace std;

enum towerType { BASIC, LONG_RANGE, HEAVY_DAMAGE, FOUR_WAY }; // Tower Types

class Tower {
protected:
	int towerPositionX, towerPositionY;
	Direction towerRotation;
	int towerDamage;
	int towerRange;
	int fireRate; 
	int fireTick;
	int towerCost;

	string upgrade1Name;
	string upgrade2Name;
	int upgrade1Level = 0;
	int upgrade2Level = 0;
	int maxUpgrade1Level = 3;
	int maxUpgrade2Level = 1;
	int upgrade1Cost = 100; // Initial upgrade cost
	int upgrade2Cost = 100;
	int totalUpgradeCost = 0;
	bool towerDelete = false;;
	
	

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
	int getTowerCost() const { return towerCost; }
	


	virtual bool upgradeRange() { return false; }
	virtual bool upgradeDamage() { return false; }
	virtual bool upgradeBurn() { return false; }

	void setTowerDelete() { towerDelete = true; }
	bool deleteTower() { return towerDelete; }


	int refundTower() {
		return (towerCost + totalUpgradeCost) / 2; // Refund half cost spent
	}

};

class basicTower : public Tower {
	public:
		bool burn = false; // Upgrade 3
		

		basicTower(int x, int y, Direction dir) : Tower(x, y, 1, 5, dir, 20) {
			towerCost = 50;
			upgrade1Cost = 150;
			upgrade2Cost = 500;
			upgrade1Name = "Damage";
			upgrade2Name = "Burn";
		} // Damage 1, Range 5, Fire Rate 20 (Adjust)
		virtual towerType getTowerType() const { return BASIC; }

		bool upgradeDamage() override;
		bool upgradeBurn();

		bool upgrade1() override { return upgradeDamage(); }
		bool upgrade2() override { return upgradeBurn(); }

		
};

class longRangeTower : public Tower {
	public:
		bool pierce = false;

		longRangeTower(int x, int y, Direction dir) : Tower(x, y, 1, 10, dir, 10) {
			towerCost = 200;
			upgrade1Cost = 250;
			upgrade2Cost = 1000;
			upgrade1Name = "Range";
			upgrade2Name = "Pierce";
		} // Damage 1, Range 10
		virtual towerType getTowerType() const { return LONG_RANGE; }
		
		bool upgradePierce();
		bool upgradeRange() override;

		bool upgrade1() override { return upgradeRange(); }
		bool upgrade2() override { return upgradePierce(); }
};

class heavyDamageTower : public Tower {
	public:
		bool slow = false;

		heavyDamageTower(int x, int y, Direction dir) : Tower(x, y, 3, 3, dir, 10) {
			towerCost = 350;
			upgrade1Cost = 250;
			upgrade2Cost = 600;
			upgrade1Name = "Range";
			upgrade2Name = "Slow";
		} // Damage 3, Range 3
		virtual towerType getTowerType() const { return HEAVY_DAMAGE; }
		
		bool upgradeRange() override;
		bool upgradeSlow();
		

		bool upgrade1() override { return upgradeRange(); }
		bool upgrade2() override { return upgradeSlow(); }
};

class fourWayTower : public Tower {
	int fireTicks[4] = { 0,0,0,0 }; // cooldown for each direction
	public:
		fourWayTower(int x, int y, Direction dir) : Tower(x, y, 1, 4, dir, 10) {
			towerCost = 500;
			upgrade1Cost = 1250;
			upgrade2Cost = 1500;
			upgrade1Name = "Fire Rate";
			upgrade2Name = "Range";
		} // Damage 1, Range 4, shoots in all directions
		virtual towerType getTowerType() const { return FOUR_WAY; }
		
		bool upgradeFireRate();
		bool upgradeRange() override;

		bool upgrade1() override { return upgradeFireRate(); }
		bool upgrade2() override { return upgradeRange(); }

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