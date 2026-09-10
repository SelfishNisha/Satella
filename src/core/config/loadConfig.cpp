#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "../../../lib/json.hpp"
#include "config.h"

namespace fs = std::filesystem;

// loads the config from the file
json loadConfig() {
  // get the file's path
  std::string configPath = getConfigPath();

  // check if the config file exists
  if (fs::exists(configPath)) {
    try {
      // open the config file
      std::ifstream file(configPath);

      // check if the file was successfully opened
      if (file.is_open()) {
        // parse the data
        json configData = json::parse(file);
        
        // close it after getting the data
        file.close();

        // check if the config contains something
        if (!configData.empty()) {
          return configData;
        } else {
          std::cout << "Config file is empty, generating defaults." << std::endl;
        }
      }
    } catch (const json::parse_error& e) {
      std::cerr << "Failed to parse config.json (" << e.what() << "), generating defaults." << std::endl;
    } catch (const std::exception& e) {
      std::cerr << "Failed to read config.json (" << e.what() << "), generating defaults." << std::endl;
    }
  } else {
    std::cout << "Config file not found at " << configPath << ", creating with defaults." << std::endl;
  }

  saveConfig(defaultConfig);
  return defaultConfig;
}