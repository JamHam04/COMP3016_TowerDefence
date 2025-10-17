#pragma once
#include "Direction.h"


class Tower {
private:
	int towerPositionX, towerPositionY;
	Direction towerRotation;
	int towerDamage;
	int towerRange;

public:



	Tower(int x, int y, int d, int r, Direction dir);

	int getTowerX() const { return towerPositionX; }
	int getTowerY() const { return towerPositionY; }
	Direction getRotation() const { return towerRotation; }
	int getRange() const { return towerRange; }
	int getDamage() const { return towerDamage; }
};