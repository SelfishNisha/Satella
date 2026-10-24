#include "../core.h"

/**
 * @param kc Keycode, can be a string or a VK
 */
void pressSideButton(std::variant<WORD, std::string> kc) {
  WORD keyCode = resolveKey(kc);

  INPUT inputs[2] = {};

  // Determine which XBUTTON
  DWORD mouseFlags = (keyCode == VK_XBUTTON1) ? XBUTTON1 : XBUTTON2;

  // Mouse down
  inputs[0].type = INPUT_MOUSE;
  inputs[0].mi.dwFlags = (mouseFlags == XBUTTON1) ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XDOWN;
  inputs[0].mi.mouseData = mouseFlags;

  // Mouse up
  inputs[1].type = INPUT_MOUSE;
  inputs[1].mi.dwFlags = (mouseFlags == XBUTTON1) ? MOUSEEVENTF_XUP : MOUSEEVENTF_XUP;

  inputs[1].mi.mouseData = mouseFlags;

  SendInput(2, inputs, sizeof(INPUT));
}