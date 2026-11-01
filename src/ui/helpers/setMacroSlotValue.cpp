#include "../ui.h"

// stores a slot value in the live macro config object without reloading the whole app
void setMacroSlotValue(const std::string& macroName, const std::string& slotName, std::string value) {
  gConfig["Macros"][macroName]["Slots"][slotName] = std::move(value);
}
