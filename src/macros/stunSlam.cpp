#include <Windows.h>
#include <string>
#include <vector>
#include <variant>
#include "../core/core.h"
#include "macros.h"

/**
 * Stun Slamming is when you disable your opponent's shield mid air and hit them
 * with a mace
 */
void stunSlam(std::vector<std::string> keys, std::vector<ExtraValue> extra) {
  std::string axe = keys[0];
  std::string mace = keys[1];

  std::string switchBackTo = std::get<std::string>(extra[0]);

  keyPress(axe);
  leftClick();
  preciseSleep(53);  // 1.05 tick
  keyPress(mace);
  leftClick();
  
  if (switchBackTo.compare("")) {
    preciseSleep(53); // 1.05 tick
    keyPress(switchBackTo);
  }
}