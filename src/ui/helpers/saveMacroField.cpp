#include "../ui.h"

// wraps the field writer so it saves the macro value and shows a status message
std::function<void(std::string)> saveMacroField(const std::string& macroName, std::function<void(std::string)> write) {
  return std::bind(&saveMacroValue, macroName, write, std::placeholders::_1);
}
