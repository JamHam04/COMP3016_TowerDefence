#pragma once
#include "Direction.h"

// Projectile class to manage projectiles fired by towers
class Projectile {
private:
	// Projectile attributes
	int projX, projY;
	int prevProjX, prevProjY;

	// Movement and stats
	Direction direction;
	int speed;
	int moveTick;
	int range;
	int distance;

	// Projectile damage
	int damage;
	
	// Projectile effects
	bool penetrate; // Go through enemies
	int pierceCount; // Number of enemies pierced
	bool slow; // Apply slow effect
	bool burn; // Apply burn effect

public:
	// Projectile constructor
	Projectile(int x, int y, Direction dir, int s, int d, int range, int distance);

	// Move projectile based on direction and speed
	void move();

	// Check if projectile has reached max range
	bool maxRange();

	// Getters
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

	// Burn Upgrade
	void setBurn(bool b) { burn = b; }
	bool canBurn() const { return burn; }
};