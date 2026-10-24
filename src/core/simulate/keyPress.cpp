#include "../core.h"

/**
 * @param kc Keycode, can be a string or a VK
 */
void keyPress(std::variant<WORD, std::string> kc) {
  INPUT inputs[2] = {};
  WORD keyCode = resolveKey(kc);

  if (keyCode == VK_XBUTTON1 || keyCode == VK_XBUTTON2) {
    pressSideButton(kc);
  }

  // Key Down
  inputs[0].type = INPUT_KEYBOARD;
  inputs[0].ki.wVk = keyCode;

  // Key Up
  inputs[1].type = INPUT_KEYBOARD;
  inputs[1].ki.wVk = keyCode;
  inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

  SendInput(2, inputs, sizeof(INPUT));
}