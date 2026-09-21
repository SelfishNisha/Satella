// just so you know, claude wrote this, i have no idea what it does but it does a good job

#include <atomic>
#include <memory>
#include <thread>
#include <vector>
#include "core.h"

static std::atomic<bool> g_physKeyState[256] = {};
static HHOOK g_hook = nullptr;

// Per-hotkey repeat state, index-aligned with g_hotkeys (built once in
// installHotkeyHook()). Wrapped in unique_ptr because std::atomic can't be
// copied or moved, which would otherwise stop this vector from compiling.
struct HotkeyRuntime
{
  std::atomic<bool> active{false}; // a repeat loop is currently running for this hotkey
};
static std::vector<std::unique_ptr<HotkeyRuntime>> g_hotkeyRuntime;

// so binding "Shift" matches either physical shift key etc
static void setPhysState(WORD vk, bool down)
{
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
static void hotkeyRepeatLoop(size_t idx)
{
  const auto &hk = g_hotkeys[idx];
  auto &rt = *g_hotkeyRuntime[idx];

  do
  {
    handleHotkeys(hk.id);
  } while (g_physKeyState[hk.keyVk] &&
           (hk.modVk == 0 || g_physKeyState[hk.modVk]));

  rt.active = false;
}

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
  if (nCode == HC_ACTION)
  {
    KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *)lParam;
    bool isInjected = (kb->flags & LLKHF_INJECTED) != 0;
    bool isKeyUp = (kb->flags & LLKHF_UP) != 0;
    WORD vk = (WORD)kb->vkCode;

    if (!isInjected)
    {
      bool wasDown = g_physKeyState[vk];
      setPhysState(vk, !isKeyUp);

      // fire only on the down transition, ignore key-repeat
      if (!isKeyUp && !wasDown)
      {
        for (size_t i = 0; i < g_hotkeys.size(); ++i)
        {
          auto &hk = g_hotkeys[i];
          bool modOk = (hk.modVk == 0) || g_physKeyState[hk.modVk];
          if (modOk && hk.keyVk == vk)
          {
            auto &rt = *g_hotkeyRuntime[i];
            bool expected = false;
            // only start a repeat thread if one isn't already running for this hotkey
            if (rt.active.compare_exchange_strong(expected, true))
            {
              std::thread(hotkeyRepeatLoop, i).detach();
            }
            break;
          }
        }
      }
    }
    // injected keys: pass straight through, don't touch state or match hotkeys
  }
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void installHotkeyHook()
{
  g_hotkeyRuntime.clear();
  g_hotkeyRuntime.reserve(g_hotkeys.size());
  for (size_t i = 0; i < g_hotkeys.size(); ++i)
    g_hotkeyRuntime.push_back(std::make_unique<HotkeyRuntime>());

  g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
}