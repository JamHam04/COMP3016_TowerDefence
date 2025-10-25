#pragma once
#include "Direction.h"

class Projectile {
private:
	int projX, projY;
	Direction direction;
	int speed;
	int damage;
	int range;
	int distance;
	int moveTick;
	bool penetrate; // Go through enemies
	bool slow;

public:
	Projectile(int x, int y, Direction dir, int s, int d, int range, int distance);

	void move();

	bool maxRange();

	int getProjX() const { return projX; }
	int getProjY() const { return projY; }
	int getDamage() const { return damage; }

	// Pierce Upgrade
	void setPenetrate(bool p) { penetrate = p; }
	bool canPenetrate() const { return penetrate; }

	// Slow Upgrade
	void setSlow(bool s) { slow = s; }
	bool canSlow() const { return slow; }
};