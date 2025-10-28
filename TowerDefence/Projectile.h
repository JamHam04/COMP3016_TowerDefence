#pragma once
#include "Direction.h"

class Projectile {
private:
	int projX, projY;
	int prevProjX, prevProjY;
	Direction direction;
	int speed;
	int damage;
	int range;
	int distance;
	int moveTick;
	bool penetrate; // Go through enemies
	int pierceCount; // Number of enemies pierced
	bool slow;
	bool burn;

public:
	Projectile(int x, int y, Direction dir, int s, int d, int range, int distance);

	void move();

	bool maxRange();

	int getProjX() const { return projX; }
	int getProjY() const { return projY; }
	int getPrevX() const { return prevProjX; }
	int getPrevY() const { return prevProjY; }
	int getDamage() const { return damage; }

	// Pierce Upgrade
	void setPenetrate(bool p) { penetrate = p; }
	bool canPenetrate() const { return penetrate; }
	void incrementPierceCount() { pierceCount++; }
	int getPierceCount() const { return pierceCount; }

	// Slow Upgrade
	void setSlow(bool s) { slow = s; }
	bool canSlow() const { return slow; }

	void setBurn(bool b) { burn = b; }
	bool canBurn() const { return burn; }
};