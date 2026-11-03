#include "../ui.h"

// flips the enabled state for a macro and refreshes the config + hotkeys right away
void handleMacroToggle(const std::string& name, part<Border> border, part<Checkbox> checkbox, bool enabled) {
  gConfig["Macros"][name]["Enabled"] = enabled;
  checkbox->text_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  checkbox->focus_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  checkbox->hover_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  border->set_color(enabled ? Color(158, 206, 106) : Color(41, 46, 66));
  notifyConfigChanged();
  setStatus((enabled ? "Enabled  " : "Disabled ") + name, 1500);
}
