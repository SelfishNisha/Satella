#include "config.h"

std::vector<std::string> getKeys(std::string mn) {
  json config = getConfig();
  std::vector<std::string> keys;

  // Check if the macro exists
  if (config.contains("Macros") && config["Macros"].contains(mn) &&
      config["Macros"][mn].contains("Slots")) {
    // Loop through all key-value pairs in Slots
    for (auto& [key, value] : config["Macros"][mn]["Slots"].items()) {
      keys.push_back(value.get<std::string>());
    }
  }

  return keys;
}