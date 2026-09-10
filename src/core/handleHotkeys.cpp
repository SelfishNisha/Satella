#include <set>
#include <string>
#include <iostream>
#include <cstdlib>
#include "../macros/macros.h"
#include "config/config.h"

/**
 * @param hkid the hotkey's id, will be used to assign a function to it.
 * 
 * uses the hotkey's id to decide what function will be called upon press.
 */
void handleHotkeys(int hkid) {
  switch (hkid) {
    case 1:
      pearlCatch(getKeys("Pearl Catch"), getExtra("Pearl Catch"));
      break;

    case 2:
      stunSlam(getKeys("Stun Slam"), getExtra("Stun Slam"));
      break;

    case 3:
      breachSwap(getKeys("Breach Swap"));
      break;

    case 4:
      lungeSwap(getKeys("Lunge Swap"));
      break;

    case 5:
      singleAnchor(getKeys("Single Anchor"));
      break;
      
    case 999:
      exit(0);
      break;

    default:
      std::cout << "Unknown Hotkey\n";
      break;
  }
}