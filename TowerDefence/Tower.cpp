#include "Tower.h"



Tower::Tower(int x, int y, int d, int r, Direction dir, int rate)
    : towerPositionX(x), towerPositionY(y),
    towerDamage(d), towerRange(r), towerRotation(dir),
    fireRate(rate), fireTick(rate),
    towerCost(0), upgrade1Level(0), upgrade2Level(0), totalUpgradeCost(0),
    towerDelete(false)
{
}



bool basicTower::upgradeDamage() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
    towerDamage += 1; // Increase damage
    totalUpgradeCost += upgrade1Cost;
    upgrade1Cost += 100;
    return true;
}

bool basicTower::upgradeBurn() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    totalUpgradeCost += upgrade2Cost;
	burn = true; // Burn Enemies
    return true;
}



bool longRangeTower::upgradeRange() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
    towerRange += 2; // Increase range
    totalUpgradeCost += upgrade1Cost;
    upgrade1Cost += 150;
    return true;
}

bool longRangeTower::upgradePierce() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    totalUpgradeCost += upgrade2Cost;
    pierce = true; // Piece enemies
    return true;
}

bool heavyDamageTower::upgradeRange() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;

    towerRange += 1; // Increase range
    totalUpgradeCost += upgrade1Cost;
    upgrade1Cost += 200;
    return true;
}

bool heavyDamageTower::upgradeSlow() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    totalUpgradeCost += upgrade2Cost;
    slow = true; // Slow enemies
    return true;
}


bool fourWayTower::upgradeFireRate() {
    if (upgrade1Level >= maxUpgrade1Level) return false;

    upgrade1Level++;
	fireRate -= 2; // Increase fire rate
    totalUpgradeCost += upgrade1Cost;
    upgrade1Cost += 250;
    return true;
}

bool fourWayTower::upgradeRange() {
    if (upgrade2Level >= maxUpgrade2Level) return false;

    upgrade2Level++;
    towerRange += 1; // Increase range
    totalUpgradeCost += upgrade2Cost;
    return true;
}
