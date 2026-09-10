#include <Windows.h>
#include <string>
#include <vector>
#include "../core/core.h"
#include "macros.h"

/**
 * Breach swapping is when you hit someone with your sword (not reqired to be a sword)
 * and switch to a breach mace in the same tick
 * by doing that you combine the breach enchantment with your sword's damage
 * and deal a much more damage to your opponent
 */
void breachSwap(std::vector<std::string> keys) {
  std::string sword = keys[0];
  std::string mace = keys[1];

  leftClick();
  keyPress(mace);
  
  preciseSleep(50);  // 1 tick

  keyPress(sword);
}