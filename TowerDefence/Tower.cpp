#include "Tower.h"



Tower::Tower(int x, int y, int d, int r, Direction dir, int rate)
    : towerPositionX(x),
      towerPositionY(y),
      towerRotation(dir),
      towerDamage(d),
      towerRange(r),
      fireRate(rate),
      fireTick(rate) // Start charged or could be 0 if you prefer
{}