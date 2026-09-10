#include <string>
#include <vector>
#include <variant>
#include "config.h"

using ExtraValue = std::variant<bool, std::string>;

std::vector<ExtraValue> getExtra(std::string mn) {
  json config = getConfig();
  std::vector<ExtraValue> extraArgs;

  // Check if the macro exists
  if (config.contains("Macros") &&
      config["Macros"].contains(mn) &&
      config["Macros"][mn].contains("Extra")) {

    // Loop through all key-value pairs in Extra
    for (auto& [key, value] : config["Macros"][mn]["Extra"].items()) {
      if (value.is_boolean()) {
        extraArgs.push_back(value.get<bool>());
      }
      else if (value.is_string()) {
        extraArgs.push_back(value.get<std::string>());
      }
    }
  }

  return extraArgs;
}