#include <vector>
#include <string>
#include <Windows.h>
#include "macros.h"
#include "../core/core.h"

enum Speed {
  Slow = 200, // 4 tick
  Medium = 100, // 2 tick
  Fast = 50 // 1 tick
};

Speed getSpeed(std::string& speed) {
  if (speed == "Slow")
    return Speed::Slow;

  if (speed == "Medium")
    return Speed::Medium;

  if (speed == "Fast")
    return Speed::Fast;

  return Speed::Medium;
}

int getMs(Speed speed) {
  return static_cast<int>(speed);
}

/**
 * Pearl Catching is when you throw an ender pearl into the air and a windcharge
 * after inorder to make them hit each other in the air and give you an y level
 * advantage
 */
void pearlCatch(std::vector<std::string> keys, std::vector<ExtraValue> extra) {
  std::string pearl = keys[0];
  std::string windCharge = keys[1];

  std::string speedString = std::get<std::string>(extra[0]);
  Speed speed = getSpeed(speedString);

  keyPress(pearl);
  rightClick();

  preciseSleep(getMs(speed));

  keyPress(windCharge);
  rightClick();
}