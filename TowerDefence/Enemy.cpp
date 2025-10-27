#include "Enemy.h"

Enemy::Enemy(int h, int s)
	: health(h), pathPosition(0), speed(s), moveTick(0), x(0), y(0),
	enemySlowed(false), enemyBurned(false), burnDamage(0), burnDuration(0), slowDuration(0), slowTick(0),
	enemyDamaged(false), enemyBurnEffect(false)
{}

void Enemy::move(const int pathX[], const int pathY[], int pathLength)
{
	// Reaches end of path
	if (pathPosition >= pathLength)
        return;
    
	if (enemyBurned) {
		burnTick++;
		// Burn damage
		if (burnTick >= 20) { // Burn every 20 ticks
			health -= burnDamage;
			enemyBurnEffect = true;
			if (health < 0) health = 0;
			burnDuration--;
			burnTick = 0;
			if (burnDuration <= 0) { // How long burn lasts
				enemyBurned = false; // Remove burn effect
				
			}
		}

		
	}

	if (enemySlowed) {
		slowTick++;
		if (slowTick >= 20) { // Slow every 20 ticks
			slowDuration--;
			slowTick = 0;
			if (slowDuration <= 0) {
				speed -= slowAmount; 
				enemySlowed = false;// Remove slow effect
			}
		}
	}

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

void Enemy::enemySlow(int amount, int tick)
{
	if (!enemySlowed) {
		slowAmount = amount;
		speed += slowAmount;
		enemySlowed = true;
		slowDuration = tick; 
		slowTick = 0;
	}

}

void Enemy::enemyBurn(int amount, int tick)
{
	// Burn effet 
	if (!enemyBurned) {
		enemyBurned = true;
		burnDamage = amount;
		burnDuration = tick;
		burnTick = 0;

	}

}