#include "../ui.h"
#include "core.h"

// save the edited config, clear the cache, and tell the hotkey hook to rebuild
void notifyConfigChanged() {
  saveConfig(gConfig);
  invalidateConfigCache();
  setStatus("Saved to config.json", 1500);
  g_hotkeysDirty = true;
  requestHotkeyRebuild();
}
