#include "../ui.h"

// save the edited value, push the config to disk, and show a quick status update
void saveMacroValue(const std::string& macroName, std::function<void(std::string)> write, std::string value) {
  write(std::move(value));
  notifyConfigChanged();
  setStatus("Saved " + macroName, 1500);
}
