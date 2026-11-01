#include "../ui.h"
#include "core.h"

// marks hotkeys dirty and posts a rebuild message to the hook thread
void requestHotkeyRebuild() {
  g_hotkeysDirty = true;
  if (g_hookThreadId != 0) {
    PostThreadMessage(g_hookThreadId, WM_APP + 1, 0, 0);
  }
}
