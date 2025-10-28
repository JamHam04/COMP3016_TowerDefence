#include "Projectile.h"

Projectile::Projectile(int x, int y, Direction dir, int s, int d, int r, int dis)
	: projX(x), projY(y), prevProjX(x), prevProjY(y), direction(dir), speed(s), damage(d),
	range(r), distance(dis), moveTick(0),
	penetrate(false), pierceCount(0), slow(false), burn(false)
{
}


void Projectile::move() {

	prevProjX = projX;
	prevProjY = projY;

	if (moveTick != speed) {
		moveTick++;
	}
	else {
		moveTick = 0;
		distance++;
		switch (direction) {
		case UP:    projY--; break;
		case RIGHT: projX++; break;
		case DOWN:  projY++; break;
		case LEFT:  projX--; break;
		}
	}
	// Prevent going out map
}

bool Projectile::maxRange() {
	return distance >= range;
}