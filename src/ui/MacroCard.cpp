#include "ui.h"

#include <functional>

part<Border> buildMacroCard(const std::string &name, const json &macro) {
  bool enabled = macro.contains("Enabled") && macro["Enabled"].get<bool>();

  auto inner = mkpart<Vertical>();
  int rows = 0;

  auto addRow = [&](part<Widget> w) {
    inner->add(w);
    ++rows;
  };

  // Title: colored by enabled state
  auto title = mkpart<Label>(StyledText().bold(name));
  title->fg_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
  addRow(title);

  // The border wraps the whole card. Construct it here so the toggle below can
  // recolor it the instant the macro is enabled or disabled.
  auto border = mkpart<Border>();
  border->fixed_height = rows + 2;
  border->height = rows + 2;
  border->set_color(enabled ? Color(158, 206, 106) : Color(41, 46, 66));
  border->add(inner);

  // Enabled toggle
  auto chk = mkpart<Checkbox>(StyledText("   Enabled"), enabled);
  chk->on_change = [border, name](bool v) {
    g_config["Macros"][name]["Enabled"] = v;
    notifyConfigChanged();
    setStatus((v ? "Enabled  " : "Disabled ") + name, 1500);
    border->set_color(v ? Color(158, 206, 106) : Color(41, 46, 66));
  };
  addRow(chk);

  // Helper: a "label + input" row. The label stretches, the input stays fixed.
  auto fieldRow = [&](const std::string &labelText, const std::string &initial,
                      std::function<void(std::string)> onChange) {
    auto row = mkpart<Horizontal>();
    auto lbl = mkpart<Label>(labelText);
    lbl->fg_color = Color(150, 155, 180);
    auto inp = mkpart<Input>();
    inp->set_text(initial);
    inp->fixed_width = 22;
    inp->placeholder = "...";
    inp->on_change = [onChange = std::move(onChange)](std::string v) {
      onChange(std::move(v));
    };
    row->add(lbl);
    row->add(inp);
    addRow(row);
  };

  // Writes a field into the live config, saves to disk, and rebuilds hotkeys.
  auto saveField = [&](std::function<void(std::string)> write) {
    return [name, write = std::move(write)](std::string v) {
      write(std::move(v));
      notifyConfigChanged();
      setStatus("Saved " + name, 1500);
    };
  };

  fieldRow("Mod Key", macro.value("Mod Key", std::string("")),
           saveField([name](std::string v) {
             g_config["Macros"][name]["Mod Key"] = std::move(v);
           }));

  fieldRow("Key", macro.value("Key", std::string("")),
           saveField([name](std::string v) {
             g_config["Macros"][name]["Key"] = std::move(v);
           }));

  if (macro.contains("Slots")) {
    auto sec = mkpart<Label>("Slots");
    sec->fg_color = Color(150, 155, 180);
    addRow(sec);
    for (auto &[slotName, slotVal] : macro["Slots"].items()) {
      fieldRow(slotName, slotVal.get<std::string>(),
               saveField([name, slotName](std::string v) {
                 g_config["Macros"][name]["Slots"][slotName] = std::move(v);
               }));
    }
  }

  if (macro.contains("Extra")) {
    auto sec = mkpart<Label>("Extra");
    sec->fg_color = Color(150, 155, 180);
    addRow(sec);
    for (auto &[extraName, extraVal] : macro["Extra"].items()) {
      std::string initial;
      if (extraVal.is_string()) {
        initial = extraVal.get<std::string>();
      } else if (extraVal.is_boolean()) {
        initial = extraVal.get<bool>() ? "true" : "false";
      }
      fieldRow(extraName, initial,
               saveField([name, extraName](std::string v) {
                 g_config["Macros"][name]["Extra"][extraName] = std::move(v);
               }));
    }
  }

  inner->fixed_height = rows;
  inner->height = rows;

  // Final sizing of the wrapper so it matches the fully-built card.
  border->fixed_height = rows + 2;
  border->height = rows + 2;

  return border;
}