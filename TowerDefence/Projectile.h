#pragma once
#include "Direction.h"

class Projectile {
private:
	int projX, projY;
	Direction direction;
	int speed;
	int damage;
	int moveTick;
	bool penetate; // Go through enemies

public:
	Projectile(int x, int y, Direction dir, int s, int d);

	void move();

	int getProjX() const { return projX; }
	int getProjY() const { return projY; }
	int getDamage() const { return damage; }
	bool canPenetrate() const { return penetate; }
};