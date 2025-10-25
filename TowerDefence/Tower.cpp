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
    totalUpgradeCost += upgradeCost;
    upgradeCost += 300;
    return true;
}

bool basicTower::upgradeMultiShot() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    totalUpgradeCost += upgradeCost;
	multiShot = true; // Shott multiple projectiles
    return true;
}



bool longRangeTower::upgradeRange() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
    towerRange += 2; // Increase range
    totalUpgradeCost += upgradeCost;
    upgradeCost += 400;
    return true;
}

bool longRangeTower::upgradePierce() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    totalUpgradeCost += upgradeCost;
    pierce = true; // Piece enemies
    return true;
}

bool heavyDamageTower::upgradeRange() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;

    towerRange += 1; // Increase range
    totalUpgradeCost += upgradeCost;
    upgradeCost += 750;
    return true;
}

bool heavyDamageTower::upgradeSlow() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    totalUpgradeCost += upgradeCost;
    slow = true; // Slow enemies
    return true;
}


bool fourWayTower::upgradeFireRate() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
	fireRate -= 2; // Increase fire rate
    totalUpgradeCost += upgradeCost;
    upgradeCost += 2500;
    return true;
}

bool fourWayTower::upgradeRange() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    towerRange += 1; // Increase range
    totalUpgradeCost += upgradeCost;
    return true;
}
