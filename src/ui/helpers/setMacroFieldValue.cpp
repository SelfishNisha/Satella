#include "../ui.h"

// updates a direct config field like Mod Key or Key for the current macro
void setMacroFieldValue(const std::string& macroName, const std::string& fieldName, std::string value) {
  gConfig["Macros"][macroName][fieldName] = std::move(value);
}
