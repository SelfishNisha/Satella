#include <Windows.h>
#include <string>
#include <vector>
#include "../core/core.h"
#include "macros.h"

/**
 * When you charge a respawn anchor in overworld or the end it explodes.
 */
void singleAnchor(std::vector<std::string> keys) {
  std::string anchor = keys[0];
  std::string glowstone = keys[1];
  std::string totem = keys[2];

  keyPress(anchor);
  rightClick();

  preciseSleep(50); // 1 tick

  keyPress(glowstone);
  rightClick();

  preciseSleep(50); // 1 tick

  keyPress(totem);
  rightClick();
}