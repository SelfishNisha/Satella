// just so you know, claude wrote this, i have no idea what it does but it does a good job

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include "config/config.h"
#include "core.h"

static std::atomic<bool> g_physKeyState[256] = {};
static HHOOK g_hook = nullptr;
std::mutex g_hotkeyMutex;
std::atomic<bool> g_hotkeysDirty{false};
DWORD g_hookThreadId = 0;

// Per-hotkey repeat state, index-aligned with g_hotkeys (built once in
// installHotkeyHook()). Wrapped in unique_ptr because std::atomic can't be
// copied or moved, which would otherwise stop this vector from compiling.
struct HotkeyRuntime {
  std::atomic<bool> active{false};  // a repeat loop is currently running for
                                    // this hotkey
};
static std::vector<std::unique_ptr<HotkeyRuntime>> g_hotkeyRuntime;

// so binding "Shift" matches either physical shift key etc
static void setPhysState(WORD vk, bool down) {
  g_physKeyState[vk] = down;
  if (vk == VK_LSHIFT || vk == VK_RSHIFT)
    g_physKeyState[VK_SHIFT] = down;
  if (vk == VK_LCONTROL || vk == VK_RCONTROL)
    g_physKeyState[VK_CONTROL] = down;
  if (vk == VK_LMENU || vk == VK_RMENU)
    g_physKeyState[VK_MENU] = down;
}

// Runs on its own thread for as long as the hotkey's combo stays physically
// held down. Calls handleHotkeys(), THEN checks whether to loop again - so
// the next call can only ever start once the previous one has fully returned.
static void hotkeyRepeatLoop(size_t idx) {
  HotkeyBinding hk = {};
  HotkeyRuntime *rt = nullptr;
  {
    std::lock_guard<std::mutex> lk(g_hotkeyMutex);
    if (idx >= g_hotkeys.size() || idx >= g_hotkeyRuntime.size())
      return;
    hk = g_hotkeys[idx];
    rt = g_hotkeyRuntime[idx].get();
  }

  do {
    handleHotkeys(hk.id);
  } while (g_physKeyState[hk.keyVk] &&
           (hk.modVk == 0 || g_physKeyState[hk.modVk]));

  rt->active = false;
}

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam,
                                             LPARAM lParam) {
  if (nCode == HC_ACTION) {
    KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *)lParam;
    bool isInjected = (kb->flags & LLKHF_INJECTED) != 0;
    bool isKeyUp = (kb->flags & LLKHF_UP) != 0;
    WORD vk = (WORD)kb->vkCode;

    if (!isInjected) {
      bool wasDown = g_physKeyState[vk];
      setPhysState(vk, !isKeyUp);

      // fire only on the down transition, ignore key-repeat
      if (!isKeyUp && !wasDown) {
        std::vector<size_t> matches;
        {
          std::lock_guard<std::mutex> lk(g_hotkeyMutex);
          for (size_t i = 0; i < g_hotkeys.size(); ++i) {
            auto &hk = g_hotkeys[i];
            bool modOk = (hk.modVk == 0) || g_physKeyState[hk.modVk];
            if (modOk && hk.keyVk == vk)
              matches.push_back(i);
          }
        }
        // Start repeat loops outside the lock
        for (size_t i : matches) {
          bool expected = false;
          {
            std::lock_guard<std::mutex> lk(g_hotkeyMutex);
            if (i >= g_hotkeyRuntime.size())
              continue;
            auto &rt = *g_hotkeyRuntime[i];
            if (rt.active.compare_exchange_strong(expected, true)) {
              std::thread(hotkeyRepeatLoop, i).detach();
            }
          }
        }
      }
    }
    // injected keys: pass straight through, don't touch state or match hotkeys
  }
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Caller must hold g_hotkeyMutex.
void installHotkeyHook() {
  g_hookThreadId = GetCurrentThreadId();

  g_hotkeyRuntime.clear();
  g_hotkeyRuntime.reserve(g_hotkeys.size());
  for (size_t i = 0; i < g_hotkeys.size(); ++i)
    g_hotkeyRuntime.push_back(std::make_unique<HotkeyRuntime>());

  g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc,
                            GetModuleHandle(NULL), 0);
}

// Caller must hold g_hotkeyMutex.
void uninstallHotkeyHook() {
  if (g_hook) {
    UnhookWindowsHookEx(g_hook);
    g_hook = nullptr;
  }
}

// Rebinds g_hotkeys from config.json and reinstalls the hook. Must run on the
// hook thread, which owns the hook handle and its message loop.
void rebindHotkeysOnHookThread() {
  std::lock_guard<std::mutex> lk(g_hotkeyMutex);

  g_hotkeys.clear();
  json config = getConfig();
  json macros = config["Macros"];
  for (json macro : macros) {
    if (macro["Enabled"].get<bool>()) {
      bindHotkey(resolveKey(macro["Mod Key"].get<std::string>()),
                 resolveKey(macro["Key"].get<std::string>()),
                 macro["ID"].get<int>());
    }
  }

  uninstallHotkeyHook();
  installHotkeyHook();
}