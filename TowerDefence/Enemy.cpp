#include "Enemy.h"

Enemy::Enemy(int h, int s)
    : health(h), pathPosition(0), speed(s), moveTick(0), x(0), y(0)
{}

void Enemy::move(const int pathX[], const int pathY[], int pathLength)
{
	// Reaches end of path
	if (pathPosition >= pathLength)
        return;
    

	// If at end
	if (moveTick != speed) {
		moveTick++;
	}
	else {
		x = pathX[pathPosition];
		y = pathY[pathPosition];
		pathPosition++; // Move 1
		moveTick = 0;
	}
}

void Enemy::hit(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
	enemyDamaged = true;
}
