#include "../ui.h"

// flips the enabled state for a macro and refreshes the config + hotkeys right away
void handleMacroToggle(const std::string& name, part<Border> border, bool enabled) {
  gConfig["Macros"][name]["Enabled"] = enabled;
  notifyConfigChanged();
  setStatus((enabled ? "Enabled  " : "Disabled ") + name, 1500);
  border->set_color(enabled ? Color(158, 206, 106) : Color(41, 46, 66));
}
