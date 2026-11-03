#include "ui.h"

#include <functional>

part<Border> buildMacroCard(const std::string& name, const json& macro) {
  // this card is built from the saved config, so it reflects the current macro state
  bool enabled = macro.contains("Enabled") && macro["Enabled"].get<bool>();

  auto inner = mkpart<Vertical>();
  int rows = 0;

  auto title = mkpart<Label>(StyledText().bold(name));
  title->fg_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  addMacroCardRow(inner, title, rows);

  auto border = mkpart<Border>();
  border->fixed_height = rows + 2;
  border->height = rows + 2;
  border->set_color(enabled ? Color(158, 206, 106) : Color(41, 46, 66));
  border->add(inner);

  // the toggle is the master switch for this macro
  auto checkbox = mkpart<Checkbox>(StyledText("   Enabled"), enabled);
  checkbox->text_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  checkbox->focus_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  checkbox->hover_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  checkbox->on_change = std::bind(&handleMacroToggle, name, border, checkbox, std::placeholders::_1);
  addMacroCardRow(inner, checkbox, rows);

  // base key fields for every macro
  addMacroFieldRow(inner, "Mod Key", macro.value("Mod Key", std::string("")), name, std::bind(&setMacroFieldValue, name, "Mod Key", std::placeholders::_1), rows);

  addMacroFieldRow(inner, "Key", macro.value("Key", std::string("")), name, std::bind(&setMacroFieldValue, name, "Key", std::placeholders::_1), rows);

  if (macro.contains("Slots")) {
    auto section = mkpart<Label>("-- Slots");
    section->fg_color = Color(150, 155, 180);
    addMacroCardRow(inner, section, rows);
    for (auto &[slotName, slotVal] : macro["Slots"].items()) {
      addMacroFieldRow(inner, slotName, slotVal.get<std::string>(), name, std::bind(&setMacroSlotValue, name, slotName, std::placeholders::_1), rows);
    }
  }

  if (macro.contains("Extra")) {
    auto section = mkpart<Label>("-- Extra");
    section->fg_color = Color(150, 155, 180);
    addMacroCardRow(inner, section, rows);
    for (auto &[extraName, extraVal] : macro["Extra"].items()) {
      std::string initial;
      if (extraVal.is_string()) {
        initial = extraVal.get<std::string>();
      } else if (extraVal.is_boolean()) {
        initial = extraVal.get<bool>() ? "true" : "false";
      }
      addMacroFieldRow(inner, extraName, initial, name, std::bind(&setMacroExtraValue, name, extraName, std::placeholders::_1), rows);
    }
  }

  inner->fixed_height = rows;
  inner->height = rows;

  border->fixed_height = rows + 2;
  border->height = rows + 2;

  return border;
}