#include "Projectile.h"

Projectile::Projectile(int x, int y, Direction dir, int s, int d) {
	projX = x;
	projY = y;
	direction = dir;
	speed = s;
	damage = d;
	moveTick = 0;
	penetate = false;
}

void Projectile::move() {



	if (moveTick != speed) {
		moveTick++;
	}
	else {
		moveTick = 0;
		switch (direction) {
		case UP:    projY--; break;
		case RIGHT: projX++; break;
		case DOWN:  projY++; break;
		case LEFT:  projX--; break;
		}
	}
	// Prevent going out map
}