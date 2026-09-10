#include <Windows.h>
#include <string>
#include <vector>
#include "../core/core.h"
#include "macros.h"

/**
 * Lunge swapping is when you left click with a zero cooldown item or your first
 * and move to your lunge spear in the same tick
 * by doing that yuo can use the spear's lunge enchantment
 * without its cooldown and be able to spam it.
 */
void lungeSwap(std::vector<std::string> keys) {
  std::string zcd = keys[0]; // zero cooldown
  std::string spear = keys[1];

  leftClick();
  keyPress(spear);

  preciseSleep(50);  // 1 tick

  keyPress(zcd);
}