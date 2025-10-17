#include "Tower.h"



Tower::Tower(int x, int y, int d, int r, Direction dir)
{ 
	towerDamage = d;
	towerPositionX = x;
	towerPositionY = y;
	towerRotation = dir;
	towerRange = r;

}