#include "Projectile.h"

Projectile::Projectile(int x, int y, Direction dir, int s, int d, int r, int dis) {
	projX = x;
	projY = y;
	direction = dir;
	speed = s;
	damage = d;
	moveTick = 0;
	penetrate = false;
	slow = false;
	burn = false;
	range = r;
	distance = dis;

}

void Projectile::move() {



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