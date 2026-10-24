#include <algorithm>
#include <unordered_map>
#include "core.h"

WORD resolveKey(const std::string& key) {
  // Single character
  if (key.length() == 1) {
    char c = toupper(key[0]);
    if (c >= 'A' && c <= 'Z') {
      return static_cast<WORD>(c);
    }
    if (c >= '0' && c <= '9') {
      return static_cast<WORD>(c);
    }
  }

  // Special keys mapping
  static const std::unordered_map<std::string, WORD> keyMap = {
      // Function keys
      {"F1", VK_F1},
      {"F2", VK_F2},
      {"F3", VK_F3},
      {"F4", VK_F4},
      {"F5", VK_F5},
      {"F6", VK_F6},
      {"F7", VK_F7},
      {"F8", VK_F8},
      {"F9", VK_F9},
      {"F10", VK_F10},
      {"F11", VK_F11},
      {"F12", VK_F12},

      // Navigation
      {"ENTER", VK_RETURN},
      {"RETURN", VK_RETURN},
      {"SPACE", VK_SPACE},
      {"TAB", VK_TAB},
      {"ESC", VK_ESCAPE},
      {"ESCAPE", VK_ESCAPE},
      {"BACK", VK_BACK},
      {"BACKSPACE", VK_BACK},
      {"DELETE", VK_DELETE},
      {"DEL", VK_DELETE},
      {"INSERT", VK_INSERT},
      {"INS", VK_INSERT},
      {"HOME", VK_HOME},
      {"END", VK_END},
      {"PAGEUP", VK_PRIOR},
      {"PGUP", VK_PRIOR},
      {"PAGEDOWN", VK_NEXT},
      {"PGDN", VK_NEXT},

      // Arrow keys
      {"UP", VK_UP},
      {"DOWN", VK_DOWN},
      {"LEFT", VK_LEFT},
      {"RIGHT", VK_RIGHT},

      // Modifiers
      {"SHIFT", VK_SHIFT},
      {"CTRL", VK_CONTROL},
      {"CONTROL", VK_CONTROL},
      {"ALT", VK_MENU},
      {"WIN", VK_LWIN},
      {"WINDOWS", VK_LWIN},

      // Punctuation
      {".", VK_OEM_PERIOD},
      {",", VK_OEM_COMMA},
      {";", VK_OEM_1},
      {"'", VK_OEM_7},
      {"[", VK_OEM_4},
      {"]", VK_OEM_6},
      {"\\", VK_OEM_5},
      {"/", VK_OEM_2},
      {"-", VK_OEM_MINUS},
      {"=", VK_OEM_PLUS},
      {"`", VK_OEM_3},

      // Numpad
      {"NUMLOCK", VK_NUMLOCK},
      {"NUM", VK_NUMLOCK},
      {"NUMPAD0", VK_NUMPAD0},
      {"NUMPAD1", VK_NUMPAD1},
      {"NUMPAD2", VK_NUMPAD2},
      {"NUMPAD3", VK_NUMPAD3},
      {"NUMPAD4", VK_NUMPAD4},
      {"NUMPAD5", VK_NUMPAD5},
      {"NUMPAD6", VK_NUMPAD6},
      {"NUMPAD7", VK_NUMPAD7},
      {"NUMPAD8", VK_NUMPAD8},
      {"NUMPAD9", VK_NUMPAD9},
      {"MULTIPLY", VK_MULTIPLY},
      {"ADD", VK_ADD},
      {"SUBTRACT", VK_SUBTRACT},
      {"DIVIDE", VK_DIVIDE},

      // Other
      {"CAPSLOCK", VK_CAPITAL},
      {"CAPS", VK_CAPITAL},
      {"SCROLLLOCK", VK_SCROLL},
      {"SCROLL", VK_SCROLL},
      {"PRINTSCREEN", VK_SNAPSHOT},
      {"PRTSC", VK_SNAPSHOT},
      {"PAUSE", VK_PAUSE},
      {"BREAK", VK_PAUSE},
      {"MOUSE_SIDE_BUTTON_FRONT", VK_XBUTTON2},
      {"MOUSE_SIDE_BUTTON_BACK", VK_XBUTTON1},
  };

  auto it = keyMap.find(key);
  if (it != keyMap.end()) {
    return it->second;
  }

  return 0;  // Unknown key
}

// Overload for WORD
WORD resolveKey(WORD key) { return key; }

// Overload for variant
WORD resolveKey(const std::variant<WORD, std::string>& key) {
  if (std::holds_alternative<WORD>(key)) {
    return std::get<WORD>(key);
  } else {
    return resolveKey(std::get<std::string>(key));
  }
}