#include "../ui.h"

// builds a single editor row for a macro field and wires it to the save helper
void addMacroFieldRow(part<Vertical> container, const std::string& labelText, const std::string& initial, const std::string& macroName, std::function<void(std::string)> write, int& rowCount) {
  auto row = mkpart<Horizontal>();
  auto label = mkpart<Label>(labelText);
  label->fg_color = Color(150, 155, 180);

  auto input = mkpart<Input>();
  input->set_text(initial);
  input->fixed_width = input->width = 22;
  input->placeholder = "...";

  auto changeHandler = saveMacroField(macroName, std::move(write));
  input->on_change = std::bind(&writeMacroField, changeHandler, std::placeholders::_1);

  row->add(label);
  row->add(input);
  addMacroCardRow(container, row, rowCount);
}
