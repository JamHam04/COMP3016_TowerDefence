#include "Enemy.h"
// Enemy constructor
Enemy::Enemy(int h, int s)
	: health(h), pathPosition(0), speed(s), moveTick(0), x(0), y(0), prevX(0), prevY(0),
	enemySlowed(false), slowAmount(0), slowDuration(0), slowTick(0),
	enemyBurned(false), burnDamage(0), burnDuration(0), burnTick(0),
	enemyDamaged(false), enemyBurnEffect(false)
{}

// Move enemy along path
void Enemy::move(const int pathX[], const int pathY[], int pathLength)

{
	// Get previous position
	prevX = x;
	prevY = y;

	// Reaches end of path
	if (pathPosition >= pathLength)
        return;
    
	// Apply burn effect
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

	// Apply slow effect
	if (enemySlowed) {
		slowTick++;
		if (slowTick >= 20) { // Slow every 20 ticks
			slowDuration--;
			slowTick = 0;
			if (slowDuration <= 0) {
				speed -= slowAmount;
				if (speed < 0) speed = 0; // Prevent speed going under 0
				enemySlowed = false;// Remove slow effect
			}
		}
	}

	// Move based on speed
	if (moveTick != speed) {
		moveTick++;
	}

	// Move enemy
	else {
		x = pathX[pathPosition];
		y = pathY[pathPosition];
		pathPosition++;
		moveTick = 0;
	}
}

// Enemy Damaged
void Enemy::hit(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
	enemyDamaged = true;
}

// Apply slow effect to enemy
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

// Apply burn effect to enemy
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