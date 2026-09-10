#include <Windows.h>
#include <string>
#include <vector>
#include "../core/core.h"
#include "macros.h"

/**
 * Stun Slamming is when you disable your opponent's shield mid air and hit them
 * with a mace
 */
void stunSlam(std::vector<std::string> keys) {
  std::string axe = keys[0];
  std::string mace = keys[1];

  keyPress(axe);
  leftClick();
  preciseSleep(53);  // 1.05 tick
  keyPress(mace);
  leftClick();
}