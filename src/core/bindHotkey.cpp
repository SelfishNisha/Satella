#include "core.h"

std::vector<HotkeyBinding> g_hotkeys;

/**
 * @param mk the key modifier, MOD_ALT, MOD_CONTROL, 0
 * @param k the key, k, e, etc.
 * @param id the hotkey's id, can not be the same as another hotkey's id
 *
 * the function sets a keybound for the key combo given to it.
 */
void bindHotkey(int mk, WORD k, int id) {
  g_hotkeys.push_back({ (WORD)mk, k, id });
}