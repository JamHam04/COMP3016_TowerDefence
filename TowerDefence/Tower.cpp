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


bool basicTower::upgrade() {
    if (upgradeLevel >= maxUpgradeLevel) return false; // Max upgrades

    upgradeLevel++; // Increase upgrade level
    switch (upgradeLevel) {
    case 2: towerDamage += 1; // Upgrade 2 - Increase damage
        upgradeCost += 300;
        break;      
    case 3: multiShot = true; // Upgrade 3 - Enable multi-shot
        upgradeCost += 500;
        break;      
    }
    
    return true;
}

bool longRangeTower::upgrade() {
    if (upgradeLevel >= maxUpgradeLevel) return false;
    upgradeLevel++;
    switch (upgradeLevel) {
    case 2: pierce = true; // Upgrade 2 - Pierce enemies
        upgradeCost += 100;
        break;       
    case 3: towerRange += 2; // Upgrade 3 - Increase range
        upgradeCost += 100;
        break;     
    }

    return true;
};

bool heavyDamageTower::upgrade() {
    if (upgradeLevel >= maxUpgradeLevel) return false;
    upgradeLevel++;
    switch (upgradeLevel) {
    case 2: slow = true; // Upgrade 2 - Slow enemies
        upgradeCost += 100;
        break;          
    case 3: towerRange += 1; // Upgrade 3: Increase range
        upgradeCost += 100;
        break;      
    }
    
    return true;
}

bool fourWayTower::upgrade() {
    if (upgradeLevel >= maxUpgradeLevel) return false;
    upgradeLevel++;
    switch (upgradeLevel) {
    case 2: fireRate += 2; // Upgrade 2: Faster fire
        upgradeCost += 100;
        break; 
    case 3: towerRange += 1; // Upgrade 3: Increase range
        upgradeCost += 100;
        break;                        
    }
    return true;
}
