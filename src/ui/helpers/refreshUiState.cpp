#include "../ui.h"
#include "core.h"

// clears stale status text and reloads the config if it changed on disk
void refreshUiState() {
  if (!gStatusMsg.empty() && std::chrono::steady_clock::now() >= gStatusExpiry) {
    gStatusMsg.clear();
    if (gStatusLabel) {
      gStatusLabel->set_text("");
    }
  }

  json fresh = loadConfig();
  if (fresh.dump() != gConfig.dump()) {
    gConfig = fresh;
    rebuildMacroCards(gScroll);
    g_hotkeysDirty = true;
    requestHotkeyRebuild();
    setStatus("Config reloaded from disk", 2500);
  }
}
