#include "Projectile.h"
// Projectile constructor
Projectile::Projectile(int x, int y, Direction dir, int s, int d, int r, int dis)
	: projX(x), projY(y), prevProjX(x), prevProjY(y), direction(dir), speed(s), damage(d),
	range(r), distance(dis), moveTick(0),
	penetrate(false), pierceCount(0), slow(false), burn(false)
{}

// Move projectile based on direction and speed
void Projectile::move() {
	// Store previous position
	prevProjX = projX;
	prevProjY = projY;

	// Move based on speed
	if (moveTick != speed) {
		moveTick++; // Increment move tick
	}
	// Move projectile
	else {
		moveTick = 0; // Reset move tick
		distance++; // Increment distance travelled
		// Move in direction
		switch (direction) {
		case UP:    projY--; break;
		case RIGHT: projX++; break;
		case DOWN:  projY++; break;
		case LEFT:  projX--; break;
		}
	}
}

// Check if projectile has reached max range
bool Projectile::maxRange() {
	return distance >= range;
}