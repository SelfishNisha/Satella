#include <iostream>
#include <atomic>
#include "core.h"
#include "config/config.h"
#include "../../lib/rang.hpp"

// returns the macro name based on their id
std::string getMacroName(int id) {
  switch (id) {
    case 1:
      return "Pearl Catch";
      break;

    case 2:
      return "Stun Slam";
      break;

    case 3:
      return "Breach Swap";
      break;

    case 4:
      return "Lunge Swap";
      break;

    case 5:
      return "Single Anchor";
      break;

    case 999:
      return "Panic (exit)";
      break;

    default:
      return "None";
      break;
  }
}

void registerHotkeys() {
  json config = getConfig();
  json macros = config["Macros"];

  // Loops through every macro
  for (json macro : macros) {
    // registering the hotkey only if the macro is enabled
    if (macro["Enabled"].get<bool>()) {
      std::string modKey = macro["Mod Key"].get<std::string>();
      std::string key = macro["Key"].get<std::string>();

      int id = macro["ID"].get<int>();

      bindHotkey(resolveKey(modKey), resolveKey(key), id);
    }
  }

  installHotkeyHook();

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    // The TUI posts this when config.json changes live -> rebind on this
    // thread, which owns the hook handle.
    if (msg.message == WM_APP + 1) {
      if (g_hotkeysDirty.exchange(false)) {
        rebindHotkeysOnHookThread();
      }
      continue;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}