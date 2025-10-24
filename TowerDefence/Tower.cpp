#include "Tower.h"



Tower::Tower(int x, int y, int d, int r, Direction dir, int rate)
    : towerPositionX(x),
      towerPositionY(y),
      towerRotation(dir),
      towerDamage(d),
      towerRange(r),
      fireRate(rate),
      fireTick(rate) 
{}


bool basicTower::upgradeDamage() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
    towerDamage += 1; // Increase damage
    upgradeCost += 300;
    return true;
}

bool basicTower::upgradeMultiShot() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
	multiShot = true; // Shott multiple projectiles
    return true;
}



bool longRangeTower::upgradeRange() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
    towerRange += 2; // Increase range
    upgradeCost += 400;
    return true;
}

bool longRangeTower::upgradePierce() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    pierce = true; // Piece enemies
    return true;
}

bool heavyDamageTower::upgradeRange() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
    towerRange += 1; // Increase range
    upgradeCost += 750;
    return true;
}

bool heavyDamageTower::upgradeSlow() {
    if (upgrade2Level >= maxUpgrade1Level) return false;

    upgrade2Level++;
    slow = true; // Slow enemies
    return true;
}


bool fourWayTower::upgradeFireRate() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
	fireRate += 2; // Increase fire rate
    upgradeCost += 1000;
    return true;
}

bool fourWayTower::upgradeRange() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    towerRange += 1; // Increase range
    return true;
}
