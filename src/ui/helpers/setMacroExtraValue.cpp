#include "../ui.h"

// update a macro's extra value in the live config object
void setMacroExtraValue(const std::string& macroName, const std::string& extraName, std::string value) {
  gConfig["Macros"][macroName]["Extra"][extraName] = std::move(value);
}
