#include "Tower.h"



Tower::Tower(int x, int y, int d, int r, Direction dir, int rate)
{ 
	towerDamage = d;
	towerPositionX = x;
	towerPositionY = y;
	towerRotation = dir;
	towerRange = r;
	fireRate = rate;
	fireTick = rate; 
}