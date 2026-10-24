#pragma once

#include <Windows.h>
#include <atomic>
#include <mutex>
#include <set>
#include <string>
#include <variant>
#include <vector>

struct HotkeyBinding {
  WORD modVk;
  WORD keyVk;
  int id;
};

extern std::vector<HotkeyBinding> g_hotkeys;

// Guards g_hotkeys / g_hook so the TUI thread and the hook thread don't
// touch them at the same time.
extern std::mutex g_hotkeyMutex;

// Set by the TUI whenever config.json changes; consumed by the hook thread.
extern std::atomic<bool> g_hotkeysDirty;

// Thread id of the thread running the hook message loop (set by
// installHotkeyHook).
extern DWORD g_hookThreadId;

void bindHotkey(int mk, WORD k, int id);
void handleHotkeys(int hkid);

void leftClick();
void rightClick();
void pressSideButton(std::variant<WORD, std::string> kc);
void keyPress(std::variant<WORD, std::string> kc);

WORD resolveKey(const std::string& key);
WORD resolveKey(WORD key);
WORD resolveKey(const std::variant<WORD, std::string>& key);

void registerHotkeys();

// Caller must hold g_hotkeyMutex.
void installHotkeyHook();
// Caller must hold g_hotkeyMutex.
void uninstallHotkeyHook();
// Rebinds g_hotkeys from config.json and reinstalls the hook. Must run on
// the hook thread (it owns the hook handle and message loop).
void rebindHotkeysOnHookThread();

void preciseSleep(double ms);