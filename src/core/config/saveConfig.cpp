#include <fstream>
#include <iostream>
#include <string>
#include "config.h"

// saves the config to a file.
void saveConfig(const json& data) {
  // get the right path to create the file at
  std::string configPath = getConfigPath();

  // open the config file (will be created if doesn't exist)
  std::ofstream file(configPath);

  // check if it was opened successfully
  if (file.is_open()) {
    // write the config to the file
    file << data.dump(2);  // indent = 2

    // why would i keep it open? :|
    file.close();
  } else {
    // print an error if something fucks up
    std::cerr << "Failed to save config to: " << configPath << std::endl;
  }
}
